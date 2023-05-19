/**
 * @file web_client.c
 * @brief Web client task and related functions
 *
 * This file contains a task that periodically sends requests to the server and parses the response.
 * The parsed data is then sent to the data manager.
 *
 * This file also contains functions for server discovery using mDNS, and setting the server configuration.
 */

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "nvs.h"
#include "mdns.h"
#include "cJSON.h"
#include "data_manager.h"
#include "networking.h"
#include "web_client.h"

#define DISCONNECTED_STATUS_FAILED_REQ_COUNT 5  // Number of consecutive failed requests before setting the status to disconnected
#define REQUEST_INTERVAL_MS 2000
#define HTTP_BUF_SIZE (100 * 1024)  // 100 KB
#define API_METER_DATA_ENDPOINT "/api/meter-data"
#define API_METER_DATA_HISTORY_ENDPOINT "/api/meter-data-history"

#define SERVER_DISCOVERY_TIMEOUT_MS 5000
#define SERVER_DISCOVERY_MAX_SERVERS 5

ESP_EVENT_DEFINE_BASE(WEB_CLIENT_EVENTS);

extern esp_event_loop_handle_t app_loop_handle;

// parse function callback type
typedef esp_err_t (*parse_publish_data_cb_t)(uint8_t *buf, uint32_t len);

static const char *TAG = "web_client";
static uint8_t *http_buf = NULL;
static esp_http_client_config_t config;
static bool connected = false;
static char server_host[256];

static web_client_server_t found_servers[SERVER_DISCOVERY_MAX_SERVERS];
static uint8_t found_servers_count = 0;
SemaphoreHandle_t found_servers_mutex = NULL; // Mutex for found_servers and found_servers_count

// Function prototypes
static esp_err_t web_client_init(void);
static esp_err_t http_event_handler(esp_http_client_event_t *e);
static esp_err_t parse_publish_meter_data(uint8_t *buf, uint32_t len);
static esp_err_t parse_publish_meter_data_history(uint8_t *buf, uint32_t len);
static esp_err_t request(const char *path, parse_publish_data_cb_t cb);
static esp_err_t read_server_config_from_nvs(void);


/**
 * @brief Web client task
 *
 * Initializes the web client and then periodically requests meter data from the API.
 * The received data is parsed and published to the data manager.
 *
 * @note This task should only be started after the following components have been initialized:
 *   - Networking
 *   - Event loop (default and app)
 *   - Data manager
 *
 * @todo Keep the connection open as long as possible to reduce overhead
 * @todo Request meter data history every x hours to keep the data manager up to date
 *
 * @param pvParameters unused
 */
_Noreturn void web_client_task(void *pvParameters) {
    esp_err_t err;

    ESP_LOGI(TAG, "Starting web client task");

    // Initialize the web client
    err = web_client_init();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize web client");
        vTaskDelete(NULL);
        abort();
    }
    ESP_ERROR_CHECK(esp_event_post_to(app_loop_handle, WEB_CLIENT_EVENTS, WEB_CLIENT_INITIALIZED, NULL, 0, portMAX_DELAY));

    // Request meter data history
    while (request(API_METER_DATA_HISTORY_ENDPOINT, parse_publish_meter_data_history) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to request meter data history. Retrying in %d ms", REQUEST_INTERVAL_MS);
        vTaskDelay(pdMS_TO_TICKS(REQUEST_INTERVAL_MS));
    }
    data_manager_notify_new_meter_history_data_available();

    // Request meter data periodically
    for(;;) {
        if(request(API_METER_DATA_ENDPOINT, parse_publish_meter_data) == ESP_OK) {
            data_manager_notify_new_meter_data_available();
        } else {
            ESP_LOGE(TAG, "Failed to request meter data. Retrying in %d ms", REQUEST_INTERVAL_MS);
        }
        vTaskDelay(pdMS_TO_TICKS(REQUEST_INTERVAL_MS));
    }

    // Free resources
    heap_caps_free(http_buf);
    vTaskDelete(NULL);
}

