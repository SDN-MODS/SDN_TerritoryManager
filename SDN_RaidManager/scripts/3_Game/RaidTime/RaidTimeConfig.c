class RaidDayWindow
{
	string DayOfWeek = "Saturday";
	int StartHour = 18;
	int StartMinute = 0;
	int Duration = 180;
}

class RaidTimeConfig
{
	ref array<ref RaidDayWindow> RaidDays = new array<ref RaidDayWindow>();
	string DiscordWebhookUrl = "";
	int AutoReloadSeconds = 15;
	bool EnableFileLog = true;
	int StateLogIntervalSeconds = 120;
	string DiscordStartTitle = "RAID START";
	string DiscordStartMessage = "Raid time is now active. Damage to base buildings is enabled.";
	string DiscordEndTitle = "RAID END";
	string DiscordEndMessage = "Raid time ended. Damage to base buildings is disabled.";
	string RaidUnavailablePlayerMessage = "Raid is not available right now.";
	int PlayerMessageCooldownSeconds = 10;

	void RaidTimeConfig()
	{
		if (RaidDays.Count() == 0)
		{
			RaidDayWindow defaultWindow = new RaidDayWindow();
			RaidDays.Insert(defaultWindow);
		}
	}
}
