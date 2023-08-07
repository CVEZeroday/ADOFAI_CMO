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

int loadImage(imageData_t* imgData, const char* filename) 
{
  FILE* _fp;
  _fp = fopen(filename, "w+");
  if (!_fp) return ERR;

  imgData->fp = _fp;

  return 0;
}
