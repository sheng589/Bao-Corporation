// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FirebaseFacebookCredential.generated.h"

class UFirebaseCredential;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFacebookCredentialDelegate, bool, isSuccess, UFirebaseCredential*, credential);

/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseFacebookCredential : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UFirebaseFacebookCredential();

	~UFirebaseFacebookCredential();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RequestFacebookCredential", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "FireBase|Auth|Facebook")
	static UFirebaseFacebookCredential* RequestFacebookCredential();

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FFacebookCredentialDelegate OnComplete;
};
