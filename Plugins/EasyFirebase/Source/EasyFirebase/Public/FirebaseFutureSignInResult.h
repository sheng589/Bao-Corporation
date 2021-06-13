// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "firebase/auth/user.h"
#include "FirebaseVariant.h"
#include "FirebaseFutureSignInResult.generated.h"

class UFirebaseUser;

USTRUCT(BlueprintType)
struct FAdditionalUserInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Auth|AdditionalUserInfo")
	FString provider_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Auth|AdditionalUserInfo")
	FString user_name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Auth|AdditionalUserInfo")
	TMap<UFirebaseVariant*, UFirebaseVariant*> profile;
};

USTRUCT(BlueprintType)
struct FUserMetadata
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Auth|UserMetadata")
	int64 last_sign_in_timestamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Auth|UserMetadata")
	int64 creation_timestamp;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FFirebaseSignInResult
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Auth|SignInResult")
	UFirebaseUser* user;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Auth|SignInResult")
	FAdditionalUserInfo info;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Auth|SignInResult")
	FUserMetadata meta;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSignInResultFinishDelegate, FFirebaseSignInResult, SignInResult, int, errorcode, const FString&, errmsg);

/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseFutureSignInResult : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFirebaseFutureSignInResult();

	~UFirebaseFutureSignInResult();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "WaitFuture", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "FireBase|Future|SignInResult")
	static UFirebaseFutureSignInResult* WaitFuture(UFirebaseFutureSignInResult* future);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FSignInResultFinishDelegate OnComplete;

	firebase::Future<firebase::auth::SignInResult> mSignInFuture;

	
};
