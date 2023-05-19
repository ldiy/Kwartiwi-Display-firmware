#ifndef SETUP_SCREEN_H
#define SETUP_SCREEN_H

#include "lvgl.h"

extern lv_obj_t * setup_screen;
extern bool setup_screen_initialized;

// Function prototypes
void setup_screen_init(void);
void setup_screen_wifi_connected_status_cb(bool connected);
void setup_screen_set_wifi_scan_result(const ui_wifi_network_t *networks, uint16_t len);
void setup_screen_set_servers_found(const ui_server_t *servers, uint8_t len);

#endif //SETUP_SCREEN_H
