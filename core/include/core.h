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

uint8_t* png2dxt5(uint8_t* src);
uint8_t* jpg2dxt1(uint8_t* src);
void pngResizer(const uint8_t* src_data, int src_width, int src_height,
                uint8_t* dst_data, int dst_width, int dst_height);
void jpgResizer(const uint8_t* src_data, int src_width, int src_height,
                uint8_t* dst_data, int dst_width, int dst_height);

#ifdef __cplusplus
}
#endif

#endif
