// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "firebase/auth/user.h"
#include "FirebaseUserInfoInterface.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class EASYFIREBASE_API UFirebaseUserInfoInterface : public UObject
{
	GENERATED_BODY()
	
public:

	UFirebaseUserInfoInterface();

	~UFirebaseUserInfoInterface();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|UserInfoInterface")
	FString uid();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|UserInfoInterface")
	FString email();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|UserInfoInterface")
	FString display_name();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|UserInfoInterface")
	FString photo_url();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|UserInfoInterface")
	FString provider_id();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|UserInfoInterface")
	FString phone_number();

	firebase::auth::UserInfoInterface* mUserInterface;
};
