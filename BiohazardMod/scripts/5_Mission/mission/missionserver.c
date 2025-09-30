modded class MissionServer {
    private ref BiohazardZoneManager m_BiohazardManager;

    override void OnInit() {
        super.OnInit();
        m_BiohazardManager = new BiohazardZoneManager();
    }

    override void OnUpdate(float timeslice) {
        super.OnUpdate(timeslice);
        if (m_BiohazardManager) {
            m_BiohazardManager.TickAllZones(timeslice);
        }
    }

    BiohazardZoneManager GetBiohazardZoneManager() {
        return m_BiohazardManager;
    }
}

