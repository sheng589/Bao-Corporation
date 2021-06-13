// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "firebase/auth.h"
#include "FirebaseAuthStateListener.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAuthStateListenerDelegate);

/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseAuthStateListener : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UFirebaseAuthStateListener();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "RunAuthStateListener", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "FireBase|Database|AuthStateListener")
	static UFirebaseAuthStateListener* RunValueListener(UFirebaseAuthStateListener* listener);

	UPROPERTY(BlueprintAssignable)
	FAuthStateListenerDelegate OnEvent;

	TSharedPtr<firebase::auth::AuthStateListener> mAuthStateListenerImp;
};
