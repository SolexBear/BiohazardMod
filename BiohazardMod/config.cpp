#define _ARMA_

class CfgPatches
{
    class BiohazardMod
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {};
    };
};

class CfgMods {
    class BiohazardMod {
        dir = "BiohazardMod";
        name = "BiohazardMod";
        type = "mod";
        dependencies[] = {"World", "Mission"};
        class defs {
            class worldScriptModule {
                files[] = {"BiohazardMod/scripts/4_World"};
            };
            class missionScriptModule {
                files[] = {"BiohazardMod/scripts/5_Mission"};
            };
        };
    };
};

