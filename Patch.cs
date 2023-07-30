using ADOFAI;
using HarmonyLib;
using UnityEngine;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ADOFAI_CMO
{
  [HarmonyPatch(typeof(scrExtImgHolder), "LoadTexture")]
  internal class Patch
  {
    public static bool Prefix(ref Texture2D __result, string filePath, out LoadResult status, int maxSideSize = -1)
    {
      status = LoadResult.MissingFile;
      Texture2D texture2D;
      if (GCS.internalLevelName != null)
      {
        return true;
      }
      else
      {
        if (!RDFile.Exists(filePath))
        {
          __result = (Texture2D)null;
          return false;
        }
        byte[] data = RDFile.ReadAllBytes(filePath, out status);
        texture2D = new Texture2D(2, 2, TextureFormat.RGBA32, false);
        if (!texture2D.LoadImage(data))
        {
          __result = (Texture2D)null;
          return false;
        }
        if (maxSideSize != -1)
          scrExtImgHolder.ShrinkImage(texture2D, maxSideSize);
        texture2D.name = filePath;
      }
      texture2D.wrapMode = TextureWrapMode.Repeat;
      __result = texture2D;
      return false;
    }

  }
}
