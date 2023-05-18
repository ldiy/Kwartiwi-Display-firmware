#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include <time.h>
#include <stdbool.h>
#include <stdint.h>


extern lv_obj_t * main_screen;
extern bool main_screen_initialized;

// Function prototypes
void main_screen_init(void);
void ui_set_power_consumption(uint16_t value);
void ui_set_time(time_t time);
void ui_set_max_peak_line(uint16_t value);
void ui_set_new_max_peak_demand(uint16_t value);
void ui_reset_peak_demand_chart_data(void);
void ui_add_peak_demand_data_point(time_t time, uint16_t value);
void ui_set_predicted_peak(uint16_t value);
void ui_set_wifi_status(bool connected);
void ui_set_connected_status(bool connected);



#endif //MAIN_SCREEN_H
