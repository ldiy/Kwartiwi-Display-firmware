/**
 * @file tp_cal_screen.c
 *
 * @brief Touch panel calibration screen
 *
 * This screen is used to calibrate the touch panel.
 * It displays a a cross and ask the user to touch it, this is done for 6 points.
 * The points and the raw touch data are then given to the touch panel driver to calculate the calibration matrix and store it in the flash.
 * When the calibration is complete, the main screen is loaded.
 */

#include <stdio.h>
#include "lvgl.h"
#include "ui_task.h"
#include "ui.h"
#include "tp_cal_screen.h"

LV_IMG_DECLARE(cal_cross);
#define CAL_CROSS_CENTER_X 16
#define CAL_CROSS_CENTER_Y 16
#define CALIBRATION_POINTS_COUNT 6
#define MAX_TP_DATA_VALUE 4095
#define START_CAL_MSG "Touch the screen to start the calibration"
#define CAL_INS_MSG "Touch the cross"
#define CAL_DONE_MSG "Calibration complete"
#define STORE_CAL_MSG "Store calibration data?"
#define STORE_BTN_MSG "Store"
#define RESTART_BTN_MSG "Restart"

// UI elements
lv_obj_t * tp_cal_screen;
static lv_obj_t * cross_img;
static lv_obj_t * status_label;
static lv_obj_t * info_label;
static lv_obj_t * confirm_msg_box;

// Points to be calibrated
static lv_point_t points[CALIBRATION_POINTS_COUNT] = {
    {40, 50},
    {200, 60},
    {50, 270},
    {190, 260},
    {130, 100},
    {110, 220}
};

// Function prototypes
static void tp_cal_screen_init(void);
static void set_cross_pos(int16_t x, int16_t y);
static void touched_cb(lv_event_t * event);
static void confirm_msg_box_cb(lv_event_t * event);


/**
 * @brief Initialize and load the calibration screen
 */
void tp_call_load_screen(void) {
    tp_cal_screen_init();
    lv_disp_load_scr(tp_cal_screen);
}

/**
 * @brief Initialize the calibration screen
 */
