// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CryptGame : ModuleRules
{
	public CryptGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
