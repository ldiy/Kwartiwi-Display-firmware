#include <stdio.h>
#include "esp_log.h"
#include "lvgl.h"
#include "tp_cal_screen.h"
#include "ui.h"

static const char * TAG = "ui";
static lv_obj_t * ui_screen1;
static lv_obj_t * ui_label1;
static int label1_value = 0;
static void ui_Screen1_screen_init(void);
static void ui_Screen1_button1_on_click(lv_event_t *event);
static void ui_Screen1_button2_on_click(lv_event_t *event);
static void ui_Screen1_button3_on_click(lv_event_t *event);

void ui_init(void) {
    ESP_LOGI(TAG, "Initializing UI");
    lv_disp_t * disp = lv_disp_get_default();
    ui_Screen1_screen_init();
//    tp_cal_screen_init();
    lv_disp_load_scr(ui_screen1);
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