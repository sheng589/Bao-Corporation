// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FirebaseUserInfoInterface.h"
#include "FirebaseCredential.h"
#include "FirebaseFutureVoid.h"
#include "FirebaseFutureSignInResult.h"
#include "FirebaseUser.generated.h"

class UFirebaseFutureString;
class UFirebaseUser;
class UFirebaseVariant;
class UFirebaseFutureSignInResult;
class UFirebaseFutureUser;

USTRUCT(BlueprintType)
struct FUserProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase")
	FString display_name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase")
	FString photo_url;
};


/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseUser : public UFirebaseUserInfoInterface
{
	GENERATED_BODY()
public:

	UFirebaseUser();

	~UFirebaseUser();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|User")
	UFirebaseFutureString* GetToken(bool forceRefresh);

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|User")
	UFirebaseFutureString* GetTokenLastResult();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|User")
	TArray<UFirebaseUserInfoInterface*> provider_data();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* UpdateEmail(const FString& email);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* UpdateEmailLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* UpdatePassword(const FString& passwd);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* UpdatePasswordLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* Reauthenticate(UFirebaseCredential* crdenntial);

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* ReauthenticateLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureSignInResult* ReauthenticateAndRetrieveData(UFirebaseCredential* crdenntial);

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|User")
	UFirebaseFutureSignInResult* ReauthenticateAndRetrieveDataLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* SendEmailVerification();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* SendEmailVerificationLastResult();


	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* UpdateUserProfile(const FUserProfile& profile);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* UpdateUserProfileLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureUser* LinkWithCredential(UFirebaseCredential* crdenntial);

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|User")
	UFirebaseFutureUser* LinkWithCredentialLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureSignInResult* LinkAndRetrieveDataWithCredential(UFirebaseCredential* crdenntial);

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|User")
	UFirebaseFutureSignInResult* LinkAndRetrieveDataWithCredentialLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureUser* UpdatePhoneNumberCredential(UFirebaseCredential* crdenntial);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureUser* UpdatePhoneNumberCredentialLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* Reload();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* ReloadLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* Delete();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|User")
	UFirebaseFutureVoid* DeleteLastResult();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|User")
	FUserMetadata metadata();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|User")
	bool is_email_verified();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|User")
	bool is_anonymous();

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|User")
	UFirebaseFutureUser* Unlink(const FString& provider);

	void bindUser(::firebase::auth::User* user);

	firebase::auth::User* mUser;
};
