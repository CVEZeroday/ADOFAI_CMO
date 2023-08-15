using HarmonyLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using UnityModManagerNet;

namespace ADOFAI_CMO
{
  public class Main
  {
    public static UnityModManager.ModEntry.ModLogger Logger;
    public static Harmony harmony;
    public static bool IsEnabled = false;

    public static void Setup(UnityModManager.ModEntry modEntry)
    {
      Logger = modEntry.Logger;
      modEntry.OnToggle = OnToggle;
    }

    public static bool OnToggle(UnityModManager.ModEntry modEntry, bool val)
    {
      IsEnabled = val;

      if (val)
      {
        harmony = new Harmony(modEntry.Info.Id);
        harmony.PatchAll(Assembly.GetExecutingAssembly());
      }
      else harmony.UnpatchAll(modEntry.Info.Id);

      return true;
    }

    private static void OnGUI(UnityModManager.ModEntry modEntry)
    {
      //
    }

    private static void OnSaveGUI(UnityModManager.ModEntry modEntry)
    {
      //
    }
  }

  public class ModSetting : UnityModManager.ModSettings
  {

  }
}
