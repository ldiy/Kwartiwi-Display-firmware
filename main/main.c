#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_event.h"
#include "networking.h"

void app_main(void) {

    //Initialize NVS
    esp_err_t err = nvs_flash_init();
    // Check if NVS partition was truncated
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // Erase NVS partition and try again
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    // Initialize the event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Initialize networking
    esp_log_level_set("networking", ESP_LOG_DEBUG);
    setup_networking();
}
