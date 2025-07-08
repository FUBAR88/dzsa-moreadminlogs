class CfgPatches
{
	class moreAdminLogs
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={};
	};
};
class CfgMods
{
	class moreAdminLogs
	{
		dir="moreAdminLogs";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="moreAdminLogs";
		credits="";
		author="";
		authorID="0";
		version="1.1";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"World"
		};
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"moreAdminLogs/scripts/4_World"
				};
			};
		};
	};
};
class CfgVehicles
{

};
