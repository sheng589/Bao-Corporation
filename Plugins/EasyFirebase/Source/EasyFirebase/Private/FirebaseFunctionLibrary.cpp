// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseFunctionLibrary.h"
#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif
#include "UObject/Package.h"
#include "UObject/ObjectMacros.h"
#include "UObject/UObjectGlobals.h"
#include "Misc/Paths.h"
#include "Misc/MessageDialog.h"
#include "HAL/FileManager.h"
#include "Internationalization/Internationalization.h"
#include "Misc/FileHelper.h"
#include "firebase/app.h"
#include "firebase/auth.h"
#include "firebase/database.h"
#include "firebase/future.h"
#include "firebase/util.h"
#include "firebase/analytics.h"
#include "EasyFirebase.h"
#include "FirebaseFutureVoid.h"

#define LOCTEXT_NAMESPACE "FEasyFirebaseModule"

#if PLATFORM_IOS
#import <FirebaseCore/FIROptions.h>
namespace firebase 
{
	static void PlatformOptionsToAppOptions(FIROptions* platform_options,
		AppOptions* app_options) {
		if (!strlen(app_options->app_id())) {
			const char* value = platform_options.googleAppID.UTF8String;
			if (value) app_options->set_app_id(value);
		}
		if (!strlen(app_options->api_key())) {
			const char* value = platform_options.APIKey.UTF8String;
			if (value) app_options->set_api_key(value);
		}
		/*if (!strlen(app_options->package_name())) {
			const char* value = platform_options.bundleID.UTF8String;
			if (value) app_options->set_package_name(value);
		}*/
		if (!strlen(app_options->messaging_sender_id())) {
			const char* value = platform_options.GCMSenderID.UTF8String;
			if (value) app_options->set_messaging_sender_id(value);
		}
		if (!strlen(app_options->database_url())) {
			const char* value = platform_options.databaseURL.UTF8String;
			if (value) app_options->set_database_url(value);
		}
		if (!strlen(app_options->ga_tracking_id())) {
			const char* value = platform_options.trackingID.UTF8String;
			if (value) app_options->set_ga_tracking_id(value);
		}
		if (!strlen(app_options->storage_bucket())) {
			const char* value = platform_options.storageBucket.UTF8String;
			if (value) app_options->set_storage_bucket(value);
		}
		if (!strlen(app_options->project_id())) {
			NSString* value = platform_options.projectID;
			if (value) app_options->set_project_id(value.UTF8String);
		}
		if (!strlen(app_options->client_id())) {
			const char* value = platform_options.clientID.UTF8String;
			if (value) app_options->set_client_id(value);
		}
	}
}
#endif

::firebase::App* g_firebaseApp = nullptr;

bool UFirebaseFunctionLibrary::FireBaseInitialize()
{
	if (g_firebaseApp) 
	{
		return true;
	}

	::firebase::AppOptions option;
#if PLATFORM_ANDROID || PLATFORM_WINDOWS
	FString strJsonData;
	FString cfgPath = FPaths::ProjectContentDir() / TEXT("google/google-services.json");
	FFileHelper::LoadFileToString(strJsonData, *cfgPath);
	firebase::AppOptions::LoadFromJsonConfig(TCHAR_TO_UTF8(*strJsonData), &option);
	
#endif
	UE_LOG(FireBase, Log, TEXT("FireBaseInitialize to initialize Firebase Database."));
#if PLATFORM_ANDROID
	g_firebaseApp = ::firebase::App::Create(FAndroidApplication::GetJavaEnv(), FJavaWrapper::GameActivityThis);
#elif PLATFORM_WINDOWS
	g_firebaseApp = ::firebase::App::Create(option);
#else
	g_firebaseApp = ::firebase::App::Create(option);
#endif

#if WITH_EDITOR
	if (!g_firebaseApp)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("OpenFireBaseFailBody", "Cannot open Content/google/google-services.json, please download google-services.json and GoogleService-Info.plist put it under Content/google/") );
		FPlatformMisc::RequestExit(0);
	}
#endif

	::firebase::auth::Auth* auth = nullptr;
	::firebase::database::Database* database = nullptr;

	void* initialize_targets[] = {&auth, &database };

	const firebase::ModuleInitializer::InitializerFn initializers[] = {
		[](::firebase::App* app, void* data) {
		
		void** targets = reinterpret_cast<void**>(data);
		::firebase::InitResult result;
		*reinterpret_cast<::firebase::auth::Auth**>(targets[0]) =
			::firebase::auth::Auth::GetAuth(app, &result);
		return result;
		},

		[](::firebase::App* app, void* data) {

		UE_LOG(FireBase, Log, TEXT("Attempt to initialize Firebase Database."));
		void** targets = reinterpret_cast<void**>(data);
		::firebase::InitResult result;
		*reinterpret_cast<::firebase::database::Database**>(targets[0]) =
			::firebase::database::Database::GetInstance(app, &result);
		return result;
	} };

	::firebase::ModuleInitializer initializer;
	initializer.Initialize(g_firebaseApp, initialize_targets, initializers,
		sizeof(initializers) / sizeof(initializers[0]));

	if (initializer.InitializeLastResult().error() != 0)
	{
		UE_LOG(FireBase, Error, TEXT("Failed to initialize Firebase libraries: %s"), initializer.InitializeLastResult().error_message());
	}

	if (initializer.InitializeLastResult().error() != 0) {
		UE_LOG(FireBase, Error, TEXT("Failed to initialize Firebase libraries: %s"), initializer.InitializeLastResult().error_message() );
		return false;
	}

	::firebase::analytics::Initialize(*g_firebaseApp);

	return true;
}