/**
 * @brief Task that searches for servers using mDNS
 *
 * This task searches for servers using mDNS and stores the results in found_servers.
 * When the task is finished, it posts the WEB_CLIENT_SERVERS_FOUND event to the default event loop.
 *
 * @param[in] pvParameters unused
 */
void find_servers_task(void *pvParameters) {
    ESP_LOGI(TAG, "Starting find servers task");

    mdns_result_t * results = NULL;
    uint8_t num_servers = 0;

    esp_err_t err = mdns_query_ptr("_kwartiwi-p1", "_tcp", SERVER_DISCOVERY_TIMEOUT_MS, SERVER_DISCOVERY_MAX_SERVERS, &results);
    if(err){
        ESP_LOGE(TAG, "Query Failed");
        return;
    }
    if(!results){
        ESP_LOGW(TAG, "No results found!");
        return;
    }

    // Take the mutex
    xSemaphoreTake(found_servers_mutex, portMAX_DELAY);

    if (err == ESP_OK && results != NULL) {
        for (mdns_result_t * r = results; r; r = r->next) {
            if (r->hostname) {
                // store the hostname with .local added
//                strncpy(found_servers[num_servers].hostname, r->hostname, sizeof(found_servers[num_servers].hostname));
                snprintf(found_servers[num_servers].hostname, sizeof(found_servers[num_servers].hostname), "%s.local", r->hostname);
            }
            if (r->port) {
                // store the port
                found_servers[num_servers].port = r->port;
            }
            if (r->addr) {
                // store the ip address
                found_servers[num_servers].ip = r->addr->addr;
            }
            ESP_LOGD(TAG, "Found server %s:%d", found_servers[num_servers].hostname, found_servers[num_servers].port);
            num_servers++;
        }
    }
    found_servers_count = num_servers;
    mdns_query_results_free(results);

    ESP_LOGI(TAG, "Found %d servers", num_servers);

    // Give the mutex back
    xSemaphoreGive(found_servers_mutex);

    // Notify the rest of the application that servers have been found
    ESP_ERROR_CHECK(esp_event_post_to(app_loop_handle, WEB_CLIENT_EVENTS, WEB_CLIENT_SERVERS_FOUND, NULL, 0, portMAX_DELAY));

    vTaskDelete(NULL);
}

/**
 * @brief Starts the find servers task
 *
 * This function starts the find servers task. When the task is finished, it posts the WEB_CLIENT_SERVERS_FOUND event.
 * The found servers can be accessed using web_client_get_found_servers().
 *
 * The task is started with the same priority as the task that calls this function.
 */
void web_client_find_servers(void) {

   if (found_servers_mutex == NULL) {
        found_servers_mutex = xSemaphoreCreateMutex();
        assert(found_servers_mutex != NULL);
    }

    // Start the task with the same priority as the current task
    xTaskCreate(find_servers_task, "find_servers_task", 4096, NULL, uxTaskPriorityGet(NULL), NULL);
}

/**
 * @brief Get the found servers
 *
 *
 * @note The found servers mutex must be taken before calling this function or using the returned pointer
 *
 * @param[out] servers A pointer to an array of web_client_server_t structs, this will be set to the found servers pointer
 * @return The number of found servers
 */
uint8_t web_client_get_found_servers(web_client_server_t **servers) {
    uint8_t num_servers = 0;

    num_servers = found_servers_count;
    *servers = found_servers;

    return num_servers;
}

/**
 * @brief Get the found servers mutex
 *
 * @warnig web_client_find_servers() must have been called once before calling this function, otherwise the mutex may not be created yet
 *
 * @return The found servers mutex
 */
SemaphoreHandle_t web_client_get_found_servers_mutex(void) {
    assert(found_servers_mutex != NULL);
    return found_servers_mutex;
}

/**
 * @brief Save the given server config to NVS
 *
 * @param[in] hostname The hostname of the server to save
 * @return ESP_OK on success, otherwise an NVS error code
 */
