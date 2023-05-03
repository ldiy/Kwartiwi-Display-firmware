/**
 * @file ui_task.c
 * @brief Setup and run the UI
 */

#include <sys/cdefs.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "lvgl.h"
#include "ui.h"
#include "buzzer.h"
#include "tsc2046.h"
#include "ui_task.h"

#define PIXEL_CLOCK_HZ  (10 * 1000 * 1000)  // 10 MHz
#define LVGL_BUFFER_SIZE (UI_TASK_DISPLAY_WIDTH * UI_TASK_DISPLAY_HEIGHT * sizeof(lv_color_t) / 5) // 1/5 of the display area (at least 1/10 is recommended)
#define MAX_TRANSFER_SIZE LVGL_BUFFER_SIZE


static const char *TAG = "ui_task";
static esp_lcd_i80_bus_handle_t i80_bus;
static esp_lcd_panel_io_handle_t io_handle;
static esp_lcd_panel_handle_t panel_handle;
static lv_disp_drv_t disp_drv;
static lv_disp_draw_buf_t disp_buf;
static lv_indev_drv_t buttons_indev_drv;
static lv_indev_drv_t touch_indev_drv;
static esp_timer_handle_t lvgl_periodic_timer;
static bool use_raw_touch_input = false;

// Function prototypes
static void init_display(void);
static void init_lvgl(void);
static void free_display(void);
static void free_lvgl(void);
static void init_buttons(void);
static void display_set_backlight(bool on);
static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map);
static bool color_trans_done_cb(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx);
static void lvgl_buttons_read_cb(lv_indev_drv_t *drv, lv_indev_data_t *data);
static void lvgl_buttons_feedback_cb(lv_indev_drv_t *drv, uint8_t event);
static void lvgl_touch_read_cb(lv_indev_drv_t *drv, lv_indev_data_t *data);
static void lvgl_touch_feedback_cb(lv_indev_drv_t *drv, uint8_t event);
static void lvgl_tick_task(void *arg);

/**
 * @brief Run the UI task
 *
 * This task initializes the display, input buttons, and LVGL, and then runs the UI.
 *
 * @note This task must be pinned to a core.
 * @note lvgl functions should only be called from this task.
 *
 * @param pvParameters unused
 */
_Noreturn void ui_task(void *pvParameters) {
    // Initialize the display
    init_display();

    // Initialize the buttons
    init_buttons();

    // Initialize LVGL
    init_lvgl();

    // Initialize the UI
    ui_init();

    // Set the backlight on
    display_set_backlight(true);

    for(;;) {
        vTaskDelay(pdMS_TO_TICKS(10));
        lv_task_handler();
    }

    // Free resources
    free_display();
    free_lvgl();

    vTaskDelete(NULL);
}

/**
 * @brief Initializes the lcd display
 *
 * This function will configure the i80 bus, panel io, panel settings and backlight.
 * @note This function should only be called from the UI task.
 * @note The backlight off by default, use display_set_backlight() to turn it on.
 * @note The allocated resources can be freed with free_display(), if the display is no longer needed.
 * @uses i80_bus, io_handle, panel_handle
 */
