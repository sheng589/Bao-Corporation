// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EasyFirebaseEditor.h"
#include "FirebaseAuthSetting.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "PropertyEditorModule.h"
#include "ISettingsModule.h"

#include "LevelEditor.h"

#define LOCTEXT_NAMESPACE "FEasyFirebaseEditorModule"

void FEasyFirebaseEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		SettingsModule->RegisterSettings(TEXT("Project"), TEXT("EasyFirebase"), TEXT("Auth"),
			LOCTEXT("Firebase", "Firebase"),
			LOCTEXT("Auth", "Settings for Auth"),
			GetMutableDefault<UFirebaseAuthSetting>()
		);

	}
}

void FEasyFirebaseEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEasyFirebaseEditorModule, EasyFirebaseEditor)