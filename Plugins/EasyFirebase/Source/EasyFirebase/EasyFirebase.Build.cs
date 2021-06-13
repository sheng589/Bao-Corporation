// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class EasyFirebase : ModuleRules
{
	public EasyFirebase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
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
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        
        
        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicDefinitions.Add("INTERNAL_EXPERIMENTAL=0");
            PrivateDependencyModuleNames.Add("Launch");
            PrivateIncludePaths.Add("ThirdParty/firebase_cpp_sdk/include");

            string[] Architectures = new string[] {
                "armeabi-v7a",
                "arm64-v8a",
            };

            string[] StaticLibrariesAndroid = new string[] {
                "firebase_app",
                "firebase_database",
                "firebase_auth",
                "firebase_analytics",
            };

            foreach (string Architecture in Architectures)
            {
                string strStaticPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/firebase_cpp_sdk/libs/android/" + Architecture + "/c++"));
                foreach (string Lib in StaticLibrariesAndroid)
                {
                    PublicAdditionalLibraries.Add(Path.Combine(strStaticPath, "lib" + Lib + ".a") );
                }
            }
            
            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "EasyFirebase_UPL.xml"));
        }
        else if(Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDefinitions.Add("INTERNAL_EXPERIMENTAL=1");
            PrivateIncludePaths.Add("ThirdParty/firebase_cpp_sdk/include");

            string strStaticPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/firebase_cpp_sdk/libs/windows/VS2015/MD/x64/Release"));

            string[] StaticLibrariesWindows = new string[] {
                "firebase_app",
                "firebase_auth",
                "firebase_database",
                "firebase_analytics",
                
            };

            foreach (string Lib in StaticLibrariesWindows)
            {
                PublicAdditionalLibraries.Add(Path.Combine(strStaticPath, Lib + ".lib") );
            }

            string[] SystemLibraryWindows = new string[]{
                "Psapi",
                "Userenv",
                "Crypt32"
            };

            foreach (string Lib in SystemLibraryWindows)
            {
                PublicSystemLibraries.Add(Lib + ".lib");
            }
        }
        
    }
}
