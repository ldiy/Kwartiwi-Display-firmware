#include <stdio.h>
#include "esp_log.h"
#include "lvgl.h"
#include "tp_cal_screen.h"
#include "data_manager.h"
#include "ui.h"

static const char * TAG = "ui";
static lv_obj_t * ui_screen1;
static lv_obj_t * ui_screen2;
static lv_obj_t * ui_label1;
static lv_obj_t * ui_label2;
static int label1_value = 0;
static void ui_Screen1_screen_init(void);
static void ui_Screen1_button1_on_click(lv_event_t *event);
static void ui_Screen1_button2_on_click(lv_event_t *event);
static void ui_Screen1_button3_on_click(lv_event_t *event);
static void ui_Screen2_screen_init(void);
void ui_init(void) {
    ESP_LOGI(TAG, "Initializing UI");
    lv_disp_t * disp = lv_disp_get_default();
//    ui_Screen1_screen_init();
//    tp_cal_screen_init();
//    lv_disp_load_scr(ui_screen1);
    ui_Screen2_screen_init();
    lv_disp_load_scr(ui_screen2);
}

void ui_load_screen1(void) {
    lv_disp_load_scr(ui_screen1);
}

static void ui_Screen1_screen_init(void) {
    ui_screen1 = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(ui_screen1, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_label1 = lv_label_create(ui_screen1);
    lv_obj_align(ui_label1, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(ui_label1, "0");

    // Create 2 buttons
    lv_obj_t * btn1 = lv_btn_create(ui_screen1);
    lv_obj_set_pos(btn1, 10, 10);
    lv_obj_set_size(btn1, 100, 50);
    lv_obj_t * label1 = lv_label_create(btn1);
    lv_label_set_text(label1, "Increment");

    lv_obj_t * btn2 = lv_btn_create(ui_screen1);
    lv_obj_set_pos(btn2, 10, 70);
    lv_obj_set_size(btn2, 100, 50);
    lv_obj_t * label2 = lv_label_create(btn2);
    lv_label_set_text(label2, "Decrement");

    lv_obj_t * btn3 = lv_btn_create(ui_screen1);
    lv_obj_set_pos(btn3, 10, 140);
    lv_obj_set_size(btn3, 100, 50);
    lv_obj_t * label3 = lv_label_create(btn3);
    lv_label_set_text(label3, "Cal Screen");

    // Set the callbacks for the buttons
    lv_obj_add_event_cb(btn1,  ui_Screen1_button1_on_click, LV_EVENT_PRESSED , NULL);
    lv_obj_add_event_cb(btn2,  ui_Screen1_button2_on_click, LV_EVENT_PRESSED , NULL);
    lv_obj_add_event_cb(btn3,  ui_Screen1_button3_on_click, LV_EVENT_PRESSED , NULL);


}

// Increment the value of label1 and update the label when button 1 is pressed
static void ui_Screen1_button1_on_click(lv_event_t * event) {
    label1_value++;
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", label1_value);
    lv_label_set_text(ui_label1, buf);
}

// Decrement the value of label1 and update the label when button 2 is pressed
static void ui_Screen1_button2_on_click(lv_event_t * event) {
    label1_value--;
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", label1_value);
    lv_label_set_text(ui_label1, buf);
}

// Load the cal_screen when button 3 is pressed
static void ui_Screen1_button3_on_click(lv_event_t * event) {
    tp_call_load_screen();
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





