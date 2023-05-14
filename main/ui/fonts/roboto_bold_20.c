/*******************************************************************************
 * Size: 20 px
 * Bpp: 2
 * Opts: 
 ******************************************************************************/

#include "lvgl.h"


#ifndef ROBOTO_BOLD_20
#define ROBOTO_BOLD_20 1
#endif

#if ROBOTO_BOLD_20

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0057 "W" */
    0xbd, 0x2, 0xf0, 0xf, 0xc7, 0xe0, 0x3f, 0x40,
    0xfc, 0x3e, 0x3, 0xf8, 0xf, 0x83, 0xf0, 0x3f,
    0xc1, 0xf4, 0x2f, 0x7, 0xfc, 0x2f, 0x2, 0xf4,
    0xbf, 0xd3, 0xf0, 0x1f, 0x4f, 0x7d, 0x3f, 0x0,
    0xf8, 0xf2, 0xe3, 0xe0, 0xf, 0xdf, 0x1f, 0x7d,
    0x0, 0xbe, 0xe0, 0xfb, 0xc0, 0x7, 0xfd, 0xf,
    0xfc, 0x0, 0x3f, 0xd0, 0xbf, 0xc0, 0x3, 0xfc,
    0xb, 0xf8, 0x0, 0x3f, 0xc0, 0x7f, 0x40, 0x2,
    0xf8, 0x3, 0xf0, 0x0,

    /* U+006B "k" */
    0xfc, 0x0, 0xf, 0xc0, 0x0, 0xfc, 0x0, 0xf,
    0xc0, 0x0, 0xfc, 0x1f, 0xcf, 0xc3, 0xf4, 0xfc,
    0xfd, 0xf, 0xef, 0x80, 0xff, 0xf0, 0xf, 0xff,
    0x40, 0xff, 0xfc, 0xf, 0xcb, 0xe0, 0xfc, 0x3f,
    0x4f, 0xc1, 0xfc, 0xfc, 0xb, 0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 280, .box_w = 18, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 171, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x14
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 87, .range_length = 21, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 2, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t roboto_bold_20 = {
#else
lv_font_t roboto_bold_20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if ROBOTO_BOLD_20*/

