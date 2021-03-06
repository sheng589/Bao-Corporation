// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EasyFirebaseEditor : ModuleRules
{
	public EasyFirebaseEditor(ReadOnlyTargetRules Target) : base(Target)
	{
        PrivatePCHHeaderFile = "Public/EasyFirebaseEditor.h";
       
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"EasyFirebaseEditor/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
                "CoreUObject",
                "InputCore",
                "UnrealEd",
                "Engine",
                "Slate",
                "SlateCore",
                "EditorStyle",
                "EditorWidgets",
                "DesktopWidgets",
                "PropertyEditor",
                "SharedSettingsWidgets",
                "SourceControl",
                "TargetPlatform",
                "RenderCore",
                "MaterialShaderQualitySettings",
            }
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