static FString getAnalyticsEventName(AnalyticsEvent name)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("AnalyticsEvent"), true);
	if (!EnumPtr)
	{
		return TEXT("");
	}

	FString EnumName = EnumPtr->GetNameByValue((int64)name).ToString();

	FString ret;
	int32 ScopeIndex = EnumName.Find(TEXT("::"), ESearchCase::CaseSensitive);
	if (ScopeIndex != INDEX_NONE)
	{
		ret = (*EnumName.Mid(ScopeIndex + 2));
	}
	else
	{
		ret = (*EnumName);
	}

	return ret;
}

static FString getAnalyticsParamName(AnalyticsParameter name)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("AnalyticsParameter"), true);
	if (!EnumPtr)
	{
		return TEXT("");
	}

	FString EnumName = EnumPtr->GetNameByValue((int64)name).ToString();

	FString ret;
	int32 ScopeIndex = EnumName.Find(TEXT("::"), ESearchCase::CaseSensitive);
	if (ScopeIndex != INDEX_NONE)
	{
		ret = (*EnumName.Mid(ScopeIndex + 2));
	}
	else
	{
		ret = (*EnumName);
	}

	return ret;
}

void UFirebaseFunctionLibrary::LogStringEvent(AnalyticsEvent name, AnalyticsParameter parameter_name, const FString& parameter_value)
{
	firebase::analytics::LogEvent(TCHAR_TO_UTF8(*getAnalyticsEventName(name) ), TCHAR_TO_UTF8(*getAnalyticsParamName(parameter_name)), TCHAR_TO_UTF8(*parameter_value));
}

void UFirebaseFunctionLibrary::LogInt64Event(AnalyticsEvent name, AnalyticsParameter parameter_name, int64 parameter_value)
{
	firebase::analytics::LogEvent(TCHAR_TO_UTF8(*getAnalyticsEventName(name)), TCHAR_TO_UTF8(*getAnalyticsParamName(parameter_name)), (int64_t)parameter_value);
}

void UFirebaseFunctionLibrary::LogIntEvent(AnalyticsEvent name, AnalyticsParameter parameter_name, int parameter_value)
{
	firebase::analytics::LogEvent(TCHAR_TO_UTF8(*getAnalyticsEventName(name)), TCHAR_TO_UTF8(*getAnalyticsParamName(parameter_name)), parameter_value);
}

void UFirebaseFunctionLibrary::LogFloatEvent(AnalyticsEvent name, AnalyticsParameter parameter_name, float parameter_value)
{
	firebase::analytics::LogEvent(TCHAR_TO_UTF8(*getAnalyticsEventName(name)), TCHAR_TO_UTF8(*getAnalyticsParamName(parameter_name)), parameter_value);
}

void UFirebaseFunctionLibrary::LogEvent(AnalyticsEvent name)
{
	firebase::analytics::LogEvent(TCHAR_TO_UTF8(*getAnalyticsEventName(name)) );
}


void UFirebaseFunctionLibrary::LogCustomStringEvent(const FString& name, const FString& parameter_name, const FString& parameter_value)
{
	firebase::analytics::LogEvent(TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*parameter_name), TCHAR_TO_UTF8(*parameter_value));
}

void UFirebaseFunctionLibrary::LogCustomInt64Event(const FString& name, const FString& parameter_name, int64 parameter_value)
{
	firebase::analytics::LogEvent(TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*parameter_name), (int64_t)parameter_value);
}

void UFirebaseFunctionLibrary::LogCustomIntEvent(const FString& name, const FString& parameter_name, int parameter_value)
{
	firebase::analytics::LogEvent(TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*parameter_name), parameter_value);
}

void UFirebaseFunctionLibrary::LogCustomFloatEvent(const FString& name, const FString& parameter_name, float parameter_value)
{
	firebase::analytics::LogEvent(TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*parameter_name), parameter_value);
}

void UFirebaseFunctionLibrary::LogCustomEvent(const FString& name)
{
	firebase::analytics::LogEvent(TCHAR_TO_UTF8(*name) );
}

void UFirebaseFunctionLibrary::SetUserProperty(const FString& name, const FString& property)
{
	firebase::analytics::SetUserProperty(TCHAR_TO_UTF8(*name), TCHAR_TO_UTF8(*property));
}