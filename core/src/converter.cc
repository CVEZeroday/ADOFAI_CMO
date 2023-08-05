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

#include <nvtt/nvtt.h>

#include "core.h"

int convert2dxt(image_t* img)
{
  nvtt::Surface image;
  image.load(img->filename.c_str());

  nvtt::Context context(true);
  nvtt::CompressionOptions compressionOptions;

  nvtt::OutputOptions outputOptions;
  outputOptions.setOutputHeader(false);
  outputOptions.setFileHandle(img->data.fp);

  if (img->data.ext == PNG)
  {
    compressionOptions.setFormat(nvtt::Format_DXT5);
    context.compress(image, 0, 0, compressionOptions, outputOptions);
  }
  else if (img->data.ext == JPG)
  {
    compressionOptions.setFormat(nvtt::Format_DXT1);
    context.compress(image, 0, 0, compressionOptions, outputOptions);
  }
  else return ERR;
  
  return 0;
}