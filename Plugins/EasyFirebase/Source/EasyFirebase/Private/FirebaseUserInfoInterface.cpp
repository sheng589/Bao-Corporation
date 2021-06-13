// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseUserInfoInterface.h"

UFirebaseUserInfoInterface::UFirebaseUserInfoInterface()
{
	mUserInterface = nullptr;
}

UFirebaseUserInfoInterface::~UFirebaseUserInfoInterface()
{
}

FString UFirebaseUserInfoInterface::uid()
{
	if (!mUserInterface)
	{
		return TEXT("");
	}

	FString ret = UTF8_TO_TCHAR(mUserInterface->uid().c_str() );
	return ret;
}

FString UFirebaseUserInfoInterface::email()
{
	if (!mUserInterface)
	{
		return TEXT("");
	}

	FString ret = UTF8_TO_TCHAR(mUserInterface->email().c_str());
	return ret;
}

FString UFirebaseUserInfoInterface::display_name()
{
	if (!mUserInterface)
	{
		return TEXT("");
	}

	FString ret = UTF8_TO_TCHAR(mUserInterface->display_name().c_str());
	return ret;
}

FString UFirebaseUserInfoInterface::photo_url()
{
	if (!mUserInterface)
	{
		return TEXT("");
	}

	FString ret = UTF8_TO_TCHAR(mUserInterface->photo_url().c_str());
	return ret;
}

FString UFirebaseUserInfoInterface::provider_id()
{
	if (!mUserInterface)
	{
		return TEXT("");
	}

	FString ret = UTF8_TO_TCHAR(mUserInterface->provider_id().c_str());
	return ret;
}

FString UFirebaseUserInfoInterface::phone_number()
{
	if (!mUserInterface)
	{
		return TEXT("");
	}

	FString ret = UTF8_TO_TCHAR(mUserInterface->phone_number().c_str());
	return ret;
}