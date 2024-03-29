/*******************************************************************************
 * Size: 70 px
 * Bpp: 4
 * Opts:
 ******************************************************************************/

#include "lvgl.h"

#ifndef ROBOTO_BOLD_70
#define ROBOTO_BOLD_70 1
#endif

#if ROBOTO_BOLD_70

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
        /* U+002E "." */
        0x0, 0xe1, 0x0, 0xfc, 0x55, 0xfd, 0xfd, 0x0,
        0x18, 0xf5, 0x40, 0x21, 0x7d, 0x10, 0x6, 0x80,
        0x7c, 0x5a, 0xc, 0x20, 0x1f, 0x8c, 0xde, 0x1,
        0xfe, 0x53, 0x0, 0xff, 0x9, 0x0, 0x7f, 0x8a,
        0xc0, 0x3f, 0x85, 0x4d, 0x80, 0x3f, 0x58, 0x2,
        0x5c, 0x3, 0x86, 0x94, 0x2, 0x8e, 0xa8, 0x85,
        0xf2, 0x80, 0x0,

        /* U+0030 "0" */
        0x0, 0xff, 0xe0, 0x9a, 0xb3, 0xb9, 0x94, 0xc0,
        0x3f, 0xf9, 0x6d, 0x7f, 0x95, 0x31, 0x9, 0xac,
        0xfc, 0x61, 0x0, 0xff, 0xe2, 0xbf, 0x4a, 0x0,
        0x7f, 0x8e, 0x7a, 0x0, 0x3f, 0xf8, 0x45, 0x90,
        0x20, 0x1f, 0xfc, 0x37, 0xd2, 0x0, 0xff, 0x8f,
        0xc, 0x3, 0xff, 0x8c, 0x5a, 0x80, 0x1f, 0xc5,
        0xa2, 0x1, 0xff, 0xc9, 0xb3, 0x0, 0xfd, 0xe2,
        0x1, 0xff, 0xcb, 0xd0, 0xf, 0xa0, 0x80, 0x3f,
        0xf9, 0x83, 0x20, 0x1c, 0x4e, 0x1, 0xff, 0x23,
        0x31, 0x0, 0x3f, 0xe6, 0x30, 0xd, 0x60, 0x1f,
        0xe6, 0xeb, 0x99, 0x5f, 0xb8, 0x7, 0xfa, 0x40,
        0x33, 0x0, 0x7f, 0x44, 0x88, 0x7, 0x44, 0x80,
        0x7f, 0x28, 0x80, 0x14, 0x3, 0xf8, 0xdc, 0x3,
        0xf3, 0x28, 0x7, 0xf3, 0x0, 0x3c, 0x3, 0xfa,
        0x0, 0x3f, 0xd0, 0x1, 0xfd, 0x60, 0x4, 0x0,
        0xfc, 0x28, 0x1, 0xfe, 0x22, 0x0, 0x7e, 0x30,
        0x11, 0x0, 0x7e, 0x40, 0xf, 0xfe, 0x2, 0x80,
        0x7f, 0x1a, 0x80, 0x7f, 0x68, 0x7, 0xff, 0x3,
        0x40, 0x3f, 0x94, 0x80, 0x3f, 0x88, 0x3, 0xff,
        0x80, 0xc0, 0x1f, 0xdd, 0xc0, 0xf, 0xe6, 0x0,
        0xff, 0xe0, 0x10, 0x7, 0xf1, 0x10, 0x3, 0xf8,
        0x40, 0x3f, 0xf9, 0x4c, 0x20, 0x1f, 0xfc, 0xa1,
        0x0, 0xfe, 0x10, 0xf, 0xff, 0xc3, 0x80, 0x7f,
        0xf5, 0xc, 0x3, 0xff, 0xfe, 0x1, 0xff, 0xff,
        0x0, 0xff, 0xff, 0x80, 0x7f, 0xf0, 0x5c, 0x3,
        0xff, 0xa8, 0x60, 0x1f, 0xff, 0x71, 0x10, 0x7,
        0xf0, 0x80, 0x7f, 0xf0, 0x4, 0x3, 0xf9, 0xc8,
        0x3, 0xff, 0xa8, 0x3c, 0x1, 0xfc, 0xc0, 0x1f,
        0xfc, 0x2, 0x0, 0xfe, 0x22, 0x0, 0x7f, 0x10,
        0x7, 0xff, 0x1, 0x80, 0x3f, 0xb9, 0x40, 0x3f,
        0xb0, 0x3, 0xff, 0x81, 0xa0, 0x1f, 0xca, 0x22,
        0x0, 0xfc, 0x80, 0x1f, 0xfc, 0x5, 0x0, 0xfe,
        0x30, 0x40, 0xf, 0xe5, 0x0, 0xff, 0x11, 0x0,
        0x3f, 0x18, 0x3, 0xc0, 0x3f, 0xa4, 0x3, 0xfd,
        0x60, 0x1f, 0xd6, 0x0, 0x51, 0x0, 0xfc, 0x70,
        0x1, 0xf9, 0x58, 0x3, 0xf9, 0x80, 0x26, 0x0,
        0xfe, 0x79, 0x10, 0xe, 0x7a, 0x0, 0xfe, 0x51,
        0x0, 0xa4, 0x3, 0xfc, 0xdd, 0x73, 0x2a, 0xf8,
        0x0, 0xff, 0x48, 0x6, 0x18, 0x0, 0xff, 0x91,
        0x98, 0xa0, 0x1f, 0xf2, 0x98, 0x7, 0x39, 0x80,
        0x7f, 0xf3, 0x6, 0xc0, 0x3e, 0xe1, 0x0, 0xff,
        0xe5, 0xe8, 0x80, 0x7c, 0x58, 0x20, 0x1f, 0xfc,
        0x9b, 0x30, 0xf, 0xe2, 0xf3, 0x0, 0xff, 0xe3,
        0x16, 0x20, 0x7, 0xfc, 0x39, 0x22, 0x1, 0xff,
        0xc3, 0x7d, 0x30, 0xf, 0xfe, 0x13, 0x74, 0xa0,
        0x7, 0xf8, 0xe3, 0xa0, 0x3, 0xff, 0x8c, 0xd7,
        0xf9, 0x53, 0x11, 0x56, 0x7e, 0x38, 0x80, 0x7f,
        0x0,

        /* U+0031 "1" */
        0x0, 0xff, 0xe3, 0xad, 0xfb, 0x0, 0x7f, 0xf1,
        0x12, 0xbe, 0x90, 0x3, 0xff, 0x86, 0x71, 0xd6,
        0xa0, 0x1f, 0xfc, 0x31, 0x7d, 0xc7, 0x10, 0xf,
        0xfe, 0x10, 0xb6, 0x74, 0x10, 0x7, 0xff, 0xd,
        0x6b, 0xa4, 0xc0, 0x3f, 0xf8, 0x67, 0x3d, 0x4a,
        0x1, 0xff, 0xc4, 0x3d, 0xc6, 0x10, 0xf, 0xfe,
        0x33, 0x90, 0x7, 0xff, 0xfc, 0x3, 0xff, 0x98,
        0x93, 0xce, 0x1, 0xff, 0xc4, 0x5a, 0xeb, 0x61,
        0x0, 0xff, 0xe0, 0x8b, 0x5f, 0xd2, 0x88, 0x7,
        0xff, 0x9, 0xb3, 0xa5, 0x0, 0x3f, 0xf8, 0xc4,
        0x60, 0x1f, 0xff, 0xf0, 0xf, 0xff, 0xf8, 0x7,
        0xff, 0xfc, 0x3, 0xff, 0xfe, 0x1, 0xff, 0xff,
        0x0, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xc0, 0x3f,
        0xff, 0xe0, 0x1f, 0xff, 0xf0, 0xf, 0xff, 0xf8,
        0x7, 0xff, 0x48,

        /* U+0032 "2" */
        0x0, 0xff, 0xe0, 0x89, 0xab, 0x3b, 0x99, 0x4c,
        0x3, 0xff, 0x98, 0x51, 0xbd, 0x95, 0x31, 0x9,
        0xac, 0xfc, 0x82, 0x0, 0xff, 0xe3, 0x1d, 0xeb,
        0x90, 0x7, 0xf8, 0xdf, 0x6d, 0x0, 0x3f, 0xf8,
        0x43, 0x38, 0x80, 0x1f, 0xfc, 0x44, 0xb9, 0x0,
        0xff, 0xe0, 0x16, 0x30, 0x7, 0xff, 0x21, 0xb4,
        0x40, 0x3f, 0x8b, 0x8, 0x3, 0xff, 0x94, 0x58,
        0x1, 0xf8, 0x70, 0x40, 0x3f, 0xf9, 0x85, 0x40,
        0x1f, 0x50, 0x80, 0x7f, 0xf3, 0x95, 0x0, 0x39,
        0x90, 0x3, 0xfe, 0x35, 0x76, 0x30, 0xf, 0xfe,
        0x7, 0x80, 0x74, 0x0, 0x7f, 0x93, 0x72, 0xa2,
        0x73, 0x50, 0x3, 0xfc, 0x82, 0x1, 0x28, 0x80,
        0x7f, 0x35, 0x90, 0x7, 0x15, 0xa8, 0x7, 0xf9,
        0xc0, 0x2e, 0x0, 0xfe, 0x39, 0x0, 0xfe, 0xa1,
        0x0, 0xfe, 0xf0, 0x9, 0x0, 0x3f, 0xbc, 0x3,
        0xfe, 0x60, 0xf, 0xe5, 0x0, 0x20, 0x7, 0xf1,
        0x18, 0x7, 0xfd, 0x80, 0x1f, 0xc2, 0x0, 0x30,
        0xf, 0xe4, 0x0, 0xff, 0xe0, 0x28, 0x7, 0xf1,
        0x80, 0x3c, 0x3, 0xfb, 0xc0, 0x3f, 0xf8, 0x2,
        0x1, 0xfc, 0x60, 0x10, 0x8f, 0xf1, 0x0, 0x7f,
        0xf0, 0x4, 0x3, 0xf9, 0x80, 0x11, 0xdd, 0xfc,
        0x80, 0x1f, 0xfc, 0x5, 0x0, 0xfe, 0x20, 0xf,
        0xfe, 0x6e, 0x0, 0x7f, 0x60, 0x7, 0xff, 0x35,
        0x80, 0x3f, 0x90, 0x3, 0xff, 0x98, 0xe2, 0x1,
        0xf9, 0x44, 0x3, 0xff, 0x96, 0x50, 0x1, 0xfd,
        0x20, 0x1f, 0xfc, 0xce, 0x0, 0xfe, 0x33, 0x0,
        0x7f, 0xf2, 0xe0, 0xc0, 0x3f, 0xbc, 0x3, 0xff,
        0x96, 0xae, 0x1, 0xfc, 0xc6, 0x1, 0xff, 0xca,
        0x3a, 0x0, 0xfe, 0x29, 0x0, 0xff, 0xe5, 0x16,
        0x80, 0x7f, 0xb8, 0x3, 0xff, 0x94, 0x3e, 0x20,
        0x1f, 0xd2, 0x60, 0x1f, 0xfc, 0x91, 0xc2, 0x0,
        0xfe, 0x66, 0x0, 0x7f, 0xf2, 0xb4, 0x80, 0x3f,
        0x92, 0x40, 0x3f, 0xf9, 0x56, 0x60, 0x1f, 0xc5,
        0x60, 0x1f, 0xfc, 0xaa, 0x40, 0xf, 0xe2, 0xc0,
        0xf, 0xfe, 0x55, 0x28, 0x7, 0xf0, 0xf8, 0x80,
        0x7f, 0xf2, 0x65, 0x40, 0x3f, 0x87, 0x8, 0x3,
        0xff, 0x93, 0xc, 0x1, 0xfc, 0x3a, 0x40, 0x1f,
        0xfc, 0x97, 0x70, 0x7, 0xfb, 0x4c, 0x3, 0xff,
        0x92, 0xd0, 0x1, 0xfe, 0xb3, 0x0, 0xff, 0xe4,
        0xac, 0x80, 0x7f, 0xad, 0x0, 0x3f, 0xf9, 0x29,
        0x40, 0x1f, 0xea, 0x40, 0xf, 0xfe, 0x4a, 0x58,
        0x7, 0xfa, 0x54, 0x3, 0xff, 0x92, 0x76, 0x1,
        0xfe, 0x96, 0x0, 0xff, 0xe4, 0x96, 0x80, 0x7f,
        0xa1, 0x80, 0x3f, 0xf9, 0x25, 0x82, 0x1, 0xfc,
        0xce, 0x1, 0xff, 0xc9, 0x1f, 0x10, 0xf, 0xf3,
        0x7f, 0xff, 0xf2, 0x20, 0x20, 0x80, 0x3f, 0xff,
        0xe0, 0x1f, 0xff, 0xf0, 0xf, 0xff, 0xf8, 0x7,
        0xff, 0x30,

        /* U+0033 "3" */
        0x0, 0xff, 0xe0, 0x92, 0xb3, 0xb9, 0x95, 0x8,
        0x3, 0xff, 0x94, 0x2f, 0x7f, 0xb5, 0x31, 0x9,
        0xab, 0xde, 0xb6, 0x0, 0xff, 0xe2, 0x95, 0x74,
        0x20, 0x7, 0xf8, 0x52, 0x7e, 0x48, 0x3, 0xff,
        0x82, 0xfa, 0xa0, 0x1f, 0xfc, 0x56, 0xd6, 0x0,
        0xff, 0xb2, 0x0, 0x3f, 0xf9, 0x33, 0x60, 0x1f,
        0xd8, 0x60, 0x1f, 0xfc, 0xb4, 0xc0, 0xf, 0xac,
        0xc0, 0x3f, 0xf9, 0xa7, 0x20, 0x1c, 0xc8, 0x1,
        0xff, 0xcf, 0x63, 0x0, 0xd0, 0x1, 0xff, 0xc0,
        0x46, 0x76, 0x30, 0xf, 0xfe, 0x7, 0x80, 0x4c,
        0x20, 0x1f, 0xe8, 0xfb, 0x98, 0x9c, 0xe6, 0x0,
        0xff, 0x19, 0x0, 0x34, 0x3, 0xf8, 0x71, 0xc0,
        0x3c, 0x33, 0x20, 0xf, 0xf2, 0x80, 0x10, 0x3,
        0xfa, 0xcc, 0x3, 0xf9, 0x94, 0x3, 0xfb, 0x40,
        0x40, 0x3f, 0x85, 0x40, 0x3f, 0xe9, 0x0, 0xfe,
        0x70, 0x31, 0x1f, 0xe4, 0x0, 0xff, 0xe0, 0x18,
        0x7, 0xf1, 0x81, 0x77, 0x7f, 0x50, 0x7, 0xff,
        0xb4, 0xc0, 0x3f, 0xf9, 0x84, 0x1, 0xfc, 0xc0,
        0x1f, 0xfc, 0xc5, 0x0, 0xfe, 0xc0, 0xf, 0xfe,
        0x58, 0xc8, 0x7, 0xf3, 0x0, 0x7f, 0xf2, 0x87,
        0x44, 0x3, 0xf3, 0x88, 0x7, 0xff, 0x20, 0x9f,
        0xcc, 0x3, 0xf1, 0x40, 0x7, 0xff, 0x5, 0xf3,
        0x3b, 0x7b, 0x60, 0x40, 0x3f, 0xbc, 0x3, 0xff,
        0x85, 0xc6, 0x7c, 0x42, 0x1, 0xfe, 0x1c, 0x20,
        0xf, 0xfe, 0x9a, 0x79, 0x80, 0x7f, 0xf4, 0x8a,
        0xac, 0x40, 0x3f, 0xfa, 0x65, 0x84, 0x1, 0xff,
        0xd5, 0x6d, 0x80, 0xf, 0xfe, 0xb3, 0xe0, 0x80,
        0x7f, 0xf5, 0x4f, 0x40, 0x3f, 0xf8, 0x53, 0xff,
        0xed, 0xa6, 0x0, 0xff, 0x1d, 0x0, 0x7f, 0xf2,
        0x9, 0x67, 0x94, 0x3, 0xf9, 0x4c, 0x3, 0xff,
        0x94, 0x34, 0xa0, 0x1f, 0xd0, 0x1, 0xff, 0xcc,
        0xb0, 0xf, 0xe4, 0x10, 0xf, 0xfe, 0x58, 0xb0,
        0x7, 0xf2, 0x0, 0x7f, 0xf3, 0x30, 0x3, 0xfb,
        0x0, 0x3f, 0xf9, 0x8c, 0x1, 0xfc, 0x60, 0x1f,
        0xfc, 0xc1, 0x0, 0xfe, 0x1c, 0xff, 0xfe, 0x10,
        0xf, 0xfe, 0x8, 0x80, 0x7f, 0x9c, 0x3, 0xf8,
        0x80, 0x3f, 0xf8, 0x2a, 0x1, 0xfc, 0x24, 0x1,
        0xfd, 0x40, 0x1f, 0xfc, 0x1d, 0x0, 0xfe, 0x2f,
        0x0, 0xfe, 0x62, 0x0, 0xff, 0x91, 0x0, 0x1f,
        0xd8, 0x80, 0x1f, 0xec, 0x20, 0xf, 0xe3, 0xa0,
        0xf, 0xf2, 0x11, 0x80, 0x7f, 0xe, 0xb8, 0x7,
        0x85, 0xf0, 0x40, 0x3f, 0x94, 0x1, 0x20, 0x1f,
        0xf4, 0x7d, 0xcc, 0x4e, 0x74, 0x0, 0x7f, 0xd0,
        0x0, 0x54, 0x0, 0xff, 0xe0, 0x23, 0x3b, 0x18,
        0x7, 0xff, 0x1, 0xc8, 0x2, 0xa1, 0x0, 0xff,
        0xe7, 0x9c, 0x0, 0x61, 0xd0, 0xf, 0xfe, 0x71,
        0x68, 0x7, 0x8f, 0x8, 0x3, 0xff, 0x96, 0x98,
        0x20, 0x1f, 0x1e, 0xb0, 0x7, 0xff, 0x26, 0x6c,
        0x40, 0x3f, 0xd3, 0x68, 0x1, 0xff, 0xc5, 0x6e,
        0x60, 0xf, 0xfe, 0xa, 0x5e, 0xb9, 0x80, 0x7f,
        0x85, 0x67, 0xe4, 0x40, 0x3f, 0xf8, 0x85, 0x19,
        0xf9, 0x53, 0x10, 0x9a, 0xbe, 0xe5, 0x30, 0x7,
        0xf8,

        /* U+0034 "4" */
        0x0, 0xff, 0xe4, 0xdf, 0xff, 0xf4, 0x80, 0x7f,
        0xf3, 0x95, 0x0, 0x3f, 0xfb, 0x16, 0x1, 0xff,
        0xd8, 0x91, 0x0, 0xff, 0xeb, 0x9b, 0x0, 0x7f,
        0xf6, 0x38, 0x3, 0xff, 0xb0, 0xe4, 0x1, 0xff,
        0xd7, 0x28, 0x0, 0xff, 0xec, 0x48, 0x7, 0xff,
        0x61, 0x90, 0x3, 0xff, 0xae, 0x30, 0x1, 0xff,
        0xd8, 0xb1, 0x0, 0xff, 0xeb, 0xa2, 0x80, 0x7f,
        0xf6, 0x24, 0x3, 0xe1, 0x0, 0xff, 0xe8, 0x41,
        0x0, 0x7d, 0x0, 0x1f, 0xfc, 0xf3, 0x70, 0xf,
        0xa0, 0x80, 0x3f, 0xf9, 0xfe, 0x1, 0xf1, 0x38,
        0x7, 0xff, 0x3d, 0xcc, 0x3, 0xee, 0x0, 0xff,
        0xe7, 0x94, 0x0, 0x7c, 0xc6, 0x1, 0xff, 0xcf,
        0x90, 0xf, 0x86, 0x0, 0x3f, 0xf9, 0xea, 0x80,
        0x1f, 0x58, 0x80, 0x7f, 0xf3, 0x86, 0xc0, 0x3e,
        0x45, 0x0, 0xff, 0xe7, 0xc0, 0x80, 0x7d, 0x40,
        0x1f, 0xfc, 0xf3, 0x60, 0xf, 0xa0, 0x40, 0x3f,
        0xf9, 0xfc, 0x1, 0xf1, 0xb8, 0x7, 0xff, 0x3e,
        0x8, 0x3, 0xef, 0x0, 0xff, 0xe7, 0x93, 0x80,
        0x7c, 0xe6, 0x1, 0xff, 0xcf, 0xe0, 0xf, 0x86,
        0x0, 0x3f, 0xf9, 0xec, 0x60, 0x1f, 0x50, 0x7,
        0xff, 0x3c, 0x64, 0x3, 0xe5, 0x40, 0xf, 0xfe,
        0x7d, 0x80, 0x7c, 0x36, 0x1, 0xff, 0xcf, 0x45,
        0x0, 0xf8, 0x7b, 0xff, 0xfa, 0xc0, 0x3f, 0x9b,
        0xff, 0x90, 0x28, 0x3, 0xff, 0xb0, 0x22, 0x0,
        0xff, 0xec, 0x8, 0x7, 0xff, 0x68, 0x40, 0x3f,
        0xfb, 0x26, 0x1, 0xff, 0xd9, 0x10, 0xf, 0xfe,
        0xcb, 0x80, 0x7f, 0xf6, 0x6f, 0xff, 0xff, 0x8f,
        0x60, 0x1f, 0xcd, 0xff, 0xc8, 0x1, 0xff, 0xff,
        0x0, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xc0, 0x3f,
        0xff, 0xe0, 0x1f, 0xff, 0xf0, 0xe,

        /* U+0035 "5" */
        0x0, 0xcb, 0xff, 0xff, 0xcf, 0x90, 0xf, 0x10,
        0x7, 0xff, 0x5b, 0x80, 0x3f, 0xfa, 0xc6, 0x1,
        0xff, 0xd6, 0x60, 0xf, 0xfe, 0xb1, 0x0, 0x7f,
        0xf5, 0x84, 0x3, 0xff, 0xaa, 0x40, 0x1f, 0xfd,
        0x61, 0x0, 0xfc, 0x55, 0x5f, 0xfc, 0x80, 0xe,
        0x60, 0xf, 0xcc, 0xab, 0xff, 0xc7, 0x30, 0xe,
        0x20, 0xf, 0xc4, 0x1, 0xff, 0xcd, 0xe0, 0xf,
        0xdc, 0x1, 0xff, 0xcd, 0x20, 0xf, 0xc4, 0x1,
        0xff, 0xcd, 0x70, 0xf, 0xcc, 0x1, 0xff, 0xcd,
        0x20, 0xf, 0xc4, 0x1, 0xff, 0xcd, 0x10, 0xf,
        0xc2, 0x1, 0xff, 0xcc, 0x20, 0xf, 0xc4, 0x1,
        0xff, 0xcd, 0x60, 0xf, 0xc2, 0x0, 0x49, 0xce,
        0xff, 0xb6, 0xdc, 0xc0, 0x3f, 0xf8, 0x2, 0x1,
        0xf9, 0xe3, 0xad, 0x8c, 0x40, 0x22, 0x48, 0xcd,
        0x60, 0xf, 0xf1, 0x0, 0x7e, 0x47, 0x10, 0xf,
        0xf8, 0xa7, 0x8, 0x3, 0xf7, 0x0, 0x7f, 0xf3,
        0xf, 0x50, 0x3, 0xe2, 0x0, 0xff, 0xe7, 0x5a,
        0x0, 0x79, 0x80, 0x3f, 0xf9, 0xf4, 0x20, 0x1c,
        0x40, 0x1f, 0xfc, 0xf1, 0xa0, 0xf, 0xfe, 0x20,
        0xab, 0x3b, 0x20, 0x7, 0xff, 0x1, 0x10, 0x1,
        0xa1, 0x0, 0x3e, 0x3b, 0xea, 0x98, 0x9b, 0xf8,
        0x0, 0xff, 0xbc, 0x3, 0x3d, 0xfe, 0x42, 0x0,
        0x1f, 0x10, 0x3, 0xe7, 0xd1, 0x0, 0xfe, 0x42,
        0x0, 0xf1, 0xbd, 0xfe, 0xc0, 0x7, 0xf8, 0xb4,
        0x3, 0xfc, 0x80, 0x1f, 0xe2, 0x0, 0xff, 0xe0,
        0x1b, 0x0, 0x7f, 0x60, 0x7, 0xff, 0x32, 0xc0,
        0x3f, 0x9c, 0x3, 0xff, 0x98, 0x42, 0x1, 0xf8,
        0x80, 0x3f, 0xf9, 0xaa, 0x1, 0xfc, 0x20, 0x1f,
        0xfc, 0xc1, 0x0, 0xfe, 0x30, 0xf, 0xfe, 0xb0,
        0x80, 0x7f, 0xf3, 0x4, 0x3, 0xfe, 0x11, 0xfe,
        0x0, 0xff, 0xe1, 0x38, 0x7, 0xf0, 0xaf, 0x77,
        0xf3, 0x80, 0x7f, 0xf0, 0x4c, 0x3, 0xf8, 0xc4,
        0x3, 0xfb, 0x40, 0x3f, 0xf8, 0x6, 0x1, 0xfc,
        0x22, 0x50, 0xf, 0xe5, 0x0, 0xff, 0xe0, 0x50,
        0x7, 0xf2, 0x80, 0x90, 0x7, 0xf4, 0x0, 0x7f,
        0x89, 0x80, 0x3f, 0xb4, 0x0, 0xa0, 0x1f, 0xce,
        0xa0, 0x1f, 0xdc, 0x1, 0xfe, 0x70, 0x5, 0x0,
        0x7f, 0xaa, 0x4, 0x3, 0x8f, 0x4c, 0x3, 0xf9,
        0x44, 0x0, 0x4c, 0x1, 0xfe, 0x7e, 0xc9, 0x8a,
        0xdc, 0x20, 0xf, 0xf4, 0x80, 0x68, 0x10, 0xf,
        0xf8, 0xd9, 0xd4, 0x80, 0x3f, 0xe6, 0x30, 0xc,
        0x34, 0x1, 0xff, 0xce, 0x29, 0x0, 0xf2, 0x48,
        0x7, 0xff, 0x30, 0x7c, 0x3, 0xf3, 0x50, 0x7,
        0xff, 0x28, 0xb0, 0x80, 0x3f, 0x97, 0x4c, 0x3,
        0xff, 0x8e, 0xb8, 0x40, 0x1f, 0xf1, 0x65, 0x10,
        0x7, 0xff, 0xc, 0xaa, 0x82, 0x1, 0xff, 0xc2,
        0x5d, 0xb6, 0x10, 0xf, 0xe1, 0x6b, 0xd5, 0x0,
        0xff, 0xe3, 0x24, 0xf7, 0x2e, 0x62, 0x29, 0xbe,
        0xe4, 0xa0, 0x7, 0xf8,

        /* U+0036 "6" */
        0x0, 0xff, 0xe4, 0x9a, 0xb3, 0x1e, 0x4, 0x3,
        0xff, 0x98, 0xb5, 0xbf, 0x95, 0x32, 0x87, 0x20,
        0xf, 0xfe, 0x49, 0xd7, 0xd2, 0x90, 0x7, 0xff,
        0x3c, 0xef, 0x14, 0x3, 0xff, 0xa5, 0x38, 0x80,
        0x1f, 0xfd, 0x23, 0xd6, 0x0, 0xff, 0xe9, 0xa6,
        0x10, 0x7, 0xff, 0x4d, 0x2c, 0x3, 0xff, 0xa8,
        0x76, 0x1, 0xff, 0xc3, 0x12, 0x33, 0x8, 0x7,
        0xff, 0x0, 0x74, 0x3, 0xff, 0x80, 0x4f, 0x7d,
        0xcd, 0xcc, 0x10, 0x7, 0xff, 0x2, 0x84, 0x3,
        0xfc, 0x99, 0xb0, 0x82, 0x1, 0xff, 0xc4, 0x54,
        0x0, 0xfe, 0x1a, 0xb3, 0x0, 0xff, 0xe4, 0x58,
        0x7, 0xf1, 0x7a, 0x80, 0x7f, 0xf2, 0x5c, 0x40,
        0x3f, 0x16, 0x8, 0x7, 0xff, 0x2a, 0x40, 0x3f,
        0xbc, 0x40, 0x3f, 0xf9, 0x4a, 0x20, 0x1f, 0xa0,
        0x80, 0x3f, 0xf9, 0x72, 0x1, 0xf8, 0x5c, 0x3,
        0xff, 0x96, 0x26, 0x1, 0xfa, 0x40, 0x22, 0x7b,
        0xdf, 0xfb, 0x6d, 0xc8, 0x3, 0xfc, 0x80, 0x1f,
        0xcc, 0x7, 0x7b, 0x8, 0x40, 0x11, 0x24, 0x6d,
        0x98, 0x7, 0xec, 0x0, 0xfc, 0x22, 0x9c, 0x40,
        0xf, 0xf9, 0x32, 0x0, 0x3e, 0x40, 0xf, 0xcb,
        0x8c, 0x1, 0xff, 0xc3, 0x7b, 0x0, 0xf1, 0x0,
        0x7e, 0x43, 0x0, 0xff, 0xe2, 0xa5, 0x0, 0x62,
        0x0, 0xff, 0xe8, 0xab, 0x0, 0x4e, 0x1, 0xff,
        0xd2, 0x91, 0x0, 0x18, 0x7, 0xff, 0x4e, 0xc0,
        0x2, 0x1, 0xff, 0xc1, 0x6b, 0xef, 0xeb, 0x50,
        0xf, 0xf9, 0x44, 0x3c, 0x3, 0xfe, 0x3d, 0x94,
        0x10, 0x14, 0xab, 0x0, 0xff, 0x98, 0x3, 0xff,
        0x80, 0x98, 0x40, 0x1f, 0x26, 0x0, 0x7f, 0xac,
        0x4, 0x3, 0xf8, 0x68, 0x3, 0xfc, 0x6e, 0x1,
        0xfc, 0x60, 0x1f, 0xf4, 0x8, 0x7, 0xfd, 0x20,
        0x1f, 0xe3, 0x0, 0xff, 0x18, 0x7, 0xff, 0x0,
        0x54, 0x3, 0xf9, 0x0, 0x3f, 0xf9, 0x98, 0x1,
        0xfd, 0xe2, 0x1, 0xff, 0xcb, 0x20, 0xf, 0xe1,
        0x0, 0xff, 0xe6, 0x38, 0x7, 0xf1, 0xf0, 0x7,
        0xf1, 0x80, 0x7f, 0xf0, 0x44, 0x3, 0xfc, 0x40,
        0x1f, 0xdc, 0x1, 0xff, 0xc1, 0x10, 0xf, 0xf3,
        0x0, 0x7f, 0x18, 0x7, 0xff, 0x5, 0x80, 0x3f,
        0x88, 0x80, 0x1f, 0xca, 0x1, 0xff, 0xc1, 0xd0,
        0xf, 0xee, 0x4, 0x0, 0xfc, 0x26, 0x1, 0xff,
        0xc0, 0x50, 0xf, 0xe5, 0xd, 0x0, 0xfe, 0x90,
        0xf, 0xf9, 0x8, 0x3, 0xf8, 0xc1, 0xc0, 0x3f,
        0x94, 0xc0, 0x3f, 0xd2, 0x1, 0xfc, 0xa0, 0x1,
        0x50, 0xf, 0xed, 0x20, 0xf, 0xd4, 0x40, 0x1f,
        0xdc, 0x1, 0x40, 0x7, 0xf0, 0xe2, 0x80, 0x71,
        0x5a, 0x80, 0x7f, 0x12, 0x0, 0x44, 0xc0, 0x1f,
        0xc3, 0x5d, 0x53, 0x2c, 0xd4, 0x0, 0xff, 0x40,
        0x7, 0x48, 0x80, 0x7f, 0x85, 0x59, 0x86, 0x1,
        0xff, 0x22, 0x80, 0x7b, 0x40, 0x3f, 0xf9, 0xa3,
        0x40, 0x1f, 0x1d, 0x80, 0x7f, 0xf3, 0x34, 0x40,
        0x3f, 0x25, 0x80, 0x7f, 0xf2, 0x47, 0x4c, 0x3,
        0xfc, 0x9a, 0x40, 0x1f, 0xfc, 0x64, 0xf2, 0x0,
        0xff, 0xe0, 0x16, 0xc0, 0x80, 0x7f, 0xf0, 0x8a,
        0xac, 0x40, 0x3f, 0xf8, 0x6f, 0xd2, 0x80, 0x1f,
        0xc2, 0xb7, 0xaa, 0x1, 0xff, 0xc7, 0x6b, 0xfc,
        0xa8, 0x8a, 0x6b, 0x7a, 0x90, 0x3, 0xfc,

        /* U+0037 "7" */
        0xef, 0xff, 0xfe, 0xb1, 0x80, 0x7f, 0xff, 0xc0,
        0x3f, 0xff, 0xe0, 0x1f, 0xfd, 0x11, 0x0, 0xff,
        0xeb, 0x11, 0x0, 0x3f, 0xfa, 0xd6, 0x1f, 0xdd,
        0xff, 0xcb, 0x90, 0xf, 0xc2, 0xc0, 0x23, 0xff,
        0xcc, 0xb0, 0xf, 0xcc, 0x1, 0xff, 0xcd, 0x42,
        0x0, 0xfd, 0x20, 0x1f, 0xfc, 0xdf, 0x0, 0xfc,
        0xa2, 0x1, 0xff, 0xcc, 0x34, 0x0, 0xfd, 0x20,
        0x1f, 0xfc, 0xd9, 0x0, 0xfc, 0x66, 0x0, 0xff,
        0xe6, 0x12, 0x80, 0x7e, 0x90, 0xf, 0xfe, 0x6d,
        0x80, 0x7e, 0x15, 0x0, 0xff, 0xe6, 0xb, 0x0,
        0x7e, 0x90, 0xf, 0xfe, 0x6c, 0x80, 0x7f, 0x30,
        0x7, 0xff, 0x35, 0x80, 0x3f, 0x28, 0x80, 0x7f,
        0xf3, 0x18, 0x40, 0x3f, 0x48, 0x7, 0xff, 0x36,
        0xc0, 0x3f, 0x19, 0x80, 0x3f, 0xf9, 0x8a, 0x40,
        0x1f, 0xa4, 0x3, 0xff, 0x9b, 0x20, 0x1f, 0x85,
        0x40, 0x3f, 0xf9, 0x88, 0x60, 0x1f, 0xa4, 0x3,
        0xff, 0x9b, 0xe0, 0x1f, 0xcc, 0x1, 0xff, 0xcc,
        0x34, 0x0, 0xfc, 0xc2, 0x1, 0xff, 0xcc, 0x90,
        0xf, 0xeb, 0x0, 0xff, 0xe6, 0xa, 0x80, 0x7e,
        0x42, 0x0, 0xff, 0xe6, 0x40, 0x7, 0xf7, 0x80,
        0x7f, 0xf3, 0x5, 0x80, 0x3f, 0x12, 0x0, 0x7f,
        0xf3, 0x18, 0x3, 0xfa, 0xc0, 0x3f, 0xf9, 0xb2,
        0x1, 0xfc, 0xc0, 0x1f, 0xfc, 0xc6, 0x10, 0xf,
        0xcc, 0x1, 0xff, 0xcd, 0xb0, 0xf, 0xeb, 0x0,
        0xff, 0xe6, 0x29, 0x0, 0x7e, 0x42, 0x0, 0xff,
        0xe6, 0x48, 0x7, 0xf7, 0x80, 0x7f, 0xf3, 0xc,
        0xc0, 0x1f, 0x89, 0x0, 0x3f, 0xf9, 0x90, 0x1,
        0xfd, 0x60, 0x1f, 0xfc, 0xc2, 0x40, 0xf, 0xc2,
        0xc0, 0x1f, 0xfc, 0xc8, 0x0, 0xfe, 0x60, 0xf,
        0xfe, 0x60, 0xa8, 0x7, 0xf4, 0x80, 0x7f, 0xf3,
        0x24, 0x3, 0xf9, 0x44, 0x3, 0xff, 0x98, 0xe0,
        0x1f, 0xd2, 0x1, 0xff, 0xcc, 0x70, 0xf, 0xe3,
        0x30, 0x7, 0xff, 0x32, 0x40, 0x3f, 0xa4, 0x3,
        0xff, 0x98, 0xc2, 0x1, 0xf8, 0x54, 0x3, 0xff,
        0x99, 0x60, 0x1f, 0xd2, 0x1, 0xff, 0xcc, 0x42,
        0x0, 0xfe, 0x60, 0xf, 0xfe, 0x64, 0x0, 0x7f,
        0x28, 0x80, 0x7f, 0xf2, 0xcc, 0xc0, 0x1f, 0xd2,
        0x1, 0xff, 0xc7,

        /* U+0038 "8" */
        0x0, 0xff, 0xe0, 0x9a, 0xb3, 0xb9, 0x94, 0xc0,
        0x3f, 0xf9, 0x45, 0x19, 0xf9, 0x53, 0x10, 0x9a,
        0xcf, 0xd9, 0x20, 0xf, 0xfe, 0x21, 0x56, 0xb9,
        0x80, 0x7f, 0x89, 0xb7, 0x10, 0x3, 0xff, 0x82,
        0xfa, 0xa0, 0x1f, 0xfc, 0x43, 0xb9, 0x0, 0xff,
        0xae, 0x0, 0x3f, 0xf9, 0xd, 0x82, 0x1, 0xfa,
        0xd0, 0x3, 0xff, 0x94, 0x78, 0x1, 0xf3, 0xa0,
        0x7, 0xff, 0x30, 0xa8, 0x3, 0x8a, 0x0, 0x3f,
        0xf9, 0xca, 0x80, 0x1a, 0xc0, 0x3f, 0xf8, 0x8,
        0xcc, 0x51, 0x0, 0xff, 0xbc, 0x3, 0x30, 0x7,
        0xf9, 0xbe, 0xe6, 0x55, 0xd0, 0x1, 0xfe, 0x41,
        0x0, 0x20, 0x7, 0xf9, 0xe4, 0x3, 0xcf, 0x20,
        0x1f, 0xe7, 0x0, 0x18, 0x7, 0xf1, 0x40, 0x7,
        0xe6, 0x30, 0xf, 0xef, 0x0, 0x70, 0x7, 0xf2,
        0x80, 0x7f, 0xa8, 0x3, 0xf8, 0x80, 0x6, 0x1,
        0xfd, 0x80, 0x1f, 0xe4, 0x0, 0xfe, 0x70, 0xf,
        0xfe, 0x3, 0x80, 0x7f, 0x8c, 0x3, 0xff, 0x80,
        0x60, 0x1f, 0xce, 0x1, 0xff, 0xc8, 0x70, 0x7,
        0x0, 0x7f, 0x10, 0x7, 0xf9, 0x40, 0x3f, 0x88,
        0x0, 0x80, 0x1f, 0xda, 0x1, 0xfe, 0xc0, 0xf,
        0xec, 0x0, 0x18, 0x80, 0x7e, 0x43, 0x0, 0xfc,
        0x2e, 0x1, 0xfc, 0xa0, 0x14, 0x0, 0x7f, 0x69,
        0x0, 0x78, 0x74, 0x3, 0xf9, 0xc0, 0x33, 0x10,
        0x7, 0xe1, 0xd8, 0x20, 0x1, 0x37, 0x98, 0x7,
        0xe1, 0x90, 0xe, 0xf0, 0xf, 0xf3, 0xef, 0xfb,
        0x64, 0x40, 0x3f, 0xb4, 0x40, 0x38, 0xb0, 0x3,
        0xff, 0x99, 0x46, 0x1, 0xf1, 0xe9, 0x0, 0x7f,
        0xf2, 0x7, 0x14, 0x3, 0xf8, 0xb5, 0xc0, 0x3f,
        0xf8, 0xcd, 0xe6, 0x1, 0xff, 0x22, 0x0, 0x3f,
        0xf8, 0xc8, 0xa0, 0x1f, 0xf4, 0x59, 0x80, 0x7f,
        0xf1, 0x8a, 0xe4, 0x3, 0xfa, 0xdc, 0x3, 0xff,
        0x94, 0xd8, 0x1, 0xf5, 0xa0, 0x7, 0xff, 0x30,
        0xf0, 0x3, 0x9d, 0x0, 0x3f, 0x8a, 0x33, 0xb9,
        0xb2, 0x40, 0x1f, 0xc7, 0x0, 0x11, 0x40, 0x7,
        0xf3, 0x6b, 0x98, 0x88, 0x9b, 0x5c, 0x3, 0xf9,
        0xcc, 0x1, 0x60, 0x1f, 0xcd, 0x20, 0x1f, 0xa1,
        0xc0, 0x3f, 0xa0, 0x0, 0xc0, 0x1f, 0x86, 0x40,
        0x3f, 0xd0, 0x20, 0x1f, 0x90, 0x50, 0x3, 0xf9,
        0x80, 0x3f, 0xf8, 0x12, 0x1, 0xfc, 0xf8, 0x1,
        0xfd, 0x80, 0x1f, 0xfc, 0x4, 0x0, 0xfe, 0xc2,
        0x0, 0xfe, 0x60, 0xf, 0xfe, 0x1, 0x0, 0x7f,
        0x30, 0x80, 0x7f, 0xf2, 0x84, 0x3, 0xf8, 0x40,
        0x3f, 0xc2, 0x1, 0xff, 0xc0, 0x10, 0xf, 0xf0,
        0x80, 0x7f, 0x28, 0x7, 0xff, 0x1, 0x40, 0x3f,
        0x84, 0xc0, 0x3f, 0xb4, 0x3, 0xff, 0x81, 0xa0,
        0x1f, 0xcd, 0xe0, 0x1f, 0xc8, 0x60, 0x1f, 0xe2,
        0x60, 0xf, 0xe2, 0x40, 0xf, 0xf6, 0x90, 0x7,
        0xf7, 0x0, 0x7f, 0xb0, 0x8c, 0x3, 0xf8, 0x71,
        0x40, 0x3c, 0x9a, 0x60, 0x1f, 0xc2, 0x81, 0x20,
        0x1f, 0xe1, 0xae, 0xa9, 0x8a, 0xeb, 0x20, 0xf,
        0xf3, 0x0, 0x14, 0xc0, 0x3f, 0xe1, 0x56, 0x75,
        0x10, 0xf, 0xf8, 0x64, 0x2, 0xe0, 0xf, 0xfe,
        0x85, 0x8, 0x4, 0x54, 0x1, 0xff, 0xce, 0x84,
        0x0, 0xe5, 0xa0, 0xf, 0xfe, 0x64, 0x38, 0x7,
        0xcb, 0xa6, 0x1, 0xff, 0xc8, 0x2c, 0x70, 0xf,
        0xe2, 0xc9, 0x20, 0xf, 0xfe, 0x20, 0xc6, 0x98,
        0x7, 0xff, 0x1, 0xb6, 0xd8, 0x80, 0x3f, 0xc4,
        0xb5, 0xce, 0x1, 0xff, 0xc4, 0x49, 0xdf, 0xba,
        0x98, 0x84, 0xd5, 0xf6, 0xd2, 0x80, 0x7f, 0x0,

        /* U+0039 "9" */
        0x0, 0xff, 0xe1, 0x1a, 0xb3, 0xb9, 0x90, 0x3,
        0xff, 0x9a, 0xd7, 0xf9, 0x53, 0x10, 0x9b, 0xfc,
        0x71, 0x0, 0xff, 0xe3, 0xbf, 0x4a, 0x0, 0x7f,
        0x1c, 0x74, 0x0, 0x7f, 0xf1, 0xf, 0x60, 0x40,
        0x3f, 0xf8, 0x4f, 0xc6, 0x1, 0xff, 0xc1, 0x5c,
        0x20, 0xf, 0xfe, 0x28, 0xe2, 0x80, 0x7f, 0xcb,
        0x40, 0x1f, 0xfc, 0x9a, 0x50, 0xf, 0xe3, 0xa0,
        0xf, 0xfe, 0x5d, 0x18, 0x7, 0xed, 0x0, 0xff,
        0xe6, 0xf0, 0x7, 0xd2, 0x20, 0x1f, 0xe1, 0x57,
        0x52, 0x0, 0xff, 0x14, 0x0, 0x71, 0x30, 0x7,
        0xfa, 0x3a, 0xa2, 0xb6, 0xc4, 0x3, 0xf9, 0xc4,
        0x3, 0x58, 0x7, 0xfa, 0x9c, 0x3, 0x93, 0xc8,
        0x3, 0xfa, 0x40, 0x33, 0x0, 0x7f, 0x3a, 0x80,
        0x7c, 0x3e, 0x1, 0xfc, 0xc0, 0x12, 0x0, 0x7f,
        0xc, 0x0, 0x7f, 0x13, 0x0, 0x7e, 0x14, 0x0,
        0x60, 0x7, 0xf3, 0x0, 0x7f, 0xd4, 0x1, 0xfd,
        0x80, 0x3, 0x0, 0xfe, 0xb0, 0xf, 0xf8, 0xc4,
        0x3, 0xf2, 0x0, 0x14, 0x3, 0xf8, 0xc0, 0x3f,
        0xf8, 0x8, 0x1, 0xf8, 0xc0, 0x2, 0x1, 0xf8,
        0x80, 0x3f, 0xf8, 0x24, 0x1, 0xfc, 0x40, 0x1f,
        0xe1, 0x0, 0xff, 0xe0, 0xf8, 0x7, 0xf3, 0x0,
        0x7f, 0x84, 0x3, 0xff, 0x82, 0x20, 0x1f, 0xc4,
        0x1, 0xfe, 0x30, 0xf, 0xfe, 0x58, 0x80, 0x80,
        0x7e, 0x10, 0xf, 0xfe, 0x69, 0x0, 0x7f, 0x20,
        0x7, 0xff, 0x2b, 0xc1, 0x40, 0x3f, 0xb4, 0x3,
        0xff, 0x99, 0xe0, 0x1f, 0xcc, 0x20, 0x1f, 0xf5,
        0x0, 0x7f, 0xc8, 0x1, 0xfe, 0xa0, 0xf, 0xf4,
        0x98, 0x7, 0xf7, 0x81, 0x18, 0x7, 0xf2, 0x50,
        0x7, 0xea, 0x60, 0xf, 0xfe, 0xc, 0x80, 0x7f,
        0x97, 0x58, 0x80, 0x4, 0xfc, 0xa0, 0x1f, 0xf0,
        0x80, 0x14, 0x40, 0x3f, 0xc5, 0x3b, 0xfe, 0xd8,
        0x10, 0xf, 0xfe, 0x25, 0x0, 0x7f, 0xf4, 0x88,
        0x2, 0x47, 0x0, 0xff, 0xe8, 0xb0, 0x6, 0x84,
        0x0, 0xff, 0xe8, 0x10, 0x7, 0x5a, 0x80, 0x7f,
        0xf1, 0x19, 0x40, 0x3f, 0x8, 0x7, 0xd5, 0x22,
        0x1, 0xff, 0xc0, 0x19, 0x93, 0x0, 0x7e, 0x50,
        0xf, 0xcd, 0xd0, 0x40, 0x1f, 0x85, 0xfd, 0x80,
        0xc0, 0x3f, 0x60, 0x7, 0xf9, 0xf7, 0x54, 0xec,
        0xc7, 0x9c, 0xe8, 0x10, 0x40, 0xf, 0xe4, 0x0,
        0xff, 0xe0, 0x12, 0xc4, 0xca, 0x18, 0xc0, 0x36,
        0x80, 0x7e, 0x13, 0x0, 0xff, 0xe5, 0x93, 0x0,
        0x7e, 0x60, 0xf, 0xfe, 0x64, 0x0, 0x7f, 0x50,
        0x7, 0xff, 0x2d, 0x94, 0x3, 0xf2, 0x10, 0x7,
        0xff, 0x29, 0xa4, 0x3, 0xfb, 0xc0, 0x3f, 0xf9,
        0x23, 0x52, 0x1, 0xfc, 0x88, 0x0, 0xff, 0xe3,
        0x9c, 0xf2, 0x80, 0x7f, 0xa8, 0x3, 0xff, 0x80,
        0x6c, 0xd3, 0xcd, 0xfe, 0x30, 0x7, 0xfd, 0x22,
        0x1, 0xff, 0xc0, 0x99, 0xd0, 0xc8, 0x1, 0xff,
        0xc1, 0x66, 0x0, 0x7f, 0xf5, 0x16, 0x40, 0x3f,
        0xfa, 0x8b, 0x40, 0x1f, 0xfd, 0x47, 0xa0, 0xf,
        0xfe, 0x99, 0x64, 0x0, 0x7f, 0xf4, 0x86, 0x74,
        0xc0, 0x3f, 0xfa, 0x2b, 0x5c, 0xc0, 0x1f, 0xfc,
        0xc1, 0x11, 0xac, 0x67, 0xd2, 0x80, 0x7f, 0xf0,
        0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
        {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
        {.bitmap_index = 0, .adv_w = 325, .box_w = 12, .box_h = 12, .ofs_x = 4, .ofs_y = -1},
        {.bitmap_index = 51, .adv_w = 643, .box_w = 34, .box_h = 52, .ofs_x = 3, .ofs_y = -1},
        {.bitmap_index = 428, .adv_w = 643, .box_w = 23, .box_h = 50, .ofs_x = 5, .ofs_y = 0},
        {.bitmap_index = 543, .adv_w = 643, .box_w = 36, .box_h = 51, .ofs_x = 2, .ofs_y = 0},
        {.bitmap_index = 921, .adv_w = 643, .box_w = 35, .box_h = 52, .ofs_x = 2, .ofs_y = -1},
        {.bitmap_index = 1338, .adv_w = 643, .box_w = 38, .box_h = 50, .ofs_x = 1, .ofs_y = 0},
        {.bitmap_index = 1576, .adv_w = 643, .box_w = 35, .box_h = 51, .ofs_x = 3, .ofs_y = -1},
        {.bitmap_index = 1964, .adv_w = 643, .box_w = 35, .box_h = 52, .ofs_x = 3, .ofs_y = -1},
        {.bitmap_index = 2403, .adv_w = 643, .box_w = 36, .box_h = 50, .ofs_x = 2, .ofs_y = 0},
        {.bitmap_index = 2702, .adv_w = 643, .box_w = 34, .box_h = 52, .ofs_x = 3, .ofs_y = -1},
        {.bitmap_index = 3174, .adv_w = 643, .box_w = 35, .box_h = 51, .ofs_x = 2, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_0[] = {
        0, 0, 1, 2, 3, 4, 5, 6,
        7, 8, 9, 10
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
        {
                {
                        .range_start = 46, .range_length = 12, .glyph_id_start = 1,
                        .unicode_list = NULL, .glyph_id_ofs_list = glyph_id_ofs_list_0, .list_length = 12, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL
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
        .bpp = 4,
        .kern_classes = 0,
        .bitmap_format = 1,
#if LV_VERSION_CHECK(8, 0, 0)
        .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t roboto_bold_70 = {
#else
lv_font_t roboto_bold_70 = {
#endif
        .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
        .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
        .line_height = 52,          /*The maximum line height required by the font*/
        .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
        .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
        .underline_position = -5,
        .underline_thickness = 3,
#endif
        .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if ROBOTO_BOLD_70*/