static void init_display(void) {
    ESP_LOGI(TAG, "Initializing display");

    // Set up the I8080 bus
    esp_lcd_i80_bus_config_t bus_config = {
            .clk_src = LCD_CLK_SRC_DEFAULT,
            .dc_gpio_num = UI_TASK_PIN_NUM_LCD_DC,
            .wr_gpio_num = UI_TASK_PIN_NUM_LCD_WR,
            .data_gpio_nums = {
                    UI_TASK_PIN_NUM_LCD_DATA0,
                    UI_TASK_PIN_NUM_LCD_DATA1,
                    UI_TASK_PIN_NUM_LCD_DATA2,
                    UI_TASK_PIN_NUM_LCD_DATA3,
                    UI_TASK_PIN_NUM_LCD_DATA4,
                    UI_TASK_PIN_NUM_LCD_DATA5,
                    UI_TASK_PIN_NUM_LCD_DATA6,
                    UI_TASK_PIN_NUM_LCD_DATA7,
            },
            .bus_width = 8,
            .max_transfer_bytes = MAX_TRANSFER_SIZE,
            .psram_trans_align = 64,
            .sram_trans_align = 4,
    };
    ESP_ERROR_CHECK(esp_lcd_new_i80_bus(&bus_config, &i80_bus));

    // Set up the I8080 IO
    esp_lcd_panel_io_i80_config_t io_config = {
            .cs_gpio_num = UI_TASK_PIN_NUM_LCD_CS,
            .pclk_hz = PIXEL_CLOCK_HZ,
            .trans_queue_depth = 10,
            .dc_levels = {
                    .dc_idle_level = 0,
                    .dc_cmd_level = 0,
                    .dc_dummy_level = 0,
                    .dc_data_level = 1,
            },
            .lcd_cmd_bits = 8,
            .lcd_param_bits = 8,
            .on_color_trans_done = color_trans_done_cb,
            .user_ctx = &disp_drv
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(i80_bus, &io_config, &io_handle));

    // Set up the display panel
    esp_lcd_panel_dev_config_t panel_config = {
            .reset_gpio_num = UI_TASK_PIN_NUM_LCD_RST,
            .rgb_endian = LCD_RGB_ENDIAN_BGR,
            .bits_per_pixel = 16,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));

    // Set the RD pin high as it is not used
    ESP_ERROR_CHECK(gpio_set_direction(UI_TASK_PIN_NUM_LCD_RD, GPIO_MODE_OUTPUT));
    gpio_set_level(UI_TASK_PIN_NUM_LCD_RD, 1);

    // Set the backlight pin as output
    ESP_ERROR_CHECK(gpio_set_direction(UI_TASK_PIN_NUM_LCD_BACKLIGHT, GPIO_MODE_OUTPUT));
    display_set_backlight(false); // Turn off the backlight, as the display is not yet initialized

    // Initialize the display
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, false));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
}

/**
 * @brief Frees the display resources
 *
 * @uses i80_bus, io_handle, panel_handle
 */
static void free_display(void) {
    ESP_LOGI(TAG, "Freeing display resources");
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, false));
    ESP_ERROR_CHECK(esp_lcd_panel_del(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_io_del(io_handle));
    ESP_ERROR_CHECK(esp_lcd_del_i80_bus(i80_bus));
}

/**
 * @brief Initializes LVGL
 *
 * This function will initialize LVGL, allocate the necessary buffers and configure the input devices.
 * The 3 buttons will be configured as an encoder input (left, right and enter).
 *
 * @note This function should only be called from the UI task.
 * @note The allocated resources can be freed with free_lvgl(), if LVGL is no longer needed.
 * @uses disp_buf, indev_drv, buttons_indev, lvgl_periodic_timer
 */
static void init_lvgl(void) {
    lv_color_t *buf1;
    lv_color_t *buf2;
    lv_indev_t *buttons_indev;

    ESP_LOGI(TAG, "Initializing LVGL");
    lv_init();
    buf1 = heap_caps_malloc(LVGL_BUFFER_SIZE, MALLOC_CAP_DMA);
    buf2 = heap_caps_malloc(LVGL_BUFFER_SIZE, MALLOC_CAP_DMA);
    if (buf1 == NULL || buf2 == NULL) {
        ESP_LOGE(TAG, "Failed to allocate LVGL buffers");
        abort();
    }
    ESP_LOGD(TAG, "Allocated LVGL buffers at %p and %p", buf1, buf2);
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, LVGL_BUFFER_SIZE / sizeof(lv_color_t));
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = lvgl_flush_cb;
    disp_drv.user_data = panel_handle;
    disp_drv.hor_res = UI_TASK_DISPLAY_WIDTH;
    disp_drv.ver_res = UI_TASK_DISPLAY_HEIGHT;
    disp_drv.rotated = 0;
    lv_disp_drv_register(&disp_drv);

    // Register 3 buttons (left, right and enter) as an encoder input device
    lv_indev_drv_init(&buttons_indev_drv);
    buttons_indev_drv.type = LV_INDEV_TYPE_ENCODER;
    buttons_indev_drv.read_cb = lvgl_buttons_read_cb;
    buttons_indev_drv.feedback_cb = lvgl_buttons_feedback_cb;
    buttons_indev = lv_indev_drv_register(&buttons_indev_drv);

    // Create the default group and assign the button input device to it
    lv_group_t *group = lv_group_create();
    lv_group_set_default(group);
    lv_indev_set_group(buttons_indev, group);

    // Register the touchscreens as input devices
    lv_indev_drv_init(&touch_indev_drv);
    touch_indev_drv.type = LV_INDEV_TYPE_POINTER;
    touch_indev_drv.read_cb = lvgl_touch_read_cb;
    touch_indev_drv.feedback_cb = lvgl_touch_feedback_cb;
    lv_indev_drv_register(&touch_indev_drv);

    // Create a periodic timer to call lvg_tick_task
    const esp_timer_create_args_t periodic_timer_args = {
            .callback = &lvgl_tick_task,
            .name = "lvgl_tick"
    };
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &lvgl_periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_periodic_timer, UI_TASK_LVGL_TICK_PERIOD_MS * 1000));
}

