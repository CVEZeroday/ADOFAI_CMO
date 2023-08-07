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

#define DEBUG

#ifdef DEBUG
#define DEBUF_PRINTF(...) printf(...);
#else
#define DEBUG_PRINTF(...) (0)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
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
  DELETE_IMAGE_ERR = -11,
  NO_MEM_ERR = -12,
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
  int ext; // 확장자. 0: png, 1: jpg, 2: dxt5, 3: dxt1
  int channels; // 채널 수
  double ratio; // 리사이징 비율
  res_t res; // 해상도
  FILE* fp; // 파일 포인터
} imageData_t;

typedef struct out_s
{
  double ratio;
  const char* mod_filename;
} out_t;

/* image.c */
int loadImage(imageData_t* imgData, const char* filename);

/* resizer.c */
int resize(imageData_t* imgData, res_t dst_res, const char* filename, double n);
uint8_t* pngResize(const uint8_t* src_data, res_t* src_res, res_t* dst_res);
uint8_t* jpgResize(const uint8_t* src_data, res_t* src_res, res_t* dst_res);

/* core.cc */
__declspec(dllexport)
int convertImage(const char* filename, int mode, int target_w, int target_h, int clr_files, double n, out_t* out);

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
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/encodings.h"

typedef struct image_s
{
  std::string filename; // 파일 이름
  imageData_t data; // C언어용 이미지 데이터
} image_t;

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

/* converter.cc */
int convert2dxt(image_t* img);

#endif
#endif
