//BiohazardZoneManager.c
class BiohazardZoneManager {
    private ref array<ref BiohazardZone> m_Zones = new array<ref BiohazardZone>();
    private bool m_Initialized = false;

    void BiohazardZoneManager() {
        Init();
    }

    void Init() {
        if (m_Initialized) return;
        m_Initialized = true;

        // Upewnij się, że plik konfiguracyjny istnieje
        BiohazardConfigGenerator.EnsureConfigExists();

        // Wczytaj dane stref
        string path = "$profile:Biohazard/bioconfig.json";
        ref BiohazardZoneDataContainer container = new BiohazardZoneDataContainer();

        if (JsonFileLoader<ref BiohazardZoneDataContainer>.JsonLoadFile(path, container)) {
            foreach (auto zoneData : container.Zones) {
                auto zone = new BiohazardZone(zoneData);
                m_Zones.Insert(zone);
            }
            Print("BiohazardMod: Załadowano " + m_Zones.Count() + " stref Biohazard.");
        } else {
            Print("BiohazardMod: Nie udało się wczytać pliku konfiguracyjnego: " + path);
        }
    }

    // Sprawdza pozycję gracza względem stref
    void CheckPlayerZones(PlayerBase player) {
        foreach (auto zone : m_Zones) {
            if (zone.IsPlayerInside(player)) {
                zone.OnPlayerEnter(player);
            } else {
                zone.OnPlayerExit(player);
            }
        }
    }
}

