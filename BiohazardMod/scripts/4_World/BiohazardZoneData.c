class BiohazardZoneData {
    string ZoneType;
    int ZoneChance;
    vector ZoneCenter;
    float ZoneRadiusMin;
    float ZoneRadiusMax;
    string ZoneMsgIn;
    string ZoneMsgOut;
    int ToxinAccumulationTimeMin;
    int ToxinAccumulationTimeMax;
    ref map<string, ref array<int>> ProtectionSuit;
}