/**
 * @brief Frees the LVGL resources, and de-initializes LVGL
 *
 * @uses disp_buf, lvgl_periodic_timer
 */
static void free_lvgl(void) {
    ESP_LOGI(TAG, "Freeing LVGL resources");
    esp_timer_stop(lvgl_periodic_timer);
    esp_timer_delete(lvgl_periodic_timer);
    heap_caps_free(disp_buf.buf1);
    heap_caps_free(disp_buf.buf2);
    lv_deinit();
}

/**
 * @brief Initializes the buttons
 *
 * @todo Move this to a separate button driver?
 *
 * Configures the 3 buttons as input, with internal pull-ups.
 */
static void init_buttons(void) {
    gpio_set_direction(UI_TASK_PIN_NUM_BUTTON_LEFT, GPIO_MODE_INPUT);
    gpio_set_pull_mode(UI_TASK_PIN_NUM_BUTTON_LEFT, GPIO_PULLUP_ONLY);
    gpio_set_direction(UI_TASK_PIN_NUM_BUTTON_RIGHT, GPIO_MODE_INPUT);
    gpio_set_pull_mode(UI_TASK_PIN_NUM_BUTTON_RIGHT, GPIO_PULLUP_ONLY);
    gpio_set_direction(UI_TASK_PIN_NUM_BUTTON_ENTER, GPIO_MODE_INPUT);
    gpio_set_pull_mode(UI_TASK_PIN_NUM_BUTTON_ENTER, GPIO_PULLUP_ONLY);
}

/**
 * @brief Set the backlight on or off
 *
 * @param[in] on true to turn the backlight on, false to turn it off
 */
static void display_set_backlight(bool on) {
    ESP_LOGI(TAG, "Setting backlight %s", on ? "on" : "off");
    gpio_set_level(UI_TASK_PIN_NUM_LCD_BACKLIGHT, on ? 1 : 0);
}

/**
 * @brief LVGL flush callback
 *
 * Write the color data to the display.
 * lv_disp_flush_ready() must be called when the color data has been transferred.
 *
 * @param[in] drv
 * @param[in] area
 * @param[in] color_map
 */
static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map) {
    esp_lcd_panel_draw_bitmap(panel_handle, area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_map);
}

/**
 * @brief esp-lcd panel IO callback, invoked when the color data has been transferred
 *
 * Notify LVGL that the color data has been transferred
 *
 * @param[in] panel_io LCD panel IO handle
 * @param[in] edata Panel IO event data, fed by driver
 * @param[in] user_ctx User data, passed from `esp_lcd_panel_io_xxx_config_t`
 * @return Whether a high priority task has been waken up by this function
 */
static bool color_trans_done_cb(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx) {
    // Notify LVGL that the color data has been transferred
    lv_disp_flush_ready(&disp_drv);
    return false;
}

/**
 * @brief LVGL button indev callback.
 *
 * This function is called periodically by LVGL to read the status of the buttons.
 *
 * @param[in] drv
 * @param[out] data
 */
static void lvgl_buttons_read_cb(lv_indev_drv_t *drv, lv_indev_data_t *data) {
    static bool enter_last_state = 0;
    static bool left_last_state = 0;
    static bool right_last_state = 0;

    // Read the buttons
    bool enter_state = gpio_get_level(UI_TASK_PIN_NUM_BUTTON_ENTER) == 0;
    bool left_state = gpio_get_level(UI_TASK_PIN_NUM_BUTTON_LEFT) == 0;
    bool right_state = gpio_get_level(UI_TASK_PIN_NUM_BUTTON_RIGHT) == 0;

    // Set the data
    data->state = LV_INDEV_STATE_REL;
    if (enter_state && !enter_last_state) {
        ESP_LOGD(TAG, "Enter key pressed");
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_KEY_ENTER;
    } else if (left_state && !left_last_state) {
        ESP_LOGD(TAG, "Left key pressed");
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_KEY_LEFT;
    } else if (right_state && !right_last_state) {
        ESP_LOGD(TAG, "Right key pressed");
        data->state = LV_INDEV_STATE_PR;
        data->key = LV_KEY_RIGHT;
    }

    // Save the last state
    enter_last_state = enter_state;
    left_last_state = left_state;
    right_last_state = right_state;
}

