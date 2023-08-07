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
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int resize(imageData_t* imgData, res_t dst_res, const char* filename)
{
  uint8_t* _data = stbi_load(filename, &imgData->res.width, &imgData->res.height, &imgData->channels, 0);

  res_t src_res = imgData->res;

  double w_ratio = (double)dst_res.width / src_res.width;
  double h_ratio = (double)dst_res.height / src_res.height;

  double ratio = (w_ratio < h_ratio) ? w_ratio : h_ratio;

  dst_res.width = (int)(src_res.width * ratio);
  dst_res.height = (int)(src_res.height * ratio);

  dst_res.width = (dst_res.width + 3) & ~3;
  dst_res.height = (dst_res.height + 3) & ~3;
  
  uint8_t* _tmp;
  if (imgData->ext == PNG)
  {
    _tmp = pngResize(_data, &src_res, &dst_res);
    if (!stbi_write_png(filename, dst_res.width, dst_res.height, imgData->channels, _tmp, dst_res.width * imgData->channels))
      goto err;
  }
  else if (imgData->ext == JPG)
  {
    _tmp = jpgResize(_data, &src_res, &dst_res);
    if (!stbi_write_jpg(filename, dst_res.width, dst_res.height, imgData->channels, _tmp, dst_res.width * imgData->channels))
      goto err;
  }
  else return ERR;

  imgData->res = dst_res;
  imgData->ratio = ratio;

  stbi_image_free(_data);
  free(_tmp);
  return 0;

err:
  stbi_image_free(_data);
  return -1;
}

uint8_t* pngResize(const uint8_t* src_data, res_t* src_res, res_t* dst_res)
{
  uint8_t* _dst = malloc(dst_res->width * dst_res->height * 4);
  stbir_resize_uint8(src_data, src_res->width, src_res->height, 0, _dst, dst_res->width, dst_res->height, 0, 4); 
  return _dst;
}

uint8_t* jpgResize(const uint8_t* src_data, res_t* src_res, res_t* dst_res)
{
  uint8_t* _dst = malloc(dst_res->width * dst_res->height * 3);
  stbir_resize_uint8(src_data, src_res->width, src_res->height, 0, _dst, dst_res->width, dst_res->height, 0, 3);
  return _dst;
}