esp_err_t web_client_save_server_config(const char *const hostname) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(WEB_CLIENT_NVS_NAMESPACE, NVS_READWRITE, &nvs_handle);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open NVS namespace %s", WEB_CLIENT_NVS_NAMESPACE);
        return err;
    }

    err = nvs_set_str(nvs_handle, WEB_CLIENT_NVS_SERVER_HOSTNAME_KEY, hostname);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set %s in NVS", WEB_CLIENT_NVS_SERVER_HOSTNAME_KEY);
        nvs_close(nvs_handle);
        return err;
    }

    err = nvs_commit(nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to commit NVS");
        nvs_close(nvs_handle);
        return err;
    }

    nvs_close(nvs_handle);

    return ESP_OK;
}

/**
 * @brief Read the server config from NVS
 *
 * @note This function uses the global server_host variable
 * @warnig This function is not thread safe, it should only be called from the web client task
 *
 * @return ESP_OK on success, otherwise an NVS error code
 */
static esp_err_t read_server_config_from_nvs(void) {
    nvs_handle_t nvs_handle;
    esp_err_t err;

    // Open NVS
    err = nvs_open(WEB_CLIENT_NVS_NAMESPACE, NVS_READONLY, &nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open NVS");
        return ESP_FAIL;
    }

    // Read the server URL
    size_t host_len = sizeof(server_host);
    err = nvs_get_str(nvs_handle, WEB_CLIENT_NVS_SERVER_HOSTNAME_KEY, server_host, &host_len);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read server URL from NVS");
        return ESP_FAIL;
    }

    // Close NVS
    nvs_close(nvs_handle);

    return ESP_OK;
}


/**
 * @brief Initialize the web client
 *
 * @note This function should only be called once, and only from the web client task
 *
 * @return ESP_OK on success, ESP_FAIL otherwise
 */
static esp_err_t web_client_init(void) {
    http_buf = heap_caps_malloc(HTTP_BUF_SIZE, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
    if (http_buf == NULL) {
        ESP_LOGE(TAG, "Failed to allocate HTTP buffer");
        return ESP_ERR_NO_MEM;
    }

    // Read config from NVS
    ESP_ERROR_CHECK(read_server_config_from_nvs());

    config.user_data = http_buf;
    config.event_handler = http_event_handler;
    config.host = server_host;
    config.path = "/";

    return ESP_OK;
}

/**
 * @brief Do a HTTP GET request to the specified path and call the specified callback when finished
 *
 * The received data is stored in the global http_buf variable.
 * When the request is finished with a 200 status code, the callback is called.
 *
 * @note This function is blocking
 * @warning This function is not thread-safe
 *
 * @param path
 * @param cb
 * @return
 */
static esp_err_t request(const char *path, parse_publish_data_cb_t cb) {
    static uint8_t failed_req_count = 0;
    esp_err_t err;
    esp_http_client_handle_t client;

    // Check arguments
    if (path == NULL || cb == NULL) {
        ESP_LOGE(TAG, "Invalid arguments");
        return ESP_ERR_INVALID_ARG;
    }

    // Initialize an HTTP client with the global config
    client = esp_http_client_init(&config);
    if (client == NULL) {
        ESP_LOGE(TAG, "Failed to initialise HTTP client");
        return ESP_FAIL;
    }

    // Set the URL to the specified path
    err = esp_http_client_set_url(client, path);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set URL");
        return ESP_FAIL;
    }

    // Perform the HTTP GET request
    err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        if (esp_http_client_get_status_code(client) == 200) {
            if (cb(http_buf, esp_http_client_get_content_length(client)) != ESP_OK) {
                ESP_LOGE(TAG, "Failed to parse and publish data");
                err = ESP_FAIL;
            }
        }
        else {
            ESP_LOGW(TAG, "HTTP GET request returned non-200 status code: %d", esp_http_client_get_status_code(client));
            err = ESP_FAIL;
        }

        // Reset the failed request count and set the status to connected
        if (!connected) {
            ESP_LOGI(TAG, "Setting status to connected");
            failed_req_count = 0;
            connected = true;
            ESP_ERROR_CHECK(esp_event_post_to(app_loop_handle, WEB_CLIENT_EVENTS, WEB_CLIENT_EVENT_CONNECTED, NULL, 0, portMAX_DELAY));
        }
    }
    else {
        ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
        failed_req_count++;
        if (failed_req_count == DISCONNECTED_STATUS_FAILED_REQ_COUNT) {
            ESP_LOGE(TAG, "Maximum failed request count reached. Setting status to disconnected");
            connected = false;
            ESP_ERROR_CHECK(esp_event_post_to(app_loop_handle, WEB_CLIENT_EVENTS, WEB_CLIENT_EVENT_DISCONNECTED, NULL, 0, portMAX_DELAY));
        }
    }

    // Close the connection and free resources
    ESP_ERROR_CHECK(esp_http_client_cleanup(client));

    return err;
}

