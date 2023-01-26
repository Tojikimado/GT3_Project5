// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_B001_Grp7 : ModuleRules
{
	public Project_B001_Grp7(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "SlateCore", "Slate"}); ;
	}
}
