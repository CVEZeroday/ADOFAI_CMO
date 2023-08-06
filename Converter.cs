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
  internal class Converter
  {
    int convertLevel(string levelfile)
    {
      string levelData = File.ReadAllText(levelfile);

      JObject jobject = JObject.Parse(levelData);
      JToken j_decorations = jobject["decorations"];
      JToken j_actions = jobject["actions"];

      foreach (JToken data in j_decorations)
      {
        if (data["eventType"].ToString() == "AddDecoration")
        {

        }
      }

      return 0;
    }
  }
}