/**
 * @brief HTTP client event handler
 *
 * This function is called by the HTTP client when an event occurs.
 *
 * @warning This function is not thread-safe
 *
 * @param[in] e The http client event
 * @return ESP_OK on success
 */
static esp_err_t http_event_handler(esp_http_client_event_t *e) {
    static size_t total_len = 0;
    switch (e->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGV(TAG, "HTTP_EVENT_ERROR");
            total_len = 0;
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGV(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGV(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGV(TAG, "HTTP_EVENT_ON_HEADER");
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGV(TAG, "HTTP_EVENT_ON_DATA");
            if (e->user_data != NULL) {
                // Copy the received data to the user_data buffer
                size_t len = e->data_len > (HTTP_BUF_SIZE - total_len) ? (HTTP_BUF_SIZE - total_len) : e->data_len;
                if (len < e->data_len) {
                    ESP_LOGW(TAG, "HTTP_EVENT_ON_DATA: data_len is larger than the user_data buffer");
                }
                memcpy(e->user_data + total_len, e->data, len);
                total_len += len;
            }
            else {
                ESP_LOGW(TAG, "HTTP_EVENT_ON_DATA: user_data is NULL");
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGV(TAG, "HTTP_EVENT_ON_FINISH");
            if (e->user_data != NULL) {
                ((uint8_t *)e->user_data)[total_len] = '\0';
            }
            total_len = 0;
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGV(TAG, "HTTP_EVENT_DISCONNECTED");
            total_len = 0;
            break;
        case HTTP_EVENT_REDIRECT:
            ESP_LOGV(TAG, "HTTP_EVENT_REDIRECT");
            break;
    }

    return ESP_OK;
}

/**
 * @brief Parse and publish the data from the meter data endpoint
 *
 * Parse the JSON data in the HTTP buffer and give it to the data manager
 *
 * The following fields are parsed and published:
 *   - timestamp
 *   - electricity delivered tariff 1
 *   - electricity delivered tariff 2
 *   - electricity returned tariff 1
 *   - electricity returned tariff 2
 *   - current average demand
 *   - current power usage
 *   - current power return
 *   - max demand of the active month
 *   - predicted peak and time
 *
 * @todo Write data directly to the data managers data struct instead of using the set_field function
 *
 * @param[in] buf The buffer containing the JSON data
 * @param[in] len The length of the JSON data
 * @return ESP_OK on success, ESP_FAIL on failure
 */
static esp_err_t parse_publish_meter_data(uint8_t *buf, uint32_t len) {
    esp_err_t err = ESP_OK;
    cJSON *obj;
    float tmp_float;
    time_t p1_timestamp;

    // Parse the JSON data
    cJSON *root = cJSON_ParseWithLength((char *) buf, len);
    if (root == NULL) {
        ESP_LOGE(TAG, "Failed to parse JSON");
        return ESP_FAIL;
    }

    // Timestamp
    obj = cJSON_GetObjectItem(root, "timestamp");
    if (cJSON_IsNumber(obj)) {
        p1_timestamp = (time_t)obj->valueint;
        data_manager_set_field(DM_DF_P1_TIMESTAMP, &p1_timestamp);
    }
    else {
        ESP_LOGW(TAG, "Failed to parse timestamp");
        err = ESP_FAIL;
    }

    // Electricity delivered tariff 1
    obj = cJSON_GetObjectItem(root, "electricityDeliveredTariff1");
    if (cJSON_IsNumber(obj)) {
        tmp_float = (float)obj->valuedouble;
        data_manager_set_field(DM_DF_ELECTRICITY_DELIVERED_TARIFF1, &tmp_float);
    }
    else {
        ESP_LOGW(TAG, "Failed to parse electricityDeliveredTariff1");
        err = ESP_FAIL;
    }

    // Electricity delivered tariff 2
    obj = cJSON_GetObjectItem(root, "electricityDeliveredTariff2");
    if (cJSON_IsNumber(obj)) {
        tmp_float = (float)obj->valuedouble;
        data_manager_set_field(DM_DF_ELECTRICITY_DELIVERED_TARIFF2, &tmp_float);
    }
    else {
        ESP_LOGW(TAG, "Failed to parse electricityDeliveredTariff2");
        err = ESP_FAIL;
    }

    // Electricity returned tariff 1
    obj = cJSON_GetObjectItem(root, "electricityReturnedTariff1");
    if (cJSON_IsNumber(obj)) {
        tmp_float = (float)obj->valuedouble;
        data_manager_set_field(DM_DF_ELECTRICITY_RETURNED_TARIFF1, &tmp_float);
    }
    else {
        ESP_LOGW(TAG, "Failed to parse electricityReturnedTariff1");
        err = ESP_FAIL;
    }

    // Electricity returned tariff 2
    obj = cJSON_GetObjectItem(root, "electricityReturnedTariff2");
    if (cJSON_IsNumber(obj)) {
        tmp_float = (float)obj->valuedouble;
        data_manager_set_field(DM_DF_ELECTRICITY_RETURNED_TARIFF2, &tmp_float);
    }
    else {
        ESP_LOGW(TAG, "Failed to parse electricityReturnedTariff2");
        err = ESP_FAIL;
    }

    // Current average demand
    obj = cJSON_GetObjectItem(root, "currentAvgDemand");
    if (cJSON_IsNumber(obj)) {
        tmp_float = (float)obj->valuedouble;
        data_manager_set_field(DM_DF_CURRENT_AVG_DEMAND, &tmp_float);
        data_manager_add_max_demand_short_term_history_item(tmp_float, p1_timestamp);
    }
    else {
        ESP_LOGW(TAG, "Failed to parse currentAvgDemand");
        err = ESP_FAIL;
    }

    // Current power usage
    obj = cJSON_GetObjectItem(root, "currentPowerUsage");
    if (cJSON_IsNumber(obj)) {
        tmp_float = (float)obj->valuedouble;
        data_manager_set_field(DM_DF_CURRENT_POWER_USAGE, &tmp_float);
    }
    else {
        ESP_LOGW(TAG, "Failed to parse currentPowerUsage");
        err = ESP_FAIL;
    }

    // Current power return
    obj = cJSON_GetObjectItem(root, "currentPowerReturn");
    if (cJSON_IsNumber(obj)) {
        tmp_float = (float)obj->valuedouble;
        data_manager_set_field(DM_DF_CURRENT_POWER_RETURN, &tmp_float);
    }
    else {
        ESP_LOGW(TAG, "Failed to parse currentPowerReturn");
        err = ESP_FAIL;
    }

    // Max demand month
    obj = cJSON_GetObjectItem(root, "maxDemandMonth");
    if (cJSON_IsObject(obj)) {
        cJSON *timestamp = cJSON_GetObjectItem(obj, "timestamp");
        cJSON *demand = cJSON_GetObjectItem(obj, "demand");
        if (cJSON_IsNumber(timestamp) && cJSON_IsNumber(demand)) {
            data_manager_demand_data_point_t max_demand_month = {
                    .timestamp = (time_t)timestamp->valueint,
                    .demand = (float)demand->valuedouble
            };
            data_manager_set_field(DM_DF_MAX_DEMAND_MONTH, &max_demand_month);
        }
        else {
            ESP_LOGW(TAG, "Failed to parse maxDemandMonth");
            err = ESP_FAIL;
        }
    }
    else {
        ESP_LOGW(TAG, "Failed to parse maxDemandMonth");
        err = ESP_FAIL;
    }

    // Predicted peak
    data_manager_demand_data_point_t predicted_peak;
    bool ok = true;
    obj = cJSON_GetObjectItem(root, "predictedPeak");
    if (cJSON_IsNumber(obj)) {
        predicted_peak.demand = (float)obj->valuedouble;
    }
    else {
        ESP_LOGW(TAG, "Failed to parse predictedPeak");
        err = ESP_FAIL;
        ok = false;
    }

    // Predicted peak time
    obj = cJSON_GetObjectItem(root, "predictedPeakTime");
    if (cJSON_IsNumber(obj)) {
        predicted_peak.timestamp = obj->valueint;
    }
    else {
        ESP_LOGW(TAG, "Failed to parse predictedPeakTime");
        err = ESP_FAIL;
        ok = false;
    }

    if (ok) {
        data_manager_set_field(DM_DF_PREDICTED_PEAK, &predicted_peak);
    }

    cJSON_Delete(root);
    return err;
}

/**
 * @brief Parse and publish data from the meter data history endpoint
 *
 * Parse the JSON data in the HTTP buffer and give it to the data manager
 *
 * The following fields are parsed and published:
 *   - max demand of the last 13 months (max demand year)
 *   - short term history of the max demand
 *
 * @param[in] buf The buffer containing the JSON data
 * @param[in] len The length of the JSON data
 * @return ESP_OK on success, ESP_FAIL otherwise
 */
static esp_err_t parse_publish_meter_data_history(uint8_t *buf, uint32_t len) {
    esp_err_t err = ESP_OK;
    cJSON *obj;
    uint16_t i;
    SemaphoreHandle_t data_manager_mutex = data_manager_get_data_mutex_handle();
    data_manager_history_data_t *short_term_history = data_manager_get_history_data();

    // Parse the JSON data
    cJSON *root = cJSON_ParseWithLength((char *) buf, len);
    if (root == NULL) {
        ESP_LOGE(TAG, "Failed to parse JSON");
        return ESP_FAIL;
    }

    xSemaphoreTake(data_manager_mutex, portMAX_DELAY);

    // Max demand year
    obj = cJSON_GetObjectItem(root, "maxDemandYear");
    if (cJSON_IsArray(obj)) {
        cJSON *item;
        i = 0;
        cJSON_ArrayForEach(item, obj) {
            cJSON *timestamp = cJSON_GetObjectItem(item, "timestamp");
            cJSON *demand = cJSON_GetObjectItem(item, "demand");
            if (cJSON_IsNumber(timestamp) && cJSON_IsNumber(demand) && i < DATA_MANAGER_MAX_DEMAND_YEAR_ITEMS) {
                short_term_history->max_demand_year[i].timestamp = (time_t)timestamp->valueint;
                short_term_history->max_demand_year[i].demand = (float)demand->valuedouble;
                i++;
            }
            else {
                ESP_LOGW(TAG, "Failed to parse maxDemandYear");
                err = ESP_FAIL;
            }
        }
        short_term_history->max_demand_year_items = i;
    }
    else {
        ESP_LOGW(TAG, "Failed to parse maxDemandYear");
        err = ESP_FAIL;
    }

    // Short term history
    obj = cJSON_GetObjectItem(root, "shortTermHistory");
    if (cJSON_IsArray(obj)) {
        cJSON *item;
        i = 0;
        cJSON_ArrayForEach(item, obj) {
            cJSON *timestamp = cJSON_GetObjectItem(item, "timestamp");
            cJSON *demand = cJSON_GetObjectItem(item, "avgDemand");
            if (cJSON_IsNumber(timestamp) && cJSON_IsNumber(demand) && i < DATA_MANAGER_MAX_DEMAND_SHORT_TERM_ITEMS) {
                short_term_history->max_demand_short_term[i].timestamp = (time_t)timestamp->valueint;
                short_term_history->max_demand_short_term[i].demand = (float)demand->valuedouble;
                i++;
            }
            else {
                ESP_LOGW(TAG, "Failed to parse shortTermHistory");
                err = ESP_FAIL;
            }
        }
        short_term_history->max_demand_short_term_items = i;
    }
    else {
        ESP_LOGW(TAG, "Failed to parse shortTermHistory");
        err = ESP_FAIL;
    }

    // Free resources
    xSemaphoreGive(data_manager_mutex);
    cJSON_Delete(root);

    return err;
}