// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseChildListener.h"
#include "FirebaseValueListener.h"
#include "Async/TaskGraphInterfaces.h"

class ChildListenerImp :public firebase::database::ChildListener
{
public:

	ChildListenerImp(UFirebaseChildListener* listener):mChildListener(listener)
	{
	}

	virtual void OnChildAdded(const firebase::database::DataSnapshot& snapshot,
		const char* previous_sibling_key)
	{
		DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.OnChildAdded"), STAT_FSimpleDelegateGraphTask_OnChildAdded, STATGROUP_TaskGraphTasks);
		FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
			FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
				{
					UFirebaseDataSnapshot* pSnapshot = NewObject<UFirebaseDataSnapshot>();
					pSnapshot->mDataSnapshot = snapshot;

					FChildEventParam param;
					param.DataSnapshot = pSnapshot;
					if (previous_sibling_key)
					{
						param.PreviousSiblingKey = UTF8_TO_TCHAR(previous_sibling_key);
					}
					mChildListener->OnEvent.Broadcast(ChildEventType::Added, param, FChildEventParam(), FChildEventParam(), nullptr, FCancelParam() );
				}),
			GET_STATID(STAT_FSimpleDelegateGraphTask_OnChildAdded),
					nullptr,
					ENamedThreads::GameThread
					);
	}

	virtual void OnChildChanged(const firebase::database::DataSnapshot& snapshot,
		const char* previous_sibling_key)
	{
		DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.OnChildChanged"), STAT_FSimpleDelegateGraphTask_OnChildChanged, STATGROUP_TaskGraphTasks);
		FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
			FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
				{
					UFirebaseDataSnapshot* pSnapshot = NewObject<UFirebaseDataSnapshot>();
					pSnapshot->mDataSnapshot = snapshot;

					FChildEventParam param;
					param.DataSnapshot = pSnapshot;
					if (previous_sibling_key)
					{
						param.PreviousSiblingKey = UTF8_TO_TCHAR(previous_sibling_key);
					}
					mChildListener->OnEvent.Broadcast(ChildEventType::Changed, FChildEventParam(), param, FChildEventParam(), nullptr, FCancelParam());
				}),
			GET_STATID(STAT_FSimpleDelegateGraphTask_OnChildChanged),
					nullptr,
					ENamedThreads::GameThread
					);
	}

	virtual void OnChildMoved(const firebase::database::DataSnapshot& snapshot,
		const char* previous_sibling_key)
	{
		DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.OnChildMoved"), STAT_FSimpleDelegateGraphTask_OnChildMoved, STATGROUP_TaskGraphTasks);
		FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
			FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
				{
					UFirebaseDataSnapshot* pSnapshot = NewObject<UFirebaseDataSnapshot>();
					pSnapshot->mDataSnapshot = snapshot;

					FChildEventParam param;
					param.DataSnapshot = pSnapshot;
					if (previous_sibling_key)
					{
						param.PreviousSiblingKey = UTF8_TO_TCHAR(previous_sibling_key);
					}
					mChildListener->OnEvent.Broadcast(ChildEventType::Moved, FChildEventParam(), FChildEventParam(), param, nullptr, FCancelParam());
				}),
			GET_STATID(STAT_FSimpleDelegateGraphTask_OnChildMoved),
					nullptr,
					ENamedThreads::GameThread
					);
	}

	virtual void OnChildRemoved(const firebase::database::DataSnapshot& snapshot)
	{
		DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.OnChildRemoved"), STAT_FSimpleDelegateGraphTask_OnChildRemoved, STATGROUP_TaskGraphTasks);
		FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
			FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
				{
					UFirebaseDataSnapshot* pSnapshot = NewObject<UFirebaseDataSnapshot>();
					pSnapshot->mDataSnapshot = snapshot;

					
					mChildListener->OnEvent.Broadcast(ChildEventType::Removed, FChildEventParam(), FChildEventParam(), FChildEventParam(), pSnapshot, FCancelParam());
				}),
			GET_STATID(STAT_FSimpleDelegateGraphTask_OnChildRemoved),
					nullptr,
					ENamedThreads::GameThread
					);
	}

	virtual void OnCancelled(const firebase::database::Error& error, const char* error_message)
	{
		DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.OnCancelled"), STAT_FSimpleDelegateGraphTask_OnCancelled, STATGROUP_TaskGraphTasks);

		FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
			FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
				{
					FCancelParam param;
					param.ErrorCode = error;
					if (error_message)
					{
						param.ErrorMessage = UTF8_TO_TCHAR(error_message);
					}
					mChildListener->OnEvent.Broadcast(ChildEventType::Cancelled, FChildEventParam(), FChildEventParam(), FChildEventParam(), nullptr, param);
				}),
			GET_STATID(STAT_FSimpleDelegateGraphTask_OnCancelled),
					nullptr,
					ENamedThreads::GameThread
					);
	}

private:

	UFirebaseChildListener* mChildListener;
};


UFirebaseChildListener::UFirebaseChildListener()
{
	mChildListenerImp = TSharedPtr<firebase::database::ChildListener>(new ChildListenerImp(this) );
}

UFirebaseChildListener* UFirebaseChildListener::RunChildListener(UFirebaseChildListener* listener)
{
	return listener;
}
