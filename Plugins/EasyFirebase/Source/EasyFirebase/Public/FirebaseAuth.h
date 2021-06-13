// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "firebase/auth.h"
#include "FirebaseAuth.generated.h"

class UFirebaseUser;
class UFirebaseFutureUser;
class UFirebaseCredential;
class UFirebaseFutureSignInResult;
class UFirebaseFutureVoid;
class UFirebaseAuthStateListener;

/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseAuth : public UObject
{
	GENERATED_BODY()
	
public:

	UFirebaseAuth();
	
	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|Auth")
	static UFirebaseAuth* GetFirebaseAuth();


	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|Auth")
	UFirebaseUser* current_user();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|Auth")
	UFirebaseFutureUser* SignInWithCustomToken(const FString& token);

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|Auth")
	UFirebaseFutureUser* SignInWithCustomTokenLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|Auth")
	UFirebaseFutureUser* SignInWithCredential(UFirebaseCredential* credential);

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|Auth")
	UFirebaseFutureUser* SignInWithCredentialLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|Auth")
	UFirebaseFutureSignInResult* SignInAndRetrieveDataWithCredential(UFirebaseCredential* credential);

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|Auth")
	UFirebaseFutureSignInResult* SignInAndRetrieveDataWithCredentialLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|Auth")
	UFirebaseFutureUser* SignInAnonymously();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|Auth")
	UFirebaseFutureUser* SignInWithEmailAndPassword(const FString& email, const FString& passwd);

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|Auth")
	UFirebaseFutureUser* SignInWithEmailAndPasswordLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|Auth")
	UFirebaseFutureUser* CreateUserWithEmailAndPassword(const FString& email, const FString& passwd);

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|Auth")
	UFirebaseFutureUser* CreateUserWithEmailAndPasswordLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|Auth")
	void SignOut();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|Auth")
	UFirebaseFutureVoid* SendPasswordResetEmail(const FString& email);

	UFUNCTION(BlueprintPure, Category = "FireBase|Auth|Auth")
	UFirebaseFutureVoid* SendPasswordResetEmailLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|Auth")
	UFirebaseAuthStateListener* AddAuthStateListener();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|Auth")
	void RemoveAuthStateListener(UFirebaseAuthStateListener* listener);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Auth|Auth")
	UFirebaseCredential* GetPlayServiceCredential(const FString& serverAuthCode);
	
};
