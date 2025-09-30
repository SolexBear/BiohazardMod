//BiohazardZone.c
class BiohazardZone {
    private ref BiohazardZoneData m_Data;
    private ref map<PlayerBase, ref ToxinAccumulator> m_Accumulators = new map<PlayerBase, ref ToxinAccumulator>();
    private ref set<PlayerBase> m_PlayersInside = new set<PlayerBase>();

    void BiohazardZone(BiohazardZoneData data) {
        m_Data = data;
    }

    bool IsPlayerInside(PlayerBase player) {
        float distance = vector.Distance(player.GetPosition(), m_Data.ZoneCenter);
        return distance <= m_Data.ZoneRadiusMax;
    }

    void OnPlayerEnter(PlayerBase player) {
        if (!m_PlayersInside.Contains(player)) {
            m_PlayersInside.Insert(player);
            player.MessageStatus(m_Data.ZoneMsgIn);

            if (!m_Accumulators.Contains(player)) {
                auto acc = new ToxinAccumulator(player, m_Data.ToxinAccumulationTimeMin, m_Data.ToxinAccumulationTimeMax);
                m_Accumulators.Insert(player, acc);
            }
        }
    }

    void OnPlayerExit(PlayerBase player) {
        if (m_PlayersInside.Contains(player)) {
            m_PlayersInside.Remove(player);
            player.MessageStatus(m_Data.ZoneMsgOut);

            if (m_Accumulators.Contains(player)) {
                m_Accumulators.Get(player).Stop();
                m_Accumulators.Remove(player);
            }
        }
    }

    void Tick(float deltaTime) {
        foreach (auto player : m_PlayersInside) {
            if (m_Accumulators.Contains(player)) {
                m_Accumulators.Get(player).Tick(deltaTime);
            }
        }
    }
}
