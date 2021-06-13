// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseFutureVoid.h"

UFirebaseFutureVoid::UFirebaseFutureVoid()
{
}

UFirebaseFutureVoid::~UFirebaseFutureVoid()
{
	if (mVoidFuture.status() != firebase::FutureStatus::kFutureStatusInvalid)
	{
		mVoidFuture.Release();
	}
}

UFirebaseFutureVoid* UFirebaseFutureVoid::WaitFuture(UFirebaseFutureVoid* future)
{
	return future;
}

void UFirebaseFutureVoid::Activate()
{
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.STAT_FSimpleDelegateGraphTask_UFirebaseFutureVoid_Complete"), STAT_FSimpleDelegateGraphTask_UFirebaseFutureVoid_Complete, STATGROUP_TaskGraphTasks);
	AddToRoot();
	mVoidFuture.OnCompletion([](const firebase::Future<void>& completed_future,
		void* user_data)
		{
			UFirebaseFutureVoid* pThis = static_cast<UFirebaseFutureVoid*>(user_data);
			FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
				FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
					{
						if (completed_future.error() == 0)
						{
							pThis->OnComplete.Broadcast(0, TEXT("") );
						}
						else
						{
							FString strErrorMsg = UTF8_TO_TCHAR(completed_future.error_message());
							pThis->OnComplete.Broadcast(completed_future.error(), strErrorMsg);
						}
						pThis->RemoveFromRoot();
					}),
				GET_STATID(STAT_FSimpleDelegateGraphTask_UFirebaseFutureVoid_Complete),
						nullptr,
						ENamedThreads::GameThread
						);

		}, this);
}