// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "firebase/database/data_snapshot.h"
#include "firebase/future.h"
#include "FirebaseDataSnapshot.h"
#include "FirebaseFutureDataSnapshot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDataSnapshotFinishDelegate, UFirebaseDataSnapshot*, dataSnapshot, int, errorcode, const FString&, errmsg);

/**
 * 
 */
UCLASS(BlueprintType)
class EASYFIREBASE_API UFirebaseFutureDataSnapshot : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UFirebaseFutureDataSnapshot();

	~UFirebaseFutureDataSnapshot();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "WaitFuture", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "FireBase|Future|DataSnapshot")
	static UFirebaseFutureDataSnapshot* WaitFuture(UFirebaseFutureDataSnapshot* future);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FDataSnapshotFinishDelegate OnComplete;
	
	firebase::Future<firebase::database::DataSnapshot> mDataSnapshotFuture;
};
