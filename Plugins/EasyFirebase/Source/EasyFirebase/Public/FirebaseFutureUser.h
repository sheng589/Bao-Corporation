// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "firebase/auth/user.h"
#include "FirebaseFutureUser.generated.h"

class UFirebaseUser;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUserFinishDelegate, UFirebaseUser*, user, int, errorcode, const FString&, errmsg);

/**
 * 
 */
UCLASS(BlueprintType)
class EASYFIREBASE_API UFirebaseFutureUser : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFirebaseFutureUser();

	~UFirebaseFutureUser();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "WaitFuture", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "FireBase|Future|User")
	static UFirebaseFutureUser* WaitFuture(UFirebaseFutureUser* future);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FUserFinishDelegate OnComplete;

	firebase::Future<firebase::auth::User*> mUserFuture;
};