/**
 * @brief LVGL button feedback callback
 *
 * This function is called by LVGL when a event is sent by the buttons input device.
 * Play a short beep when a button is pressed (LV_EVENT_CLICKED).
 *
 * @param[in] drv unused
 * @param[in] event The event code
 */
static void lvgl_buttons_feedback_cb(lv_indev_drv_t *drv, uint8_t event) {
    if ((lv_event_code_t)event == LV_EVENT_CLICKED) {
        buzzer_beep(BUZZER_BEEP_TYPE_SHORT);
    }
}

/**
 * @brief LVGL touchpad indev callback
 *
 * This function is called periodically by LVGL to read the status of the touchscreen.
 * If use_raw_touch_input is true, the raw touch coordinates are used, otherwise the coordinates are calibrated.
 *
 * @uses use_raw_touch_input
 *
 * @param[in] drv
 * @param[out] data
 */
static void lvgl_touch_read_cb(lv_indev_drv_t * drv, lv_indev_data_t*data) {
    static lv_point_t last_point = {0};
    static bool last_state = false;
    tsc2046_data_t tsc2046_data;

    tsc2046_data = tsc2046_read(use_raw_touch_input);

    if (tsc2046_data.state == TSC2046_STATE_PRESSED) {
        last_point.x = (int16_t)tsc2046_data.x;
        last_point.y = (int16_t)tsc2046_data.y;
        if (last_state == false) {
            ESP_LOGD(TAG, "Touch: %d, %d", last_point.x, last_point.y);
        }
        last_state = true;
    } else {
        last_state = false;
    }
    data->point = last_point;
    data->state = last_state ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}

/**
 * @brief LVGL touchscreen feedback callback
 *
 * This function is called by LVGL when a event is sent by the touchpad input device.
 * Play a short beep when a the touchscreen is pressed (LV_EVENT_PRESSED).
 *
 * @todo Merge with lvgl_buttons_feedback_cb?
 *
 * @param[in] drv
 * @param[in] event
 */
static void lvgl_touch_feedback_cb(lv_indev_drv_t * drv, uint8_t event) {
    if ((lv_event_code_t)event == LV_EVENT_PRESSED) {
        buzzer_beep(BUZZER_BEEP_TYPE_SHORT);
    }
}

/**
 * @brief LVGL tick task
 *
 * Increment the LVGL tick
 *
 * @param arg unused
 */
static void lvgl_tick_task(void *arg) {
    lv_tick_inc(UI_TASK_LVGL_TICK_PERIOD_MS);
}

/**
 * @brief Calibrate the touchscreen
 *
 * Calibrate the touchscreen using the given points. At least 3 points are required.
 * The index of the points must match. For example, the first point in src_points corresponds to the first point in cal_points.
 * The calibration data is not saved to flash, so it will be lost after a reboot.
 * To save the calibration data to flash, use ui_task_store_tp_cal().
 *
 * @todo Return error code, so that the ui can display an error message
 *
 * @param[in] src_points The raw touchscreen coordinates
 * @param[in] cal_points The target coordinates
 * @param[in] len The number of points
 */
void ui_task_calibrate_tp(lv_point_t src_points[], lv_point_t cal_points[], size_t len) {
    tsc2046_cal_data_point_t cal_data[len];

    if (len < 3) {
        ESP_LOGE(TAG, "At least 3 calibration points are required");
        return;
    }

    for (size_t i = 0; i < len; i++) {
        cal_data[i].x_raw = (uint16_t)src_points[i].x;
        cal_data[i].y_raw = (uint16_t)src_points[i].y;
        cal_data[i].x_cal = (uint16_t)cal_points[i].x;
        cal_data[i].y_cal = (uint16_t)cal_points[i].y;

        ESP_LOGD(TAG, "Calibration point %d: %d, %d -> %d, %d", i, cal_data[i].x_raw, cal_data[i].y_raw, cal_data[i].x_cal, cal_data[i].y_cal);
    }

    if (tsc2046_calibrate(cal_data, len) != ESP_OK) {
        ESP_LOGE(TAG, "Calibration failed");
    }
}

/**
 * @brief Store the current touchscreen calibration data to flash
 */
void ui_task_store_tp_cal(void) {
    tsc2046_store_cal_data();
}

/**
 * @brief Use raw or calibrated touchscreen data
 *
 * @param[in] raw Use raw data if true, calibrated data if false
 */
void ui_task_use_raw_tp_data(bool raw) {
    use_raw_touch_input = raw;
}