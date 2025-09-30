//ToxinAccumulator.c
class ToxinAccumulator {
    private PlayerBase m_Player;
    private int m_AccumulationTime;
    private bool m_Active = false;
    private float m_Timer = 0;
    private bool m_SymptomsTriggered = false;

    void ToxinAccumulator(PlayerBase player, int minTime, int maxTime) {
        m_Player = player;
        m_AccumulationTime = Math.RandomInt(minTime, maxTime + 1);
        m_Active = true;
        m_Timer = 0;
        m_SymptomsTriggered = false;
        Print("BiohazardMod: Akumulacja toksyn rozpoczęta dla gracza " + player.GetIdentity().GetName());
    }

    void Tick(float deltaTime) {
        if (!m_Active || m_SymptomsTriggered) return;

        m_Timer += deltaTime;
        if (m_Timer >= m_AccumulationTime) {
            TriggerSymptoms();
        }
    }

    void TriggerSymptoms() {
		m_Player.GetSymptomManager().QueueUpPrimarySymptom(SymptomConstants.SYMPTOM_COUGH);
        m_SymptomsTriggered = true;
        if (!m_Player) return;

        // Przykładowe objawy
        m_Player.MessageStatus("⚠️ Objawy skażenia: kaszel, ziewanie, osłabienie");
        m_Player.GetHealthManager().DecreaseHealth(10); // Przykładowe obniżenie zdrowia
        m_Player.PlaySound("cough_1"); // Wymaga dodania dźwięku do moda
        m_Player.PlaySound("yawn_1");
		m_Player.SetShake(1.0, 2.0); // efekt drżenia ekranu

        Print("BiohazardMod: Objawy toksyczne uruchomione dla gracza " + m_Player.GetIdentity().GetName());
		if (ProtectionValidator.IsProtected(m_Player, m_Player.GetZoneData().ProtectionSuit)) {
        Print("BiohazardMod: Gracz chroniony — objawy zablokowane.");
        return;
}

    }

    void Stop() {
        m_Active = false;
        m_Timer = 0;
        m_SymptomsTriggered = false;
        Print("BiohazardMod: Akumulacja toksyn zatrzymana.");
    }

    bool IsActive() {
        return m_Active;
    }
}
