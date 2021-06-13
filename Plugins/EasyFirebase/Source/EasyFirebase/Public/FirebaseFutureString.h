// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "firebase/future.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FirebaseFutureString.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FStringFinishDelegate, const FString&, data, int, errorcode, const FString&, errmsg);

/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseFutureString : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UFirebaseFutureString();

	~UFirebaseFutureString();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "WaitFuture", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "FireBase|Future|String")
	static UFirebaseFutureString* WaitFuture(UFirebaseFutureString* future);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FStringFinishDelegate OnComplete;

	firebase::Future<std::string> mStringFuture;
};
