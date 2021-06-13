// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FirebaseAuthSetting.generated.h"

/**
 * 
 */
UCLASS(transient, config = Engine)
class UFirebaseAuthSetting : public UObject
{
	GENERATED_BODY()
	

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "Facebook AppId"))
	FString AndroidFacebookAppId;

	UPROPERTY(Config, EditAnywhere, Category = Android, Meta = (DisplayName = "GooglePlay AppId"))
	FString GooglePlayAppId;

	UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "Goole Client Id"))
	FString GoogleClientId;

	UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "Goole Reversed Client Id"))
	FString GoogleReversedClientId;

	UPROPERTY(Config, EditAnywhere, Category = IOS, Meta = (DisplayName = "Facebook AppId"))
	FString IOSFacebookAppIdId;

	virtual void PostInitProperties() override;

	void saveValues(const FString& appid);
	void saveGooglePlayAppId(const FString& appid);
	
#if WITH_EDITOR
	// UObject interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
