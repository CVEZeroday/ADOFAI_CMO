/********************************************/
/* This source code is part of ADOFAI_CMO   */
/********************************************/
/*     Copyrights (C) 2023 CVE_zeroday.     */
/*          All rights reserved.            */
/********************************************/
/*          File Name: resizer.c            */
/*   Created by CVE_zeroday on 05.08.2023   */
/*               (T.Y.Kim)                  */
/********************************************/

#include <stdio.h>

#include "core.h"

int loadImage(imageData_t* imgData, const char* filename) // filename은 _파일명.png 형태
{
  FILE* _fp;
  _fp = fopen(filename, "wb"); // _파일명.png 생성
  if (_fp == NULL) return ERR;

  imgData->fp = _fp;

  return 0;
}