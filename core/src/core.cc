/********************************************/
/* This source code is part of ADOFAI_CMO   */
/********************************************/
/*     Copyrights (C) 2023 CVE_zeroday.     */
/*          All rights reserved.            */
/********************************************/
/*           File Name: core.c              */
/*   Created by CVE_zeroday on 01.08.2023   */
/*               (T.Y.Kim)                  */
/********************************************/

/* This projects requires NVTT 3 and NVIDIA GPU. */
/* AMD GPU Acceleration is not supported yet. */

#include "core.h"

using namespace rapidjson;

// filename requires .adofai file path
// mode 0: optimize all
// mode 1: resize only
// mode 2: convert to dxt only
// target_w, target_h requires the target resolution (ignored in mode 2)
int convertImage(const char* filename, int mode, int target_w, int target_h, int clr_files)
{
  if (mode < 0 || mode > 2)
    return INVALID_MODE_ERR;

  res_t target_res;

      image_t _image;

      parseImageName(filename, &_image);

      if (_image.data.ext == ERR)
        return INVALID_EXT_ERR;

      int find = _image.filename.rfind("\\") + 1;

      std::string _imagepath = _image.filename.substr(0, find);
      std::string _imagename = "_" + _image.filename.substr(find, _image.filename.length() - find);
      if (loadImage(&_image.data, (_imagepath + _imagename).c_str()) == ERR)
        return LOAD_IMAGE_ERR;
      std::cout << "making new image: " << _imagename << "\n";

      switch (mode)
      {
        case 0:
        case 1:
          target_res.width = target_w;
          target_res.height = target_h;
          break;
        case 2:
          target_res = _image.data.res;
          break;
      }

      if (resize(&_image.data, target_res, _image.filename.c_str()) == ERR)
        return RESIZE_ERR;
      std::cout << "resizing image: " << _image.filename << "\n";

      if (mode != 1)
      {
        if (convert2dxt(&_image) == ERR)
          return DXT_CONVERSION_ERR;
        std::cout << "converting image: " << _image.filename << "\n";

        if (_image.data.ext == DXT5)
          _image.filename = _image.filename.substr(_image.filename.find_last_of(".")) += ".dxt5";
        if (_image.data.ext == DXT1)
          _image.filename = _image.filename.substr(_image.filename.find_last_of(".")) += ".dxt1";

      }

      rename(_imagename.c_str(), _image.filename.c_str()); // 임시 이름을 확장자 맞춰서 복구
      std::cout << "renaming image: " << _image.filename << "\n";

      fclose(_image.data.fp);
      if (clr_files) 
        if (remove(_image.filename.c_str()) == ERR)
          return DELETE_IMAGE_ERR;

  return 0;
}

void parseImageName(std::string filename, image_t *img)
{
  img->filename = filename;
  std::string ext = filename.substr(filename.find_last_of(".") + 1);
  for (auto& _ext : png_exts)
  {  
    if (_ext == ext)
    {
      img->data.ext = PNG;
      return;
    }
  }
  for (auto& _ext : jpg_exts)
  {
    if (_ext == ext)
    {
      img->data.ext = JPG;
      return;
    }
  }

  img->data.ext = ERR;
  return;
}

bool removeUTF8BOM(FILE* fp)
{
  unsigned char bom[3] = { 0 };
  fread(bom, sizeof(unsigned char), 3, fp);
  if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF)
  {
    fseek(fp, 3, SEEK_SET);
    return true;
  }
  fseek(fp, 0, SEEK_SET);
  return false;
}