#ifndef NETWORKING_H
#define NETWORKING_H

#include <stdbool.h>
#include "esp_bit_defs.h"
#include "esp_event.h"
#include "esp_wifi.h"

// NVS keys
#define NETWORKING_NVS_NAMESPACE "networking"
#define NETWORKING_NVS_KEY_STA_SSID "station_ssid"
#define NETWORKING_NVS_KEY_STA_PASS "station_pass"
#define NETWORKING_NVS_KEY_HOSTNAME "hostname"
#define NETWORKING_NVS_KEY_MDNS_INSTANCE_NAME "mdns_instance"

#define NETWORKING_WIFI_STA_CONN_RETRIES 5  // Number of times to retry connecting to AP before giving up (max 255)
#define NETWORKING_WIFI_STA_WPA2_ONLY true  // Only connect to APs that support WPA2

#define NETWORKING_HOSTNAME_MAX_LEN 32              // Max length of hostname
#define NETWORKING_MDNS_INSTANCE_NAME_MAX_LEN 32    // Max length of mDNS instance name


ESP_EVENT_DECLARE_BASE(NETWORKING_EVENTS);

typedef enum {
    NETWORKING_INITIALIZED,
    NETWORKING_EVENT_WIFI_CONNECTED,
    NETWORKING_EVENT_WIFI_DISCONNECTED,
    NETWORKING_EVENT_WIFI_SCAN_DONE,
} networking_event_id_t;


// Function prototypes
void setup_networking(void);
esp_err_t networking_wifi_connect(void);
void networking_wifi_scan(void);
bool networking_is_initialized(void);
void networking_set_wifi_config(const char * ssid, const char * password);
esp_err_t networking_save_wifi_config(const char * ssid, const char * password);

#endif //NETWORKING_H
