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

#ifndef LV_ATTRIBUTE_IMG_CONNECTED_SYMBOL_NC_14_14
#define LV_ATTRIBUTE_IMG_CONNECTED_SYMBOL_NC_14_14
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_CONNECTED_SYMBOL_NC_14_14 uint8_t connected_symbol_nc_14_14_map[] = {
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0xf8, 0xff, 	/*Color of index 1*/
  0x00, 0x00, 0x93, 0xff, 	/*Color of index 2*/
  0x00, 0x00, 0x4c, 0xff, 	/*Color of index 3*/

  0x00, 0x00, 0x2a, 0x90, 
  0x00, 0x0b, 0x55, 0x60, 
  0x00, 0x05, 0x55, 0x60, 
  0x00, 0x0d, 0x55, 0x60, 
  0x00, 0x09, 0x55, 0x60, 
  0x00, 0x26, 0xd5, 0x40, 
  0x27, 0x28, 0x95, 0xc0, 
  0x35, 0xc2, 0x6d, 0x80, 
  0x15, 0x72, 0x80, 0x00, 
  0x95, 0x5c, 0x00, 0x00, 
  0x95, 0x57, 0x00, 0x00, 
  0x95, 0x55, 0x00, 0x00, 
  0x95, 0x5e, 0x00, 0x00, 
  0x6a, 0x80, 0x00, 0x00, 
};

const lv_img_dsc_t connected_symbol_nc_14_14 = {
  .header.cf = LV_IMG_CF_INDEXED_2BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 14,
  .header.h = 14,
  .data_size = 72,
  .data = connected_symbol_nc_14_14_map,
};