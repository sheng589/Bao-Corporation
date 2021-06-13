// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FirebaseGoogleServerAuthCode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGogoleServerAuthCodeDelegate, bool, isSuccess, const FString&, serverAuthCode);

/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseGoogleServerAuthCode : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:

	UFirebaseGoogleServerAuthCode();
	~UFirebaseGoogleServerAuthCode();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "UFirebaseGoogleServerAuthCode", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "FireBase|Auth|Google")
	static UFirebaseGoogleServerAuthCode* RequestGoogleServerAuthCode();

	virtual void Activate() override;


	UPROPERTY(BlueprintAssignable)
	FGogoleServerAuthCodeDelegate OnComplete;
};
