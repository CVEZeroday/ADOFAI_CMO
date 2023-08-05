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
int convertLevel(const char* filename, int mode, int target_w, int target_h, int clr_files)
{
  if (mode < 0 || mode > 2)
    return INVALID_MODE_ERR;

  std::ifstream file(filename);
  if (!file.is_open())
    return OPEN_FILE_ERR;

  std::stringstream ss;
  res_t target_res;

  ss << file.rdbuf();

  Document level;
  level.Parse(ss.str().c_str());

  if (level.HasParseError())
    return PARSE_ERR;

  if (!level.HasMember("actions"))
    return INVALID_LEVEL_ERR;
  auto& actions = level["actions"];
  for (SizeType i = 0; i < actions.Size(); ++i)
  {
    if (strcmp(actions[i]["eventType"].GetString(), "AddDecoration") == 0)
    {
      image_t _image;

      if (!level.HasMember("decorationImage"))
        return INVALID_LEVEL_ERR;
      parseImageName(actions[i]["decorationImage"].GetString(), &_image);

      if (_image.data.ext == ERR)
        return INVALID_EXT_ERR;

      std::string _imagename("_" + _image.filename); // _imagename은 _파일명.확장자
      if (loadImage(&_image.data, _imagename.c_str()) == ERR)
        return LOAD_IMAGE_ERR;

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

      if (mode != 1)
      {
        if (convert2dxt(&_image) == ERR)
          return DXT_CONVERSION_ERR;

        if (_image.data.ext == DXT5)
          _image.filename = _image.filename.substr(_image.filename.find_last_of(".")) += ".dxt5";
        if (_image.data.ext == DXT1)
          _image.filename = _image.filename.substr(_image.filename.find_last_of(".")) += ".dxt1";

        if (!level.HasMember("decorationImage"))
          return INVALID_LEVEL_ERR;
        actions[i]["decorationImage"].SetString(_image.filename.c_str(), level.GetAllocator());
      }

      rename(_imagename.c_str(), _image.filename.c_str()); // 임시 이름을 확장자 맞춰서 복구
      fclose(_image.data.fp);
      if (clr_files) 
        if (remove(_image.filename.c_str()) == ERR)
          return DELETE_IMAGE_ERR;

      auto& _scale = actions[i]["scale"];
      _scale[0].SetInt(_scale[0].GetInt() * _image.data.ratio);
      _scale[1].SetInt(_scale[1].GetInt() * _image.data.ratio);

      images.insert({actions[i]["tag"].GetString(), _image});
    }
  }

  for (SizeType i = 0; i < actions.Size(); ++i)
  {
    if (strcmp(actions[i]["eventType"].GetString(), "MoveDecoration") == 0)
    {
      auto it = images.find(actions[i]["tag"].GetString());
      if (it != images.end())
      {
        auto& _scale = actions[i]["scale"];
        _scale[0].SetInt(_scale[0].GetInt() * (*it).second.data.ratio);
        _scale[1].SetInt(_scale[1].GetInt() * (*it).second.data.ratio);
      }
    }
  }

  StringBuffer buf;
  Writer<StringBuffer> writer(buf);
  level.Accept(writer);

  if (clr_files)
  {
    std::ofstream output_file(filename);
    output_file << buf.GetString();
  }
  else
  {
    std::ofstream output_file("mod_" + std::string(filename));
    output_file << buf.GetString();
  }
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
