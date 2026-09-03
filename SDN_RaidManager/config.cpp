class CfgPatches
{
	class RaidTime
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = { "DZ_Data", "DZ_Scripts" };
	};
};

class CfgMods
{
	class RaidTime
	{
		dir = "RaidTime";
		name = "RaidTime";
		author = "S3NZ4T10N";
		credits = "S3NZ4T10N | SteamID: 76561198995988155";
		type = "mod";
		dependencies[] = { "Game", "World", "Mission" };

		class defs
		{
			class gameScriptModule
			{
				files[] = { "RaidTime/scripts/3_Game" };
			};
			class worldScriptModule
			{
				files[] = { "RaidTime/scripts/4_World" };
			};
			class missionScriptModule
			{
				files[] = { "RaidTime/scripts/5_Mission" };
			};
		};
	};
};
