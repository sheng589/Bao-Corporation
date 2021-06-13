// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FirebaseGoogleCredential.generated.h"

class UFirebaseCredential;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGogoleCredentialDelegate, bool, isSuccess, UFirebaseCredential*, credential);

/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseGoogleCredential : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UFirebaseGoogleCredential();

	~UFirebaseGoogleCredential();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RequestGoogleCredential", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "FireBase|Auth|Google")
	static UFirebaseGoogleCredential* RequestGoogleCredential();

	virtual void Activate() override;


	UPROPERTY(BlueprintAssignable)
	FGogoleCredentialDelegate OnComplete;
};
