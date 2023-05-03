#ifndef UI_TASK_H
#define UI_TASK_H

#include <sys/cdefs.h>
#include "lvgl.h"

#define UI_TASK_PIN_NUM_LCD_DC          7
#define UI_TASK_PIN_NUM_LCD_WR          15
#define UI_TASK_PIN_NUM_LCD_RD          16
#define UI_TASK_PIN_NUM_LCD_CS          48
#define UI_TASK_PIN_NUM_LCD_RST         8
#define UI_TASK_PIN_NUM_LCD_DATA0       47
#define UI_TASK_PIN_NUM_LCD_DATA1       21
#define UI_TASK_PIN_NUM_LCD_DATA2       14
#define UI_TASK_PIN_NUM_LCD_DATA3       13
#define UI_TASK_PIN_NUM_LCD_DATA4       12
#define UI_TASK_PIN_NUM_LCD_DATA5       11
#define UI_TASK_PIN_NUM_LCD_DATA6       10
#define UI_TASK_PIN_NUM_LCD_DATA7       9
#define UI_TASK_PIN_NUM_LCD_BACKLIGHT   4
#define UI_TASK_PIN_NUM_LCD_TE          38
#define UI_TASK_PIN_NUM_BUTTON_ENTER    0
#define UI_TASK_PIN_NUM_BUTTON_LEFT     5
#define UI_TASK_PIN_NUM_BUTTON_RIGHT    6

#define UI_TASK_DISPLAY_WIDTH  240
#define UI_TASK_DISPLAY_HEIGHT 320

#define UI_TASK_LVGL_TICK_PERIOD_MS 1

// Function prototypes
_Noreturn void ui_task(void *pvParameters);
void ui_task_calibrate_tp(lv_point_t src_points[], lv_point_t cal_points[], size_t len);
void ui_task_store_tp_cal(void);
void ui_task_use_raw_tp_data(bool raw);

#endif //UI_TASK_H
