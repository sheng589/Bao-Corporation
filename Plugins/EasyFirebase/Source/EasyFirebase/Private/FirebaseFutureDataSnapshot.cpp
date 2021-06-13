// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseFutureDataSnapshot.h"
#include "Async/TaskGraphInterfaces.h"

UFirebaseFutureDataSnapshot::UFirebaseFutureDataSnapshot()
{

}

UFirebaseFutureDataSnapshot::~UFirebaseFutureDataSnapshot()
{
	if (mDataSnapshotFuture.status() != firebase::FutureStatus::kFutureStatusInvalid)
	{
		mDataSnapshotFuture.Release();
	}
}

UFirebaseFutureDataSnapshot* UFirebaseFutureDataSnapshot::WaitFuture(UFirebaseFutureDataSnapshot* future)
{
	return future;
}

void UFirebaseFutureDataSnapshot::Activate()
{
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.UFirebaseFutureDataSnapshot_Complete"), STAT_FSimpleDelegateGraphTask_UFirebaseFutureDataSnapshot_Complete, STATGROUP_TaskGraphTasks);
	AddToRoot();
	mDataSnapshotFuture.OnCompletion([](const firebase::Future<firebase::database::DataSnapshot >& completed_future,
		void* user_data)
		{
			UFirebaseFutureDataSnapshot* pThis = static_cast<UFirebaseFutureDataSnapshot*>(user_data);
			FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
				FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
					{
						if (completed_future.error() == 0)
						{
							UFirebaseDataSnapshot* ret = NewObject<UFirebaseDataSnapshot>();
							ret->mDataSnapshot = *completed_future.result();
							pThis->OnComplete.Broadcast(ret, 0, TEXT("") );
						}
						else
						{
							FString strErrorMsg = UTF8_TO_TCHAR(completed_future.error_message() );
							pThis->OnComplete.Broadcast(nullptr, completed_future.error(), strErrorMsg);
						}
						pThis->RemoveFromRoot();
					}),
				GET_STATID(STAT_FSimpleDelegateGraphTask_UFirebaseFutureDataSnapshot_Complete),
						nullptr,
						ENamedThreads::GameThread
						);

		}, this);
}
