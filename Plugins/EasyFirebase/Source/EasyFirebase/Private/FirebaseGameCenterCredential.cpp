// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseGameCenterCredential.h"
#include "FirebaseCredential.h"
#include "EasyFirebase.h"

#if PLATFORM_IOS
#import <GameKit/GameKit.h>
#endif

UFirebaseGameCenterCredential::UFirebaseGameCenterCredential()
{
}

UFirebaseGameCenterCredential::~UFirebaseGameCenterCredential()
{
	if (mCredentialFuture.status() != firebase::FutureStatus::kFutureStatusInvalid)
	{
		mCredentialFuture.Release();
	}
}

UFirebaseGameCenterCredential* UFirebaseGameCenterCredential::RequestGameCenterCredential()
{
	UFirebaseGameCenterCredential* ret = NewObject<UFirebaseGameCenterCredential>();
	
	return ret;
}

void UFirebaseGameCenterCredential::onGameCenterLoginFinish()
{
#if PLATFORM_IOS
	mCredentialFuture = firebase::auth::GameCenterAuthProvider::GetCredential();
#endif
	
	if (mCredentialFuture.status() == firebase::FutureStatus::kFutureStatusInvalid)
	{
		RemoveFromRoot();
		return;
	}
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.STAT_FSimpleDelegateGraphTask_UFirebaseGameCenterCredential"), STAT_FSimpleDelegateGraphTask_UFirebaseGameCenterCredential, STATGROUP_TaskGraphTasks);
	mCredentialFuture.OnCompletion([](const firebase::Future<firebase::auth::Credential>& completed_future,
		void* user_data)
		{
			UFirebaseGameCenterCredential* pThis = static_cast<UFirebaseGameCenterCredential*>(user_data);
			FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
			FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
				{
					if (completed_future.error() == 0)
					{
						UFirebaseCredential* ret = NewObject<UFirebaseCredential>();
						ret->mCredential = *completed_future.result();
						pThis->OnComplete.Broadcast(ret, 0, TEXT(""));
					}
					else
					{
						FString strErrorMsg = UTF8_TO_TCHAR(completed_future.error_message());
						pThis->OnComplete.Broadcast(nullptr, completed_future.error(), strErrorMsg);
					}
					pThis->RemoveFromRoot();
				}),
				GET_STATID(STAT_FSimpleDelegateGraphTask_UFirebaseGameCenterCredential),
				nullptr,
				ENamedThreads::GameThread
				);

		}, this);
}

void UFirebaseGameCenterCredential::Activate()
{
#if PLATFORM_IOS
	AddToRoot();
	GKLocalPlayer* localPlayer = [GKLocalPlayer localPlayer];
	localPlayer.authenticateHandler = ^ (UIViewController * __nullable viewController, NSError * __nullable error) {
		if (error == NULL && localPlayer.isAuthenticated == TRUE) {
			NSLog(@"Firebase GameCenter Login success");
			onGameCenterLoginFinish();
		}else {
			NSLog(@"Firebase GameCenter Login fail:%@", error);
			onGameCenterLoginFinish();
		}
	};
#endif

	
}