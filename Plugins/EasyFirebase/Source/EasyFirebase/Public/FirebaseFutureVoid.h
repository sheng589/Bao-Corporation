// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "firebase/future.h"
#include "FirebaseFutureVoid.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FVoidFinishDelegate, int, errcode, const FString&, errmsg);

/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseFutureVoid : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFirebaseFutureVoid();

	~UFirebaseFutureVoid();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "WaitFuture", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "FireBase|Future|void")
	static UFirebaseFutureVoid* WaitFuture(UFirebaseFutureVoid* future);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FVoidFinishDelegate OnComplete;

	firebase::Future<void> mVoidFuture;

};
