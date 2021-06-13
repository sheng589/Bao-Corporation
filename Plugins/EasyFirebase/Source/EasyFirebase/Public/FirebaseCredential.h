// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "firebase/auth/credential.h"
#include "FirebaseCredential.generated.h"

/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseCredential : public UObject
{
	GENERATED_BODY()
	
public:

	UFirebaseCredential();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|Credential")
	FString provider();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|Credential")
	bool is_valid();

	firebase::auth::Credential mCredential;
};
