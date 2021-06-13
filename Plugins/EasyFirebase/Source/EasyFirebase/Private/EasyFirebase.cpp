// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EasyFirebase.h"
#include "FirebaseFunctionLibrary.h"

#define LOCTEXT_NAMESPACE "FEasyFirebaseModule"



void FEasyFirebaseModule::StartupModule()
{
	UFirebaseFunctionLibrary::FireBaseInitialize();
	OnStartModule();
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FEasyFirebaseModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#if !PLATFORM_IOS
void FEasyFirebaseModule::OnStartModule()
{
}
#endif

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEasyFirebaseModule, EasyFirebase)