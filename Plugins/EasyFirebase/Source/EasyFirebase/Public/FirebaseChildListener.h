// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "firebase/database/listener.h"
#include "FirebaseDataSnapshot.h"
#include "FirebaseValueListener.h"
#include "FirebaseChildListener.generated.h"

struct FCancelParam;

USTRUCT(BlueprintType)
struct FChildEventParam
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase")
		UFirebaseDataSnapshot* DataSnapshot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase")
		FString PreviousSiblingKey;
};

UENUM(BlueprintType)
enum class ChildEventType : uint8
{
	Added 	UMETA(DisplayName = "Added"),
	Changed 	UMETA(DisplayName = "Changed"),
	Moved 	UMETA(DisplayName = "Moved"),
	Removed 	UMETA(DisplayName = "Removed"),
	Cancelled 	UMETA(DisplayName = "Cancelled"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FChildListenerDelegate, ChildEventType, eventType, FChildEventParam, addedCtx, FChildEventParam, changedCtx, FChildEventParam, movedCtx, UFirebaseDataSnapshot*, removedCtx,  FCancelParam, cancel);

/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseChildListener : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UFirebaseChildListener();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RunChildListener", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "FireBase|Database|ChildListener")
		static UFirebaseChildListener* RunChildListener(UFirebaseChildListener* listener);

	UPROPERTY(BlueprintAssignable)
		FChildListenerDelegate OnEvent;

	TSharedPtr<firebase::database::ChildListener> mChildListenerImp;
};
