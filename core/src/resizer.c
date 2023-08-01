/********************************************/
/* This source code is part of ADOFAI_CMO   */
/********************************************/
/*     Copyrights (C) 2023 CVE_zeroday.     */
/*          All rights reserved.            */
/********************************************/
/*          File Name: resizer.c            */
/*   Created by CVE_zeroday on 01.08.2023   */
/*               (T.Y.Kim)                  */
/********************************************/

#include <stdio.h>
#include "core.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

void pngResizer(const uint8_t* src_data, int src_width, int src_height, 
                uint8_t* dst_data, int dst_width, int dst_height)
{
  stbir_resize_uint8(src_data, src_width, src_height, 0, dst_data, dst_width, dst_height, 0, 4); 
}

void jpgResizer(const uint8_t* src_data, int src_width, int src_height, 
                uint8_t* dst_data, int dst_width, int dst_height)
{
  stbir_resize_uint8(src_data, src_width, src_height, 0, dst_data, dst_width, dst_height, 0, 3); 
}
