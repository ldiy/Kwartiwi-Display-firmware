#include "lvgl.h"
#include "tp_cal_screen.h"
#include "main_screen.h"


lv_obj_t * main_screen;
static lv_obj_t * ui_label1;
static int label1_value = 0;

static void button1_on_click(lv_event_t *event);
static void button2_on_click(lv_event_t *event);
static void button3_on_click(lv_event_t *event);

void main_screen_init(void) {
    main_screen = lv_obj_create(NULL);
    lv_obj_clear_flag(main_screen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(main_screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_label1 = lv_label_create(main_screen);
    lv_obj_align(ui_label1, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(ui_label1, "0");

    // Create 2 buttons
    lv_obj_t * btn1 = lv_btn_create(main_screen);
    lv_obj_set_pos(btn1, 10, 10);
    lv_obj_set_size(btn1, 100, 50);
    lv_obj_t * label1 = lv_label_create(btn1);
    lv_label_set_text(label1, "Increment");

    lv_obj_t * btn2 = lv_btn_create(main_screen);
    lv_obj_set_pos(btn2, 10, 70);
    lv_obj_set_size(btn2, 100, 50);
    lv_obj_t * label2 = lv_label_create(btn2);
    lv_label_set_text(label2, "Decrement");

    lv_obj_t * btn3 = lv_btn_create(main_screen);
    lv_obj_set_pos(btn3, 10, 140);
    lv_obj_set_size(btn3, 100, 50);
    lv_obj_t * label3 = lv_label_create(btn3);
    lv_label_set_text(label3, "Cal Screen");

    // Set the callbacks for the buttons
    lv_obj_add_event_cb(btn1, button1_on_click, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(btn2, button2_on_click, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(btn3, button3_on_click, LV_EVENT_PRESSED, NULL);
}

// Increment the value of label1 and update the label when button 1 is pressed
static void button1_on_click(lv_event_t * event) {
    label1_value++;
    lv_label_set_text_fmt(ui_label1, "%d", label1_value);
}

// Decrement the value of label1 and update the label when button 2 is pressed
static void button2_on_click(lv_event_t * event) {
    label1_value--;
    lv_label_set_text_fmt(ui_label1, "%d", label1_value);
}

// Load the cal_screen when button 3 is pressed
static void button3_on_click(lv_event_t * event) {
    tp_call_load_screen();
}