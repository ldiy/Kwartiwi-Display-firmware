#ifdef __has_include
#if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_CAL_CROSS
#define LV_ATTRIBUTE_IMG_CAL_CROSS
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_CAL_CROSS uint8_t cal_cross_map[] = {
0xff, 0xff, 0xff, 0xff, 	/*Color of index 0*/
0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0xff, 0xff, 0xff, 0xff, 0x80,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00,
};

const lv_img_dsc_t cal_cross = {
        .header.cf = LV_IMG_CF_INDEXED_1BIT,
        .header.always_zero = 0,
        .header.reserved = 0,
        .header.w = 33,
        .header.h = 33,
        .data_size = 173,
        .data = cal_cross_map,
};
