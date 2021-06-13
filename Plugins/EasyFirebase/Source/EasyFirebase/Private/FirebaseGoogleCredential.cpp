// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseGoogleCredential.h"
#include "FirebaseCredential.h"
#include "firebase/auth/credential.h"
#include "Async/TaskGraphInterfaces.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

#include "EasyFirebase.h"
#include <set>

static std::set<UFirebaseGoogleCredential*> s_firebaseGoogleCredentialInList;

UFirebaseGoogleCredential::UFirebaseGoogleCredential()
{
}

UFirebaseGoogleCredential::~UFirebaseGoogleCredential()
{
	std::set<UFirebaseGoogleCredential*>::iterator it = s_firebaseGoogleCredentialInList.find(this);
	if (it != s_firebaseGoogleCredentialInList.end())
	{
		s_firebaseGoogleCredentialInList.erase(it);
	}
}

UFirebaseGoogleCredential* UFirebaseGoogleCredential::RequestGoogleCredential()
{
	UFirebaseGoogleCredential* ret = NewObject<UFirebaseGoogleCredential>();
	s_firebaseGoogleCredentialInList.insert(ret);
	return ret;
}

#if PLATFORM_ANDROID
static void requestAndroidGoogleLogin()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID googleSignInMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_RequestGoogleSignIn", "()V", bIsOptional);
		if (googleSignInMethod == nullptr)
		{
			UE_LOG(FireBase, Error, TEXT("AndroidThunkJava_RequestGoogleSignIn not found"));
			return;
		}

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, googleSignInMethod);
	}
}

__attribute__((visibility("default"))) extern "C" void Java_com_epicgames_ue4_FirebaseGoogleLogin_nativeGoogleSignInResult(JNIEnv* jenv, jobject thiz, jboolean isSuccess, jstring token)
{
	FString strIdToken = FJavaHelper::FStringFromParam(jenv, token);
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_epicgames_ue4_FirebaseGoogleLogin_nativeGoogleSignInResult"), STAT_FSimpleDelegateGraphTask_Java_com_epicgames_ue4_FirebaseGoogleLogin_nativeGoogleSignInResult, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				if ((bool)isSuccess)
				{
					UFirebaseCredential* pCredential = NewObject<UFirebaseCredential>();
					pCredential->mCredential = firebase::auth::GoogleAuthProvider::GetCredential(TCHAR_TO_UTF8(*strIdToken), nullptr);
					//for (size_t i = 0; i < s_firebaseGoogleCredentialInList.size(); i++)
					for(std::set<UFirebaseGoogleCredential*>::iterator it = s_firebaseGoogleCredentialInList.begin(); it != s_firebaseGoogleCredentialInList.end(); it++)
					{
						(*it)->OnComplete.Broadcast(true, pCredential);
					}
				}
				else
				{
					for (std::set<UFirebaseGoogleCredential*>::iterator it = s_firebaseGoogleCredentialInList.begin(); it != s_firebaseGoogleCredentialInList.end(); it++)
					{
						(*it)->OnComplete.Broadcast(false, nullptr);
					}
				}

				s_firebaseGoogleCredentialInList.clear();
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_epicgames_ue4_FirebaseGoogleLogin_nativeGoogleSignInResult),
				nullptr,
				ENamedThreads::GameThread
				);
}
#elif PLATFORM_IOS
extern "C" void requestIosGoogleSignIn();
extern "C" void onIosGoogleSignInCallback(bool isSuccess, const FString& strIdToken)
{
	if ((bool)isSuccess)
	{
		UFirebaseCredential* pCredential = NewObject<UFirebaseCredential>();
		pCredential->mCredential = firebase::auth::GoogleAuthProvider::GetCredential(TCHAR_TO_UTF8(*strIdToken), nullptr);
		//for (size_t i = 0; i < s_firebaseGoogleCredentialInList.size(); i++)
		for (std::set<UFirebaseGoogleCredential*>::iterator it = s_firebaseGoogleCredentialInList.begin(); it != s_firebaseGoogleCredentialInList.end(); it++)
		{
			(*it)->OnComplete.Broadcast(true, pCredential);
		}
				
	}
	else
	{
		for (std::set<UFirebaseGoogleCredential*>::iterator it = s_firebaseGoogleCredentialInList.begin(); it != s_firebaseGoogleCredentialInList.end(); it++)
		{
			(*it)->OnComplete.Broadcast(false, nullptr);
		}
	}

	s_firebaseGoogleCredentialInList.clear();
}
#endif

void UFirebaseGoogleCredential::Activate()
{
#if PLATFORM_ANDROID
	requestAndroidGoogleLogin();
#elif PLATFORM_IOS
	requestIosGoogleSignIn();
#endif
}