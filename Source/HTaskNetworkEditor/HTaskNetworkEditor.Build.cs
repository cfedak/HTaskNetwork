using UnrealBuildTool;

public class HTaskNetworkEditor : ModuleRules
{
	public HTaskNetworkEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine",
			"UnrealEd",
			"HTaskNetworkRuntime"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"AssetTools",
			"InputCore",
			"AIGraph",
			"Slate",
			"SlateCore",
			"GraphEditor",
			"PropertyEditor",
			"EditorStyle",
			"Kismet",
			"KismetWidgets",
			"ApplicationCore",
			"ToolMenus"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}