modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		RaidTimeManager.GetInstance().Init();
	}
}
