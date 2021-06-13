// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "firebase/future.h"
#include "firebase/auth/credential.h"
#include "FirebaseGameCenterCredential.generated.h"

class UFirebaseCredential;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGameCenterFinishDelegate, UFirebaseCredential*, Credential, int, errorcode, const FString&, errmsg);

/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseGameCenterCredential : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UFirebaseGameCenterCredential();
	~UFirebaseGameCenterCredential();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RequestGameCenterCredential", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "FireBase|Auth|IOS")
	static UFirebaseGameCenterCredential* RequestGameCenterCredential();

	virtual void Activate() override;

	void onGameCenterLoginFinish();

	UPROPERTY(BlueprintAssignable)
	FGameCenterFinishDelegate OnComplete;


	firebase::Future<firebase::auth::Credential> mCredentialFuture;
};
