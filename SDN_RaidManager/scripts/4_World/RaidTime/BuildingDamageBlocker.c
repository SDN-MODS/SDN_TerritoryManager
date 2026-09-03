modded class BaseBuildingBase
{
	private static ref map<string, int> s_RaidBlockedMsgCooldown = new map<string, int>();
	private ref Timer m_RaidTimeStateTimer;

	override void EEInit()
	{
		super.EEInit();

		if (!GetGame() || !GetGame().IsServer())
		{
			return;
		}

		RaidTimeRefreshDamageState();

		if (!m_RaidTimeStateTimer)
		{
			m_RaidTimeStateTimer = new Timer(CALL_CATEGORY_SYSTEM);
		}

		// Keep damage state synced with schedule transitions.
		m_RaidTimeStateTimer.Run(15.0, this, "RaidTimeRefreshDamageState", NULL, true);
	}

	void RaidTimeRefreshDamageState()
	{
		if (!GetGame() || !GetGame().IsServer())
		{
			return;
		}

		RaidTimeManager manager = RaidTimeManager.GetInstance();
		if (!manager || !manager.IsEnabled())
		{
			SetAllowDamage(true);
			return;
		}

		SetAllowDamage(manager.IsRaidTime());
	}

	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (GetGame() && GetGame().IsServer())
		{
			RaidTimeManager manager = RaidTimeManager.GetInstance();
			if (manager && manager.IsEnabled() && !manager.IsRaidTime())
			{
				SetAllowDamage(false);
				RaidTimeNotifyBlockedHit(source, manager);
				return;
			}
		}

		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}

	private void RaidTimeNotifyBlockedHit(EntityAI source, RaidTimeManager manager)
	{
		if (!source || !manager)
		{
			return;
		}

		PlayerBase player = PlayerBase.Cast(source);
		if (!player)
		{
			player = PlayerBase.Cast(source.GetHierarchyRootPlayer());
		}

		if (!player)
		{
			return;
		}

		string message = manager.GetRaidUnavailableMessage();
		if (message == "")
		{
			return;
		}

		int cooldownMs = manager.GetPlayerMessageCooldownSeconds() * 1000;
		int nowMs = GetGame().GetTime();

		string playerKey = "unknown";
		PlayerIdentity identity = player.GetIdentity();
		if (identity)
		{
			playerKey = identity.GetPlainId();
		}

		int nextAllowedMs = 0;
		if (s_RaidBlockedMsgCooldown.Find(playerKey, nextAllowedMs))
		{
			if (nowMs < nextAllowedMs)
			{
				return;
			}
		}

		s_RaidBlockedMsgCooldown.Set(playerKey, nowMs + cooldownMs);
		player.MessageStatus(message);
	}
}
