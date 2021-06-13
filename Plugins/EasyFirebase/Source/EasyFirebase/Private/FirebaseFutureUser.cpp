// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseFutureUser.h"
#include "FirebaseUser.h"
#include "Async/TaskGraphInterfaces.h"
#include "FirebaseFutureVoid.h"
#include "FirebaseFutureUser.h"
#include "EasyFirebase.h"

UFirebaseFutureUser::UFirebaseFutureUser()
{
}

UFirebaseFutureUser::~UFirebaseFutureUser()
{
	if (mUserFuture.status() != firebase::FutureStatus::kFutureStatusInvalid)
	{
		mUserFuture.Release();
	}
}

UFirebaseFutureUser* UFirebaseFutureUser::WaitFuture(UFirebaseFutureUser* future)
{
	return future;
}

void UFirebaseFutureUser::Activate()
{
	
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.STAT_FSimpleDelegateGraphTask_UFirebaseFutureUser_Complete"), STAT_FSimpleDelegateGraphTask_UFirebaseFutureUser_Complete, STATGROUP_TaskGraphTasks);
	AddToRoot();
	mUserFuture.OnCompletion([](const firebase::Future<firebase::auth::User*>& completed_future,
		void* user_data)
		{
			UFirebaseFutureUser* pThis = static_cast<UFirebaseFutureUser*>(user_data);
			FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
				FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
					{
						firebase::auth::User* pUser = *completed_future.result();
						if (completed_future.error() == 0)
						{
							UFirebaseUser* pFirebaseUser = NewObject<UFirebaseUser>();
							pFirebaseUser->bindUser(pUser);
							
							pThis->OnComplete.Broadcast(pFirebaseUser, 0, TEXT(""));
						}
						else
						{
							FString strErrorMsg = UTF8_TO_TCHAR(completed_future.error_message());
							pThis->OnComplete.Broadcast(nullptr, completed_future.error(), strErrorMsg);
						}
						pThis->RemoveFromRoot();
					}),
				GET_STATID(STAT_FSimpleDelegateGraphTask_UFirebaseFutureUser_Complete),
						nullptr,
						ENamedThreads::GameThread
						);

		}, this);
}