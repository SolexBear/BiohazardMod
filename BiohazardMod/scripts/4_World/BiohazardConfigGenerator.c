//BiohazardConfigGenerator.c
class BiohazardConfigGenerator {
    static void EnsureConfigExists() {
        string folderPath = "$profile:Biohazard";
        string filePath = folderPath + "/bioconfig.json";

        // Tworzenie folderu, jeśli nie istnieje
        if (!FileExist(folderPath)) {
            MakeDirectory(folderPath);
            Print("BiohazardMod: Folder utworzony: " + folderPath);
        }

        // Tworzenie pliku JSON, jeśli nie istnieje
        if (!FileExist(filePath)) {
            auto defaultZone = new BiohazardZoneData();
            defaultZone.ZoneType = "Biohazard";
            defaultZone.ZoneChance = 100;
            defaultZone.ZoneCenter = "1695.40 0 14042.22";
            defaultZone.ZoneRadiusMin = 675;
            defaultZone.ZoneRadiusMax = 725;
            defaultZone.ZoneMsgIn = "CAUTION: YOU ARE IN A BIOHAZARD ZONE";
            defaultZone.ZoneMsgOut = "YOU LEFT THE BIOHAZARD ZONE";
            defaultZone.ToxinAccumulationTimeMin = 5;
            defaultZone.ToxinAccumulationTimeMax = 60;
            defaultZone.ProtectionSuit = new map<string, ref array<int>>();

            defaultZone.ProtectionSuit.Insert("NBCBootsGray", {10});
            defaultZone.ProtectionSuit.Insert("NBCGlovesGray", {10});
            defaultZone.ProtectionSuit.Insert("NBCHoodGray", {10});
            defaultZone.ProtectionSuit.Insert("NBCJacketGray", {20});
            defaultZone.ProtectionSuit.Insert("NBCPantsGray", {20});
            defaultZone.ProtectionSuit.Insert("GP5GasMask", {30, 1});
            defaultZone.ProtectionSuit.Insert("GasMask", {30, 1});

            auto container = new BiohazardZoneDataContainer();
            container.Zones = new array<ref BiohazardZoneData>();
            container.Zones.Insert(defaultZone);

            JsonFileLoader<ref BiohazardZoneDataContainer>.JsonSaveFile(filePath, container);
            Print("BiohazardMod: Plik konfiguracyjny utworzony: " + filePath);
        }
    }
}
