#include <stdio.h>
#include "esp_log.h"
#include "lvgl.h"
#include "data_manager.h"

#include "ui.h"

static const char * TAG = "ui";

static lv_obj_t * ui_screen2;
static lv_obj_t * ui_label2;


static void load_main_screen(lv_timer_t * timer);
lv_timer_t * loading_screen_timer;

void ui_init(void) {
    ESP_LOGI(TAG, "Initializing UI");
    lv_disp_t * disp = lv_disp_get_default();

    // Show the loading screen
    loading_screen_init();
    lv_disp_load_scr(loading_screen);

    // Wait until everything is loaded
    // TODO: wait until everything is loaded before showing the main screen
    loading_screen_timer = lv_timer_create(load_main_screen, 2000, NULL);
    lv_timer_set_repeat_count(loading_screen_timer, 1);

}

static void load_main_screen(lv_timer_t * timer) {
    main_screen_init();
    lv_disp_load_scr(main_screen);

    // De-init the loading screen
    loading_screen_deinit();
}



// Show the following values from the data manager on screen 2 in a single label, every item on a new line
// - p1 timestamp
// - electricity delivered tariff 1
// - current avg demand
// - current power usage
// - max demand month and time
// - predicted peak and time
// Update the values every second if the screen is active

static void update_screen2(void) {
    char buf[256];

    time_t timestamp;
    float electricity_delivered_tariff_1;
    float current_avg_demand;
    float current_power_usage;
    data_manager_demand_data_point_t max_demand_month;
    data_manager_demand_data_point_t predicted_peak;

    data_manager_get_field(DM_DF_P1_TIMESTAMP, &timestamp);
    data_manager_get_field(DM_DF_ELECTRICITY_DELIVERED_TARIFF1, &electricity_delivered_tariff_1);
    data_manager_get_field(DM_DF_CURRENT_AVG_DEMAND, &current_avg_demand);
    data_manager_get_field(DM_DF_CURRENT_POWER_USAGE, &current_power_usage);
    data_manager_get_field(DM_DF_MAX_DEMAND_MONTH, &max_demand_month);
    data_manager_get_field(DM_DF_PREDICTED_PEAK, &predicted_peak);

    snprintf(buf, sizeof(buf), "p1 timestamp: %s\n"
                                "del tariff 1: %f\n"
                                "avg demand: %f\n"
                                "power usage: %f\n"
                                "max dem mo %f at: %s\n"
                                "peak %f at: %s\n",
                                ctime(&(timestamp)),
                                electricity_delivered_tariff_1,
                                current_avg_demand,
                                current_power_usage,
                                max_demand_month.demand,
                                ctime(&(max_demand_month.timestamp)),
                                predicted_peak.demand,
                                ctime(&(predicted_peak.timestamp))
    );
    lv_label_set_text(ui_label2, buf);
}
void ui_update_screen2_timer(lv_timer_t *t) {
    update_screen2();
}
static void ui_Screen2_screen_init(void) {
    ui_screen2 = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(ui_screen2, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_label2 = lv_label_create(ui_screen2);
    update_screen2();

    lv_timer_t * timer = lv_timer_create(ui_update_screen2_timer, 2000, NULL);
}





