// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShootThemUp : ModuleRules
{
	public ShootThemUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine",
			"PhysicsCore",
			"InputCore",
			"Niagara",
			"GameplayTasks",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] 
		{
			"ShootThemUp/Public/AI",
			"ShootThemUp/Public/AI/Decorators",
			"ShootThemUp/Public/AI/EQS",
			"ShootThemUp/Public/AI/Services",
			"ShootThemUp/Public/AI/Tasks",
			"ShootThemUp/Public/Animation",
			"ShootThemUp/Public/Components",
			"ShootThemUp/Public/Components/Widgets",
			"ShootThemUp/Public/Dev",
			"ShootThemUp/Public/Menu",
			"ShootThemUp/Public/Menu/UI",
			"ShootThemUp/Public/Pickups",
			"ShootThemUp/Public/Player",
			"ShootThemUp/Public/Sound",
			"ShootThemUp/Public/UI",
			"ShootThemUp/Public/Weapon",
			"ShootThemUp/Public/Weapon/Components",
	
			"ShootThemUp/Public/Interfaces"
		});
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
