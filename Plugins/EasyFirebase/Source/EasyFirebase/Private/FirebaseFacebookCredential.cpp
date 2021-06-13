// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseFacebookCredential.h"
#include "FirebaseCredential.h"
#include "firebase/auth/credential.h"
#include "Async/TaskGraphInterfaces.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

#include "EasyFirebase.h"
#include <set>

static std::set<UFirebaseFacebookCredential*> s_firebaseFacebookCredentialInList;

UFirebaseFacebookCredential::UFirebaseFacebookCredential()
{

}

UFirebaseFacebookCredential::~UFirebaseFacebookCredential()
{
	std::set<UFirebaseFacebookCredential*>::iterator it = s_firebaseFacebookCredentialInList.find(this);
	if (it != s_firebaseFacebookCredentialInList.end())
	{
		s_firebaseFacebookCredentialInList.erase(it);
	}
}

UFirebaseFacebookCredential* UFirebaseFacebookCredential::RequestFacebookCredential()
{
	UFirebaseFacebookCredential* ret = NewObject<UFirebaseFacebookCredential>();
	s_firebaseFacebookCredentialInList.insert(ret);
	return ret;
}

#if PLATFORM_ANDROID
static void requestAndroidFacebookLogin()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID facebookSignInMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_RequestFacebookSignIn", "()V", bIsOptional);
		if (facebookSignInMethod == nullptr)
		{
			UE_LOG(FireBase, Error, TEXT("AndroidThunkJava_RequestFacebookSignIn not found"));
			return;
		}

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, facebookSignInMethod);
	}
}

__attribute__((visibility("default"))) extern "C" void Java_com_firebasehelper_FirebaseFacebookLogin_nativeFacebookSignInResult(JNIEnv* jenv, jobject thiz, jboolean isSuccess, jstring token)
{
	const char* charsAccessToken = jenv->GetStringUTFChars(token, 0);
	FString strAccessToken = FString(UTF8_TO_TCHAR(charsAccessToken));
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_firebasehelper_FirebaseFacebookLogin_nativeFacebookSignInResult"), STAT_FSimpleDelegateGraphTask_Java_com_firebasehelper_FirebaseFacebookLogin_nativeFacebookSignInResult, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				if ((bool)isSuccess)
				{
					UFirebaseCredential* pCredential = NewObject<UFirebaseCredential>();
					pCredential->mCredential = firebase::auth::FacebookAuthProvider::GetCredential(TCHAR_TO_UTF8(*strAccessToken) );
					
					for (std::set<UFirebaseFacebookCredential*>::iterator it = s_firebaseFacebookCredentialInList.begin(); it != s_firebaseFacebookCredentialInList.end(); it++)
					{
						(*it)->OnComplete.Broadcast(true, pCredential);
					}
				}
				else
				{
					for (std::set<UFirebaseFacebookCredential*>::iterator it = s_firebaseFacebookCredentialInList.begin(); it != s_firebaseFacebookCredentialInList.end(); it++)
					{
						(*it)->OnComplete.Broadcast(false, nullptr);
					}
				}

				s_firebaseFacebookCredentialInList.clear();
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_firebasehelper_FirebaseFacebookLogin_nativeFacebookSignInResult),
				nullptr,
				ENamedThreads::GameThread
				);
}

#elif PLATFORM_IOS
extern "C" void requestIosFacebookSignIn();
extern "C" void onIosFacebookSignInCallback(bool isSuccess, const FString& strAccessToken)
{
	if ((bool)isSuccess)
	{
		UFirebaseCredential* pCredential = NewObject<UFirebaseCredential>();
		pCredential->mCredential = firebase::auth::FacebookAuthProvider::GetCredential(TCHAR_TO_UTF8(*strAccessToken));
		
		for (std::set<UFirebaseFacebookCredential*>::iterator it = s_firebaseFacebookCredentialInList.begin(); it != s_firebaseFacebookCredentialInList.end(); it++)
		{
			(*it)->OnComplete.Broadcast(true, pCredential);
		}

}
	else
	{
		for (std::set<UFirebaseFacebookCredential*>::iterator it = s_firebaseFacebookCredentialInList.begin(); it != s_firebaseFacebookCredentialInList.end(); it++)
		{
			(*it)->OnComplete.Broadcast(false, nullptr);
		}
	}

	s_firebaseFacebookCredentialInList.clear();
}
#endif

void UFirebaseFacebookCredential::Activate()
{
#if PLATFORM_ANDROID
	requestAndroidFacebookLogin();
#elif PLATFORM_IOS
	requestIosFacebookSignIn();
#endif
}