static void tp_cal_screen_init(void) {
    // Screen
    tp_cal_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(tp_cal_screen, lv_color_hex(0xFFFFFF), LV_STATE_DEFAULT);
    lv_obj_set_ext_click_area(tp_cal_screen, MAX_TP_DATA_VALUE);
    lv_obj_add_event_cb(tp_cal_screen, touched_cb, LV_EVENT_PRESSED, NULL);

    // Info label
    info_label = lv_label_create(tp_cal_screen);
    lv_obj_align(info_label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_long_mode(info_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(info_label, LV_HOR_RES - 20);
    lv_obj_set_style_text_align(info_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(info_label, START_CAL_MSG);

    // Status label
    status_label = lv_label_create(tp_cal_screen);
    lv_obj_align_to(status_label, info_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_label_set_text(status_label, "");

    // Cal cross point img
    cross_img = lv_img_create(tp_cal_screen);
    lv_img_set_src(cross_img, &cal_cross);
    lv_obj_set_align(cross_img, LV_ALIGN_TOP_LEFT);
    lv_obj_add_flag(cross_img, LV_OBJ_FLAG_HIDDEN);

    // Confirm message box
    static const char * confirm_msg_box_btns[] = {STORE_BTN_MSG, RESTART_BTN_MSG, NULL};
    confirm_msg_box = lv_msgbox_create(tp_cal_screen, CAL_DONE_MSG, STORE_CAL_MSG, confirm_msg_box_btns, false);
    lv_obj_center(confirm_msg_box);
    lv_obj_add_event_cb(confirm_msg_box, confirm_msg_box_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_flag(confirm_msg_box, LV_OBJ_FLAG_HIDDEN);
}

/**
 * @brief Set the position of the calibration cross
 *
 * Sets the position of the calibration cross image, so that the center of the cross is at the given coordinates.
 *
 * @param[in] x The x coordinate
 * @param[in] y The y coordinate
 */
static void set_cross_pos(lv_coord_t x, lv_coord_t y) {
    x -= CAL_CROSS_CENTER_X;
    y -= CAL_CROSS_CENTER_Y;
    lv_obj_align(cross_img, LV_ALIGN_TOP_LEFT, x, y);
}

/**
 * @brief Show the given calibration point
 *
 * Update the position of the calibration cross to the selected point.
 * The point number compared to the total number of calibration points is shown in the status label. (e.g. "1 / 6")
 *
 * @param[in] point The index of the point to show (0 - CALIBRATION_POINTS_COUNT)
 */
static void show_point(uint8_t point) {
    assert(point < CALIBRATION_POINTS_COUNT);

    set_cross_pos(points[point].x, points[point].y);
    lv_label_set_text_fmt(status_label, "%d / %d", point+1, CALIBRATION_POINTS_COUNT);
}

/**
 * @brief Callback function for when the screen is touched
 *
 * This function is called when the screen is touched. It is used to handle the calibration process.
 * On the first touch, the calibration process is started.
 * The user is instructed to touch the cross, which moves to the next point after each touch.
 * After the last point is touched, a message box is shown, asking the user to store the calibration data or restart the calibration process.
 *
 * @param[in] event unused
 */
static void touched_cb(lv_event_t * event) {
    static bool cal_started = false;
    static lv_point_t cal_points[CALIBRATION_POINTS_COUNT];
    static uint8_t cal_point_index = 0;


    if (!cal_started) {
        lv_obj_clear_flag(cross_img, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(status_label, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(status_label, CAL_INS_MSG);

        // Show the first point
        show_point(cal_point_index = 0);

        // Use the raw input data from the touchscreen
        ui_task_use_raw_tp_data(true);

        cal_started = true;
    }
    else {
        // Get the touched point and store it
        lv_point_t p;
        lv_indev_t * indev = lv_indev_get_act();
        lv_indev_get_point(indev, &p);
        cal_points[cal_point_index] = p;

        // Move to the next point
        cal_point_index++;

        if (cal_point_index < CALIBRATION_POINTS_COUNT) {
            // Show the next point
            show_point(cal_point_index);
        }
        else {
            // Calibration done
            lv_obj_add_flag(cross_img, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(status_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(info_label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(confirm_msg_box, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_event_cb(tp_cal_screen, touched_cb);

            // Calibrate the touchscreen using the collected data
            ui_task_calibrate_tp(cal_points, points, CALIBRATION_POINTS_COUNT);

            // Now the touchscreen input data can be used normally
            ui_task_use_raw_tp_data(false);

            // Reset the calibration state so that the user can restart the calibration, if needed
            cal_started = false;
        }
    }
}

/**
 * @brief Callback function for the confirm message box
 *
 * This function is called when the buttons in the confirm message box are pressed.
 * If the "Store" button is pressed, the calibration data is stored and the main screen is shown.
 * If the "Restart" button is pressed, the calibration process is restarted.
 *
 * @param[in] event unused
 */
static void confirm_msg_box_cb(lv_event_t * event) {
    switch (lv_msgbox_get_active_btn(confirm_msg_box)) {
        case 0: // Store
            // Save the calibration data, so that it can be used on the next boot
            ui_task_store_tp_cal();

            // Go back to the main screen
            lv_obj_del_async(tp_cal_screen);
            lv_disp_load_scr(main_screen);
            break;
        case 1: // Restart
            lv_obj_clear_flag(info_label, LV_OBJ_FLAG_HIDDEN);
            lv_label_set_text(info_label, START_CAL_MSG);
            lv_obj_add_flag(confirm_msg_box, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_event_cb(tp_cal_screen, touched_cb, LV_EVENT_PRESSED, NULL);
            break;
        default:
            break;
    }
}