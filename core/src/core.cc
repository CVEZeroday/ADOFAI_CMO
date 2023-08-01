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

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#include "core.h"

using namespace rapidjson;

bool ParseJson(Document& doc, const std::string& jsonData)
{
  if (doc.Parse(jsonData.c_str()).HasParseError())
    return false;
  return doc.IsObject();
}

std::string JsonDocToString(Document& doc, bool isPretty = false)
{
  StringBuffer buf;
  if(isPretty)
  {
    PrettyWriter<StringBuffer> writer(buf);
    doc.Accept(writer);
  }
  else
  {
    Writer<StringBuffer> writer(buf);
    doc.Accept(writer);
  }
  return buf.GetString();
}

int parse(const char* filename)
{
  std::ifstream file(filename);
  std::stringstream ss;

  ss << file.rdbuf();

  Document level;
  ParseJson(level, ss.str());

  const Value& valueInfo = level["actions"];
  for (auto& data : valueInfo.GetArray())
  {
    if (strcmp(data["eventType"].GetString(), "AddDecoration") == 0)
    {

    }
  }

  for (auto& data : valueInfo.GetArray())
  {
    if (strcmp(data["eventType"].GetString(), "MoveDecoration") == 0)
    {

    }
  }

  return 0;
}
