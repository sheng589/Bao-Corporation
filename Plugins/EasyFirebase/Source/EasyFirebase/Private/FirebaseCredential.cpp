// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseCredential.h"

UFirebaseCredential::UFirebaseCredential()
{

}

FString UFirebaseCredential::provider()
{
	if (!mCredential.is_valid())
	{
		return TEXT("");
	}

	return FString(UTF8_TO_TCHAR(mCredential.provider().c_str()));
}

bool UFirebaseCredential::is_valid()
{
	return mCredential.is_valid();
}