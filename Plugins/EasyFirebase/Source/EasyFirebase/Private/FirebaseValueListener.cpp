// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseValueListener.h"
#include "FirebaseQuery.h"
#include "Async/TaskGraphInterfaces.h"

class ValueListenerImp :public firebase::database::ValueListener
{
public:

	ValueListenerImp(UFirebaseValueListener* cb) :mCb(cb)
	{
	}

	~ValueListenerImp()
	{

	}

	void OnValueChanged(const firebase::database::DataSnapshot& snapshot) override
	{
		DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.OnValueChanged"), STAT_FSimpleDelegateGraphTask_OnValueChanged, STATGROUP_TaskGraphTasks);

		FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
			FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
				{
					UFirebaseDataSnapshot* pSnapshot = NewObject<UFirebaseDataSnapshot>();
					pSnapshot->mDataSnapshot = snapshot;
					mCb->OnEvent.Broadcast(ValueEventType::Changed, pSnapshot, FCancelParam() );
				}),
			GET_STATID(STAT_FSimpleDelegateGraphTask_OnValueChanged),
					nullptr,
					ENamedThreads::GameThread
					);
	}
	void OnCancelled(const firebase::database::Error& error_code, const char* error_message) override
	{
		DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.OnCancelled"), STAT_FSimpleDelegateGraphTask_OnCancelled, STATGROUP_TaskGraphTasks);

		FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
			FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
				{
					FCancelParam param;
					param.ErrorCode = error_code;
					if (error_message)
					{
						param.ErrorMessage = UTF8_TO_TCHAR(error_message);
					}
					mCb->OnEvent.Broadcast(ValueEventType::Cancelled, nullptr, param);
				}),
			GET_STATID(STAT_FSimpleDelegateGraphTask_OnCancelled),
					nullptr,
					ENamedThreads::GameThread
					);
	}

private:

	UFirebaseValueListener* mCb;
};


UFirebaseValueListener* UFirebaseValueListener::RunValueListener(UFirebaseValueListener* listener)
{
	return listener;
}

UFirebaseValueListener::UFirebaseValueListener()
{
	mValueListenerImp = TSharedPtr<firebase::database::ValueListener>(new ValueListenerImp(this));
}
