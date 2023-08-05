/********************************************/
/* This source code is part of ADOFAI_CMO   */
/********************************************/
/*     Copyrights (C) 2023 CVE_zeroday.     */
/*          All rights reserved.            */
/********************************************/
/*         File Name: converter.c           */
/*   Created by CVE_zeroday on 01.08.2023   */
/*               (T.Y.Kim)                  */
/********************************************/

#include "core.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_DXT_IMPLEMENTATION
#include "stb_dxt.h"

int convert2dxt(imageData_t* imgData)
{
  uint8_t* tmp = imgData->bytes;
  if (imgData->ext == PNG)
  {
    imgData->bytes = png2dxt5(imgData->bytes);
  }
  else if (imgData->ext == JPG)
  {
    imgData->bytes = jpg2dxt1(imgData->bytes);
  }
  else return ERR;
  
  free(tmp);
  return 0;
}

uint8_t* png2dxt5(const uint8_t* src)
{
  stb_compress_dxt_block(unsigned char *dest, const unsigned char *src_rgba_four_bytes_per_pixel, int alpha, int mode);
  return 0;
}

uint8_t* jpg2dxt1(const uint8_t* src)
{

  return 0;
}
