/********************************************/
/* This source code is part of ADOFAI_CMO   */
/********************************************/
/*     Copyrights (C) 2023 CVE_zeroday.     */
/*          All rights reserved.            */
/********************************************/
/*         File Name: Converter.cs          */
/*   Created by CVE_zeroday on 01.08.2023   */
/*               (T.Y.Kim)                  */
/********************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace ADOFAI_Custom_Optimization_mod
{
  struct out_s
  {
    double ratio;
    string mod_filename;
  };

  class Converter
  {

    [DllImport("CMO_CORE.dll")]
    public static extern int convertImage(string filename, int mode, int target_w, int target_h, int clr_files, double n, out out_s _out);

    private Dictionary<string, double> image_ratio;
    public static int convertLevel(string levelfile, int mode, int targrt_w, int target_h, double n, int clr_files)
    {
      images = new Dictionary<string, image_s>();

      string levelData = File.ReadAllText(levelfile);

      JObject jobject = JObject.Parse(levelData);
      JToken j_decorations = jobject["decorations"];
      JToken j_actions = jobject["actions"];

      foreach (JToken data in j_decorations)
      {
        if (data["eventType"].ToString() == "AddDecoration")
        {
          out_s _out;
          int ret = convertImage(data["decorationImage"].ToString(), mode, target_w, target_h, clr_files, n, _out);
          if (ret) return ret;
        
          data["decorationImage"] = _out.mod_filename;
          data["scale"][0] *= _out.ratio;
          data["scale"][1] *= _out.ratio;
          
          images_ratio.Add(data["tag"], _out.ratio);
        }
      }
      foreach (JToken data in j_actions)
      {
        if (data["eventType"].ToString() == "MoveDecoration")
        {
          if (images_ratio.ContainsKey(data["tag"].ToString()))
          {
            data["scale"][0] *= images_ratio[data["tag"].ToString()];
            data["scale"][1] *= images_ratio[data["tag"].ToString()];
          }
        }

      }

      levelData = jobject.ToString();
      File.WriteAllText("output_" + levelfile, levelData);

      return 0;
    }
  }
}
