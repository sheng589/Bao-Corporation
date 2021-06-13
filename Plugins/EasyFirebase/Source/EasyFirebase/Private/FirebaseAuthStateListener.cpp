// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseAuthStateListener.h"
#include "Async/TaskGraphInterfaces.h"

class AuthStateListener :public firebase::auth::AuthStateListener
{
public:

	AuthStateListener(UFirebaseAuthStateListener* cb):mCb(cb)
	{
	}

	virtual void OnAuthStateChanged(firebase::auth::Auth* auth)
	{
		DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.OnAuthStateChanged"), STAT_FSimpleDelegateGraphTask_OnAuthStateChanged, STATGROUP_TaskGraphTasks);
		FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
			{
				mCb->OnEvent.Broadcast();
			}),
		GET_STATID(STAT_FSimpleDelegateGraphTask_OnAuthStateChanged),
				nullptr,
				ENamedThreads::GameThread
				);
	}

private:

	UFirebaseAuthStateListener* mCb;
};


UFirebaseAuthStateListener::UFirebaseAuthStateListener()
{
	mAuthStateListenerImp = TSharedPtr<firebase::auth::AuthStateListener>(new AuthStateListener(this) );
}

UFirebaseAuthStateListener* UFirebaseAuthStateListener::RunValueListener(UFirebaseAuthStateListener* listener)
{
	return listener;
}