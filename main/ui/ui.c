#include "esp_log.h"
#include "lvgl.h"
#include "data_manager.h"
#include "ui.h"

#define CHECK_INIT_PERIOD_MS 100
#define CHECK_INIT_TIMEOUT_MS 10000

static const char * TAG = "ui";
static bool initialized = false;
static lv_timer_t * loading_screen_timer;

// Function prototypes
static void load_main_screen(lv_timer_t * timer);


/**
 * @brief Initialize the UI
 *
 * Show the loading screen until the initialization is complete (ui_set_initialized()) or the timeout is reached, then show the main screen
 *
 * @note The data manager must be initialized before calling this function
 */
void ui_init(void) {
    ESP_LOGI(TAG, "Initializing UI");

    main_screen_init();

    // Show the loading screen
    loading_screen_init();
    lv_disp_load_scr(loading_screen);

    // Display the main screen when everything is loaded or the timeout is reached
    loading_screen_timer = lv_timer_create(load_main_screen, CHECK_INIT_PERIOD_MS, NULL);
}

/**
 * @brief Set the initialization status
 *
 * @param[in] value true to set the initialization status to true, false otherwise
 */
void ui_set_initialized(bool value) {
    initialized = value;
}

/**
 * @brief Load the main screen after the initialization is complete or the timeout is reached
 *
 * This function is called periodically by a timer every CHECK_INIT_PERIOD_MS milliseconds
 *
 * @note The main screen must be initialized before calling this function
 *
 * @param timer
 */
static void load_main_screen(lv_timer_t * timer) {
    static uint16_t counter = 0;
    counter++;

    if (initialized || counter * CHECK_INIT_PERIOD_MS > CHECK_INIT_TIMEOUT_MS) {
        lv_timer_del(loading_screen_timer);
        lv_disp_load_scr(main_screen);
        loading_screen_deinit();
        counter = 0;
        return;
    }
}
