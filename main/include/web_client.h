#ifndef WEB_CLIENT_H
#define WEB_CLIENT_H

#include "esp_event.h"

ESP_EVENT_DECLARE_BASE(WEB_CLIENT_EVENTS);

typedef enum {
    WEB_CLIENT_INITIALIZED,
    WEB_CLIENT_EVENT_CONNECTED,
    WEB_CLIENT_EVENT_DISCONNECTED,
//    WEB_CLIENT_EVENT_METER_DATA_RECEIVED,
//    WEB_CLIENT_EVENT_METER_HISTORY_RECEIVED,
} web_client_event_id_t;

// Function prototypes
_Noreturn void web_client_task(void *pvParameters);

#endif //WEB_CLIENT_H
