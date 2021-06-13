// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "firebase/database/listener.h"
#include "FirebaseDataSnapshot.h"
#include "FirebaseValueListener.generated.h"

USTRUCT(BlueprintType)
struct FCancelParam
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Database")
	int ErrorCode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Database")
	FString ErrorMessage;
};

UENUM(BlueprintType)
enum class ValueEventType : uint8
{
	Changed 	UMETA(DisplayName = "Changed"),
	Cancelled 	UMETA(DisplayName = "Cancelled"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FValueListenerDelegate, ValueEventType, eventType, UFirebaseDataSnapshot*, dataSnapshot, FCancelParam, cancel);

/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseValueListener : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UFirebaseValueListener();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RunValueListener", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "FireBase|Database|ValueListener")
	static UFirebaseValueListener* RunValueListener(UFirebaseValueListener* listener);
	
	UPROPERTY(BlueprintAssignable)
	FValueListenerDelegate OnEvent;
	
	TSharedPtr<firebase::database::ValueListener> mValueListenerImp;
};
