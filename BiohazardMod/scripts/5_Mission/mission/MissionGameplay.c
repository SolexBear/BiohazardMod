//MissionGameplay.c
modded class MissionGameplay
{
	class BiohazardHUD {
    private Widget m_Root;
    private TextWidget m_Warning;

    void Init() {
        m_Root = GetGame().GetWorkspace().CreateWidgets("BiohazardMod/layout/BiohazardHUD.layout");
        m_Warning = TextWidget.Cast(m_Root.FindAnyWidget("BiohazardWarning"));
        m_Root.Show(false);
    }

    void ShowWarning(bool state) {
        m_Root.Show(state);
    }
   }

}