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

    BiohazardConfigGenerator.EnsureConfigExists();

    string path = "$profile:Biohazard/bioconfig.json";
    ref BiohazardZoneDataContainer container = new BiohazardZoneDataContainer();

    JsonFileLoader<ref BiohazardZoneDataContainer>.JsonLoadFile(path, container);

    if (container && container.Zones && container.Zones.Count() > 0) {
        foreach (auto zoneData : container.Zones) {
            auto zone = new BiohazardZone(zoneData);
            m_Zones.Insert(zone);
        }
        Print("BiohazardMod: Załadowano " + m_Zones.Count() + " stref Biohazard.");
    } else {
        Print("BiohazardMod: Nie udało się wczytać danych ze stref.");
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
	void TickAllZones(float deltaTime) {
    foreach (auto zone : m_Zones) {
        zone.Tick(deltaTime);
    }
}

}

