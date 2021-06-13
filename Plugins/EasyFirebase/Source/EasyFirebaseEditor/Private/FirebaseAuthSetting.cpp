// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseAuthSetting.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/ConfigCacheIni.h"
#include <sstream>

#if WITH_EDITOR
void UFirebaseAuthSetting::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	saveValues(AndroidFacebookAppId);

	SaveConfig(CPF_Config, *GetDefaultConfigFilename());
}

#endif

void UFirebaseAuthSetting::saveValues(const FString& appid)
{
	std::stringstream ss;
	ss << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
	ss << "<resources>" << std::endl;
	ss << "\t<string name=\"facebook_app_id\">" << TCHAR_TO_UTF8(*appid) << "</string>" << std::endl;
	ss << "\t<string name=\"fb_login_protocol_scheme\">fb" << TCHAR_TO_UTF8(*appid) << "</string>" << std::endl;
	ss << "</resources>" << std::endl;

	FString strContent = UTF8_TO_TCHAR(ss.str().c_str());


	FString strProjectFacebookStringPath = FPaths::ProjectDir() / TEXT("Build/Android/strings.xml");
	FFileHelper::SaveStringToFile(strContent, *strProjectFacebookStringPath);
}

void UFirebaseAuthSetting::saveGooglePlayAppId(const FString& appid)
{
	std::stringstream ss;
	ss << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
	ss << "<resources>" << std::endl;
	ss << "\t<string name=\"app_id\">" << TCHAR_TO_UTF8(*appid) << "</string>" << std::endl;
	ss << "</resources>" << std::endl;

	FString strContent = UTF8_TO_TCHAR(ss.str().c_str());


	FString strProjectFacebookStringPath = FPaths::ProjectDir() / TEXT("Build/Android/GooglePlayAppID.xml");
	FFileHelper::SaveStringToFile(strContent, *strProjectFacebookStringPath);
}

void UFirebaseAuthSetting::PostInitProperties()
{
	FString appId;
	GConfig->GetString(TEXT("/Script/EasyFirebaseEditor.FirebaseAuthSetting"), TEXT("AndroidFacebookAppId"), appId, GEngineIni);
	saveValues(appId);

	FString googlePlayAppId;
	GConfig->GetString(TEXT("/Script/EasyFirebaseEditor.FirebaseAuthSetting"), TEXT("GooglePlayAppId"), googlePlayAppId, GEngineIni);
	saveGooglePlayAppId(googlePlayAppId);

	Super::PostInitProperties();
}