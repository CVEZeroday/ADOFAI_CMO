#ifndef __CORE_H__
#define __CORE_H__
/********************************************/
/* This source code is part of ADOFAI_CMO   */
/********************************************/
/*     Copyrights (C) 2023 CVE_zeroday.     */
/*          All rights reserved.            */
/********************************************/
/*           File Name: core.h              */
/*   Created by CVE_zeroday on 01.08.2023   */
/*               (T.Y.Kim)                  */
/********************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum errno_e
{
  ERR = -1,
  INVALID_MODE_ERR = -2,
  OPEN_FILE_ERR = -3,
  PARSE_ERR = -4,
  INVALID_LEVEL_ERR = -5,
  INVALID_EXT_ERR = -6,
  LOAD_IMAGE_ERR = -7,
  RESIZE_ERR = -8,
  DXT_CONVERSION_ERR = -9,
  SAVE_IMAGE_ERR = -10,
  DELETE_IMAGE_ERR = -11
};

enum ext_e
{
  PNG = 0,
  JPG = 1,
  DXT5 = 2,
  DXT1 = 3,
};

/* struct declaration */
typedef struct res_s
{
  int width;
  int height;
} res_t;

typedef struct imageData_s
{
  int ext;
  double ratio;
  res_t res;
  uint8_t* bytes;
} imageData_t;

/* image.c */
int loadImage(imageData_t* imgData);
int saveImage(imageData_t* imgData, const char* filename);
int deleteImage(imageData_t* imgData, const char* filename, int ext);

/* converter.c */
int convert2dxt(imageData_t* imgData);
uint8_t* png2dxt5(const uint8_t* src);
uint8_t* jpg2dxt1(const uint8_t* src);

/* resizer.c */
int resize(imageData_t* imgData, res_t dst_res);
uint8_t* pngResize(const uint8_t* src_data, res_t* src_res, res_t* dst_res);
uint8_t* jpgResize(const uint8_t* src_data, res_t* src_res, res_t* dst_res);

/* core.cc */
__declspec(dllexport)
int convertLevel(const char* filename, int mode, int target_w, int target_h);

#ifdef __cplusplus
}
#endif

/* c++ only */
#ifdef __cplusplus
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

typedef struct image_s
{
  std::string filename;
  std::string tag;
  imageData_t data;
} image_t;

static std::map<std::string, image_t> images;

static std::vector<std::string> png_exts ({
  "png"
});
static std::vector<std::string> jpg_exts ({
  "jpg",
  "jpeg",
  "jfif",
  "jpe"
});

void parseImageName(std::string filename, image_t *img);
#endif
#endif
