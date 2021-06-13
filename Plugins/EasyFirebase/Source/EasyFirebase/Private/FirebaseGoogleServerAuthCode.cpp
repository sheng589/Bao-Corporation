// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseGoogleServerAuthCode.h"
#include "Async/TaskGraphInterfaces.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

#include "EasyFirebase.h"
#include <set>

static std::set<UFirebaseGoogleServerAuthCode*> s_firebaseGoogleServerAuthCodeList;


#if PLATFORM_ANDROID

static void requestAndroidGoogleServerAuthCode()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		const bool bIsOptional = false;
		static jmethodID googleGameSignInMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_RequestGoogleServerAuthCode", "()V", bIsOptional);
		if (googleGameSignInMethod == nullptr)
		{
			UE_LOG(FireBase, Error, TEXT("AndroidThunkJava_RequestGoogleServerAuthCode not found"));
			return;
		}

		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, googleGameSignInMethod);
	}
}

__attribute__((visibility("default"))) extern "C" void Java_com_epicgames_ue4_FirebaseGoogleLogin_nativeGoogleGameSignInResult(JNIEnv* jenv, jobject thiz, jboolean isSuccess, jstring serverAuthCode)
{
	FString strServerAuthCode = FJavaHelper::FStringFromParam(jenv, serverAuthCode);
	
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.Java_com_epicgames_ue4_FirebaseGoogleLogin_nativeGoogleGameSignInResult"), STAT_FSimpleDelegateGraphTask_Java_com_epicgames_ue4_FirebaseGoogleLogin_nativeGoogleGameSignInResult, STATGROUP_TaskGraphTasks);
	FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				if ((bool)isSuccess)
				{
					for (std::set<UFirebaseGoogleServerAuthCode*>::iterator it = s_firebaseGoogleServerAuthCodeList.begin(); it != s_firebaseGoogleServerAuthCodeList.end(); it++)
					{
						(*it)->OnComplete.Broadcast(true, strServerAuthCode);
					}
				}
				else
				{
					for (std::set<UFirebaseGoogleServerAuthCode*>::iterator it = s_firebaseGoogleServerAuthCodeList.begin(); it != s_firebaseGoogleServerAuthCodeList.end(); it++)
					{
						(*it)->OnComplete.Broadcast(false, TEXT("") );
					}
				}
				s_firebaseGoogleServerAuthCodeList.clear();
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_Java_com_epicgames_ue4_FirebaseGoogleLogin_nativeGoogleGameSignInResult),
				nullptr,
				ENamedThreads::GameThread
				);
}


#endif

UFirebaseGoogleServerAuthCode::UFirebaseGoogleServerAuthCode()
{

}

UFirebaseGoogleServerAuthCode::~UFirebaseGoogleServerAuthCode()
{
	s_firebaseGoogleServerAuthCodeList.erase(this);
}

UFirebaseGoogleServerAuthCode* UFirebaseGoogleServerAuthCode::RequestGoogleServerAuthCode()
{
	UFirebaseGoogleServerAuthCode* ret = NewObject<UFirebaseGoogleServerAuthCode>();
	s_firebaseGoogleServerAuthCodeList.insert(ret);
	
	return ret;
}

void UFirebaseGoogleServerAuthCode::Activate()
{
#if PLATFORM_ANDROID
	requestAndroidGoogleServerAuthCode();
#endif

	
}