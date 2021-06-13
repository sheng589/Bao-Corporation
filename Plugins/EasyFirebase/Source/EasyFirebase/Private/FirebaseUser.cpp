// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseUser.h"
#include "FirebaseFutureString.h"
#include "FirebaseFutureUser.h"

UFirebaseUser::UFirebaseUser():mUser(nullptr)
{
}

void UFirebaseUser::bindUser(::firebase::auth::User* user)
{
	mUser = user;
	mUserInterface = user;
}

UFirebaseUser::~UFirebaseUser()
{
	mUserInterface = nullptr;
	mUser = nullptr;
}

UFirebaseFutureString* UFirebaseUser::GetToken(bool forceRefresh)
{
	if (!mUser)
	{
		return nullptr;
	}

	firebase::Future<std::string> result = mUser->GetToken(forceRefresh);
	UFirebaseFutureString* ret = NewObject<UFirebaseFutureString>();
	ret->mStringFuture = result;

	return ret;
}

UFirebaseFutureString* UFirebaseUser::GetTokenLastResult()
{
	if (!mUser)
	{
		return nullptr;
	}

	firebase::Future<std::string> result = mUser->GetTokenLastResult();
	UFirebaseFutureString* ret = NewObject<UFirebaseFutureString>();
	ret->mStringFuture = result;

	return ret;
}

TArray<UFirebaseUserInfoInterface*> UFirebaseUser::provider_data()
{
	if (!mUser)
	{
		return TArray<UFirebaseUserInfoInterface*>();
	}

	TArray<UFirebaseUserInfoInterface*> ret;
	const std::vector<firebase::auth::UserInfoInterface*>& userList = mUser->provider_data();
	
	for (size_t i = 0; i < userList.size(); i++)
	{
		UFirebaseUserInfoInterface* tmp = NewObject<UFirebaseUserInfoInterface>();
		tmp->mUserInterface = userList[i];

		ret.Push(tmp);
	}

	return ret;
}

UFirebaseFutureVoid* UFirebaseUser::UpdateEmail(const FString& email)
{
	if (!mUser)
	{
		return nullptr;
	}

	auto future = mUser->UpdateEmail(TCHAR_TO_UTF8(*email) );
	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = future;

	return ret;
}

UFirebaseFutureVoid* UFirebaseUser::UpdateEmailLastResult()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureVoid = mUser->UpdateEmailLastResult();

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = futureVoid;

	return ret;
}

UFirebaseFutureVoid* UFirebaseUser::UpdatePassword(const FString& passwd)
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureVoid = mUser->UpdatePassword(TCHAR_TO_UTF8(*passwd) );

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = futureVoid;

	return ret;
}


UFirebaseFutureVoid* UFirebaseUser::UpdatePasswordLastResult()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureVoid = mUser->UpdatePasswordLastResult();

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = futureVoid;

	return ret;
}

UFirebaseFutureVoid* UFirebaseUser::Reauthenticate(UFirebaseCredential* crdenntial)
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureVoid = mUser->Reauthenticate(crdenntial->mCredential);

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = futureVoid;

	return ret;
}


UFirebaseFutureVoid* UFirebaseUser::ReauthenticateLastResult()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureVoid = mUser->ReauthenticateLastResult();

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = futureVoid;

	return ret;
}


UFirebaseFutureSignInResult* UFirebaseUser::ReauthenticateAndRetrieveData(UFirebaseCredential* crdenntial)
{
	if (!mUser)
	{
		return nullptr;
	}

	auto signInResultFuture = mUser->ReauthenticateAndRetrieveData(crdenntial->mCredential);

	UFirebaseFutureSignInResult* ret = NewObject<UFirebaseFutureSignInResult>();
	ret->mSignInFuture = signInResultFuture;

	return ret;
}

UFirebaseFutureSignInResult* UFirebaseUser::ReauthenticateAndRetrieveDataLastResult()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto signInResultFuture = mUser->ReauthenticateAndRetrieveDataLastResult();

	UFirebaseFutureSignInResult* ret = NewObject<UFirebaseFutureSignInResult>();
	ret->mSignInFuture = signInResultFuture;

	return ret;
}


UFirebaseFutureVoid* UFirebaseUser::SendEmailVerification()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureVoid = mUser->SendEmailVerification();

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = futureVoid;

	return ret;
}


