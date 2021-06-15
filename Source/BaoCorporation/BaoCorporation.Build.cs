// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BaoCorporation : ModuleRules
{
	public BaoCorporation(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
