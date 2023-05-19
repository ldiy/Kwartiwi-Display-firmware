#ifndef WEB_CLIENT_H
#define WEB_CLIENT_H

#include "esp_event.h"

#define WEB_CLIENT_NVS_NAMESPACE "web_client"
#define WEB_CLIENT_NVS_SERVER_HOSTNAME_KEY "srv-host"

ESP_EVENT_DECLARE_BASE(WEB_CLIENT_EVENTS);

typedef enum {
    WEB_CLIENT_INITIALIZED,
    WEB_CLIENT_EVENT_CONNECTED,
    WEB_CLIENT_EVENT_DISCONNECTED,
    WEB_CLIENT_SERVERS_FOUND,
//    WEB_CLIENT_EVENT_METER_DATA_RECEIVED,
//    WEB_CLIENT_EVENT_METER_HISTORY_RECEIVED,
} web_client_event_id_t;

typedef struct {
    char hostname[256];
    uint16_t port;
    esp_ip_addr_t ip;
} web_client_server_t;

// servers found cb
typedef void (*web_client_servers_found_cb_t)(web_client_server_t *servers, uint8_t count);


// Function prototypes
_Noreturn void web_client_task(void *pvParameters);
void web_client_find_servers(void);

uint8_t web_client_get_found_servers(web_client_server_t **servers);
SemaphoreHandle_t web_client_get_found_servers_mutex(void);
esp_err_t web_client_save_server_config(const char *hostname);

#endif //WEB_CLIENT_H