UFirebaseFutureVoid* UFirebaseUser::SendEmailVerificationLastResult()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureVoid = mUser->SendEmailVerificationLastResult();

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = futureVoid;

	return ret;
}


UFirebaseFutureVoid* UFirebaseUser::UpdateUserProfile(const FUserProfile& profile)
{
	if (!mUser)
	{
		return nullptr;
	}

	firebase::auth::User::UserProfile tmpProfile;
	tmpProfile.display_name = TCHAR_TO_UTF8(*profile.display_name);

	auto futureVoid = mUser->UpdateUserProfile(tmpProfile);

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = futureVoid;

	return ret;
}

UFirebaseFutureVoid* UFirebaseUser::UpdateUserProfileLastResult()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureVoid = mUser->UpdateUserProfileLastResult();

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = futureVoid;

	return ret;
}

UFirebaseFutureUser* UFirebaseUser::LinkWithCredential(UFirebaseCredential* crdenntial)
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureUser = mUser->LinkWithCredential(crdenntial->mCredential);

	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = futureUser;

	return ret;
}


UFirebaseFutureUser* UFirebaseUser::LinkWithCredentialLastResult()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureUser = mUser->LinkWithCredentialLastResult();

	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = futureUser;

	return ret;
}

UFirebaseFutureSignInResult* UFirebaseUser::LinkAndRetrieveDataWithCredential(UFirebaseCredential* crdenntial)
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureSiggInResult = mUser->LinkAndRetrieveDataWithCredential(crdenntial->mCredential);

	UFirebaseFutureSignInResult* ret = NewObject<UFirebaseFutureSignInResult>();
	ret->mSignInFuture = futureSiggInResult;

	return ret;
}

UFirebaseFutureSignInResult* UFirebaseUser::LinkAndRetrieveDataWithCredentialLastResult()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureSiggInResult = mUser->LinkAndRetrieveDataWithCredentialLastResult();

	UFirebaseFutureSignInResult* ret = NewObject<UFirebaseFutureSignInResult>();
	ret->mSignInFuture = futureSiggInResult;

	return ret;
}

UFirebaseFutureUser* UFirebaseUser::UpdatePhoneNumberCredential(UFirebaseCredential* crdenntial)
{
	if (!mUser)
	{
		return nullptr;
	}

	auto userFuture = mUser->UpdatePhoneNumberCredential(crdenntial->mCredential);

	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = userFuture;

	return ret;
}

UFirebaseFutureUser* UFirebaseUser::UpdatePhoneNumberCredentialLastResult()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto userFuture = mUser->UpdatePhoneNumberCredentialLastResult();

	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = userFuture;

	return ret;
}


UFirebaseFutureVoid* UFirebaseUser::Reload()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureVoid = mUser->Reload();

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = futureVoid;

	return ret;
}

UFirebaseFutureVoid* UFirebaseUser::ReloadLastResult()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureVoid = mUser->Reload();

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = futureVoid;

	return ret;
}

UFirebaseFutureVoid* UFirebaseUser::Delete()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureVoid = mUser->Delete();

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = futureVoid;

	return ret;
}

UFirebaseFutureVoid* UFirebaseUser::DeleteLastResult()
{
	if (!mUser)
	{
		return nullptr;
	}

	auto futureVoid = mUser->DeleteLastResult();

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = futureVoid;

	return ret;
}

FUserMetadata UFirebaseUser::metadata()
{
	if (!mUser)
	{
		return FUserMetadata();
	}

	FUserMetadata ret;
	auto meta = mUser->metadata();
	ret.creation_timestamp = meta.creation_timestamp;
	ret.last_sign_in_timestamp = meta.last_sign_in_timestamp;

	return ret;
}

bool UFirebaseUser::is_email_verified()
{
	if (!mUser)
	{
		return false;
	}

	return mUser->is_email_verified();
}

UFirebaseFutureUser* UFirebaseUser::Unlink(const FString& provider)
{
	if (!mUser)
	{
		return nullptr;
	}

	UFirebaseFutureUser* ret = NewObject<UFirebaseFutureUser>();
	ret->mUserFuture = mUser->Unlink(TCHAR_TO_UTF8(*provider));

	return ret;
}

bool UFirebaseUser::is_anonymous()
{
	if (!mUser)
	{
		return false;
	}

	return mUser->is_anonymous();
}