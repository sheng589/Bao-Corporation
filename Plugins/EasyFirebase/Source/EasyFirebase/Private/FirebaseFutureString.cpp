// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseFutureString.h"
#include "Async/TaskGraphInterfaces.h"

UFirebaseFutureString::UFirebaseFutureString()
{
}

UFirebaseFutureString::~UFirebaseFutureString()
{
	if (mStringFuture.status() != firebase::FutureStatus::kFutureStatusInvalid)
	{
		mStringFuture.Release();
	}
}

UFirebaseFutureString* UFirebaseFutureString::WaitFuture(UFirebaseFutureString* future)
{
	return future;
}

void UFirebaseFutureString::Activate()
{
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.STAT_FSimpleDelegateGraphTask_UFirebaseFutureString_Complete"), STAT_FSimpleDelegateGraphTask_UFirebaseFutureString_Complete, STATGROUP_TaskGraphTasks);
	AddToRoot();
	mStringFuture.OnCompletion([](const firebase::Future<std::string>& completed_future,
		void* user_data)
		{
			UFirebaseFutureString* pThis = static_cast<UFirebaseFutureString*>(user_data);
			FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
				FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
					{
						std::string strResult = *completed_future.result();
						if (completed_future.error() == 0)
						{
							pThis->OnComplete.Broadcast(FString(UTF8_TO_TCHAR(strResult.c_str() )), 0, TEXT(""));
						}
						else
						{
							FString strErrorMsg = UTF8_TO_TCHAR(completed_future.error_message());
							pThis->OnComplete.Broadcast(TEXT(""), completed_future.error(), strErrorMsg);
						}
						pThis->RemoveFromRoot();
					}),
				GET_STATID(STAT_FSimpleDelegateGraphTask_UFirebaseFutureString_Complete),
						nullptr,
						ENamedThreads::GameThread
						);

		}, this);
}