// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HypeRateUE5 : ModuleRules
{
	public HypeRateUE5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
