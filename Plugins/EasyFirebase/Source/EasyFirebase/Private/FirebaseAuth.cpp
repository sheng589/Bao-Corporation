// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseAuth.h"
#include "EasyFirebase.h"
#include "firebase/app.h"
#include "FirebaseUser.h"
#include "FirebaseFutureVoid.h"
#include "FirebaseUser.h"
#include "FirebaseFutureUser.h"
#include "FirebaseFutureSignInResult.h"
#include "FirebaseCredential.h"
#include "FirebaseAuthStateListener.h"

extern ::firebase::App* g_firebaseApp;

UFirebaseAuth::UFirebaseAuth()
{
}

UFirebaseAuth* UFirebaseAuth::GetFirebaseAuth()
{
	return NewObject<UFirebaseAuth>();
}

UFirebaseUser* UFirebaseAuth::current_user()
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:current_user fail, auth is null") );
		return nullptr;
	}

	auto curUser = auth->current_user();
	if (!curUser)
	{
		return nullptr;
	}

	UFirebaseUser* ret = NewObject< UFirebaseUser>();
	ret->bindUser(curUser);

	return ret;
}

UFirebaseFutureUser* UFirebaseAuth::SignInWithCustomToken(const FString& token)
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:SignInWithCustomToken fail, auth is null"));
		return nullptr;
	}

	auto userFuture = auth->SignInWithCustomToken(TCHAR_TO_UTF8(*token));
	
	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = userFuture;

	return ret;
}

UFirebaseFutureUser* UFirebaseAuth::SignInWithCustomTokenLastResult()
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:SignInWithCustomTokenLastResult fail, auth is null"));
		return nullptr;
	}

	auto userFuture = auth->SignInWithCustomTokenLastResult();
	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = userFuture;

	return ret;
}

UFirebaseFutureUser* UFirebaseAuth::SignInWithCredential(UFirebaseCredential* credential)
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:SignInWithCredential fail, auth is null"));
		return nullptr;
	}

	auto userFuture = auth->SignInWithCredential(credential->mCredential);
	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = userFuture;

	return ret;
}

UFirebaseFutureUser* UFirebaseAuth::SignInWithCredentialLastResult()
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:SignInWithCredentialLastResult fail, auth is null"));
		return nullptr;
	}

	auto userFuture = auth->SignInWithCredentialLastResult();
	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = userFuture;

	return ret;
}

UFirebaseFutureSignInResult* UFirebaseAuth::SignInAndRetrieveDataWithCredential(UFirebaseCredential* credential)
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:SignInWithCredentialLastResult fail, auth is null"));
		return nullptr;
	}

	auto signInResultFuture = auth->SignInAndRetrieveDataWithCredential(credential->mCredential);
	UFirebaseFutureSignInResult* ret = NewObject<UFirebaseFutureSignInResult>();
	ret->mSignInFuture = signInResultFuture;

	return ret;
}

UFirebaseFutureSignInResult* UFirebaseAuth::SignInAndRetrieveDataWithCredentialLastResult()
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:SignInAndRetrieveDataWithCredentialLastResult fail, auth is null"));
		return nullptr;
	}

	auto signInResultFuture = auth->SignInAndRetrieveDataWithCredentialLastResult();
	UFirebaseFutureSignInResult* ret = NewObject<UFirebaseFutureSignInResult>();
	ret->mSignInFuture = signInResultFuture;

	return ret;
}

UFirebaseFutureUser* UFirebaseAuth::SignInAnonymously()
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:SignInAnonymously fail, auth is null"));
		return nullptr;
	}

	auto userFuture = auth->SignInAnonymously();
	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = userFuture;

	return ret;
}

UFirebaseFutureUser* UFirebaseAuth::SignInWithEmailAndPassword(const FString& email, const FString& passwd)
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:SignInWithEmailAndPassword fail, auth is null"));
		return nullptr;
	}

	auto userFuture = auth->SignInWithEmailAndPassword(TCHAR_TO_UTF8(*email), TCHAR_TO_UTF8(*passwd) );
	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = userFuture;

	return ret;
}

UFirebaseFutureUser* UFirebaseAuth::SignInWithEmailAndPasswordLastResult()
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:SignInWithEmailAndPasswordLastResult fail, auth is null"));
		return nullptr;
	}

	auto userFuture = auth->SignInWithEmailAndPasswordLastResult();
	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = userFuture;

	return ret;
}

UFirebaseFutureUser* UFirebaseAuth::CreateUserWithEmailAndPassword(const FString& email, const FString& passwd)
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:CreateUserWithEmailAndPassword fail, auth is null"));
		return nullptr;
	}

	auto userFuture = auth->CreateUserWithEmailAndPassword(TCHAR_TO_UTF8(*email), TCHAR_TO_UTF8(*passwd));
	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = userFuture;

	return ret;
}


UFirebaseFutureUser* UFirebaseAuth::CreateUserWithEmailAndPasswordLastResult()
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:CreateUserWithEmailAndPasswordLastResult fail, auth is null"));
		return nullptr;
	}

	auto userFuture = auth->CreateUserWithEmailAndPasswordLastResult();
	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = userFuture;

	return ret;
}

void UFirebaseAuth::SignOut()
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:SignOut fail, auth is null"));
		return;
	}

	auth->SignOut();
}

UFirebaseFutureVoid* UFirebaseAuth::SendPasswordResetEmail(const FString& email)
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:SendPasswordResetEmail fail, auth is null"));
		return nullptr;
	}

	auto voidFuture = auth->SendPasswordResetEmail(TCHAR_TO_UTF8(*email) );
	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = voidFuture;

	return ret;
}

UFirebaseFutureVoid* UFirebaseAuth::SendPasswordResetEmailLastResult()
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:SendPasswordResetEmailLastResult fail, auth is null"));
		return nullptr;
	}

	auto voidFuture = auth->SendPasswordResetEmailLastResult();
	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = voidFuture;

	return ret;
}

UFirebaseAuthStateListener* UFirebaseAuth::AddAuthStateListener()
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:AddAuthStateListener fail, auth is null"));
		return nullptr;
	}

	UFirebaseAuthStateListener* ret = NewObject<UFirebaseAuthStateListener>();
	auth->AddAuthStateListener(ret->mAuthStateListenerImp.Get());

	return ret;
}

void UFirebaseAuth::RemoveAuthStateListener(UFirebaseAuthStateListener* listener)
{
	::firebase::auth::Auth* auth = nullptr;
	if ((auth = ::firebase::auth::Auth::GetAuth(g_firebaseApp)) == nullptr)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:RemoveAuthStateListener fail, auth is null"));
		return;
	}

	if (!listener)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseAuth:RemoveAuthStateListener fail, listener is null"));
		return;
	}

	auth->RemoveAuthStateListener(listener->mAuthStateListenerImp.Get() );
}

UFirebaseCredential* UFirebaseAuth::GetPlayServiceCredential(const FString& serverAuthCode)
{
	firebase::auth::Credential credential = firebase::auth::PlayGamesAuthProvider::GetCredential(TCHAR_TO_UTF8(*serverAuthCode) );
	UFirebaseCredential* ret = NewObject<UFirebaseCredential>();
	ret->mCredential = credential;

	return ret;
}