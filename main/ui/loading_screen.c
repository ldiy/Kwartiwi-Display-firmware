/**
 * @file loading_screen.c
 * @brief Loading screen
 */

#include "lvgl.h"
#include "loading_screen.h"

lv_obj_t * loading_screen;
static lv_obj_t * logo_img;
static lv_obj_t * spinner;

LV_IMG_DECLARE(kwartiwi_logo_240);

/**
 * @brief Initialize the loading screen
 */
void loading_screen_init(void) {
    loading_screen = lv_obj_create(NULL);
    lv_obj_clear_flag(loading_screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(loading_screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Logo
    logo_img = lv_img_create(loading_screen);
    lv_img_set_src(logo_img, &kwartiwi_logo_240);
    lv_obj_set_width(logo_img, LV_SIZE_CONTENT);
    lv_obj_set_height(logo_img, LV_SIZE_CONTENT);
    lv_obj_set_x(logo_img, 0);
    lv_obj_set_y(logo_img, -20);
    lv_obj_set_align(logo_img, LV_ALIGN_CENTER);
    lv_obj_clear_flag(logo_img, LV_OBJ_FLAG_SCROLLABLE);

    // Spinner
    spinner = lv_spinner_create(loading_screen, 1000, 90);
    lv_obj_set_width(spinner, 40);
    lv_obj_set_height(spinner, 40);
    lv_obj_set_x(spinner, 0);
    lv_obj_set_y(spinner, -40);
    lv_obj_set_align(spinner, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(spinner, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_width(spinner, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(spinner, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
}

/**
 * @brief Destruct the loading screen
 */
void loading_screen_deinit(void) {
    lv_obj_del(loading_screen);
}