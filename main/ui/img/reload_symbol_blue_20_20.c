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

#ifndef LV_ATTRIBUTE_IMG_RELOAD_SYMBOL_BLUE_20_20
#define LV_ATTRIBUTE_IMG_RELOAD_SYMBOL_BLUE_20_20
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_RELOAD_SYMBOL_BLUE_20_20 uint8_t reload_symbol_blue_20_20_map[] = {
  0xfe, 0xfd, 0xfc, 0xff, 	/*Color of index 0*/
  0xf0, 0xce, 0xbb, 0xff, 	/*Color of index 1*/
  0xe4, 0x9d, 0x69, 0xff, 	/*Color of index 2*/
  0xe0, 0x85, 0x19, 0xff, 	/*Color of index 3*/

  0x00, 0x05, 0xbe, 0x50, 0x1a, 
  0x00, 0x6f, 0xff, 0xf9, 0x3f, 
  0x01, 0xff, 0xff, 0xff, 0xbf, 
  0x07, 0xff, 0xff, 0xff, 0xff, 
  0x1f, 0xfe, 0x85, 0xff, 0xff, 
  0x2f, 0xf4, 0x00, 0x2f, 0xff, 
  0x7f, 0xd0, 0x00, 0xbf, 0xff, 
  0x7f, 0xc0, 0x02, 0xff, 0xff, 
  0xbf, 0x40, 0x01, 0x55, 0x55, 
  0xff, 0x40, 0x00, 0x00, 0x00, 
  0xff, 0x00, 0x00, 0x00, 0x00, 
  0xbf, 0x40, 0x00, 0x00, 0x54, 
  0x7f, 0xc0, 0x00, 0x03, 0xfe, 
  0x7f, 0xd0, 0x00, 0x07, 0xfd, 
  0x2f, 0xf4, 0x00, 0x1f, 0xf8, 
  0x1f, 0xff, 0x51, 0xff, 0xf4, 
  0x07, 0xff, 0xff, 0xff, 0xd0, 
  0x01, 0xff, 0xff, 0xff, 0x40, 
  0x00, 0x6f, 0xff, 0xf9, 0x00, 
  0x00, 0x05, 0xbe, 0x50, 0x00, 
};

const lv_img_dsc_t reload_symbol_blue_20_20 = {
  .header.cf = LV_IMG_CF_INDEXED_2BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 20,
  .header.h = 20,
  .data_size = 116,
  .data = reload_symbol_blue_20_20_map,
};