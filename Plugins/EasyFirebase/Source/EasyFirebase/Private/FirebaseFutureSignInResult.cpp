// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseFutureSignInResult.h"
#include "FirebaseUser.h"
#include "Async/TaskGraphInterfaces.h"

extern UFirebaseVariant* makeFirebaseVariant(firebase::Variant v);

void makeFirebaseSignInResult(const firebase::auth::SignInResult result, FFirebaseSignInResult& signInResult)
{
	signInResult.user = NewObject<UFirebaseUser>();
	signInResult.user->mUserInterface = result.user;

	signInResult.user->mUser = result.user;

	signInResult.meta.creation_timestamp = result.meta.creation_timestamp;
	signInResult.meta.last_sign_in_timestamp = result.meta.last_sign_in_timestamp;

	signInResult.info.user_name = UTF8_TO_TCHAR(result.info.user_name.c_str());
	signInResult.info.provider_id = UTF8_TO_TCHAR(result.info.provider_id.c_str());

	for (auto it = result.info.profile.begin(); it != result.info.profile.end(); it++)
	{
		signInResult.info.profile.Add(makeFirebaseVariant(it->first), makeFirebaseVariant(it->second) );
	}
}

UFirebaseFutureSignInResult::UFirebaseFutureSignInResult()
{
}

UFirebaseFutureSignInResult::~UFirebaseFutureSignInResult()
{
	if (mSignInFuture.status() != firebase::FutureStatus::kFutureStatusInvalid)
	{
		mSignInFuture.Release();
	}
}

UFirebaseFutureSignInResult* UFirebaseFutureSignInResult::WaitFuture(UFirebaseFutureSignInResult* future)
{
	return future;
}

void UFirebaseFutureSignInResult::Activate()
{
	DECLARE_CYCLE_STAT(TEXT("FSimpleDelegateGraphTask.STAT_FSimpleDelegateGraphTask_UFirebaseFutureSignInResult_Complete"), STAT_FSimpleDelegateGraphTask_UFirebaseFutureSignInResult_Complete, STATGROUP_TaskGraphTasks);
	AddToRoot();
	mSignInFuture.OnCompletion([](const firebase::Future<firebase::auth::SignInResult>& completed_future,
		void* user_data)
		{
			UFirebaseFutureSignInResult* pThis = static_cast<UFirebaseFutureSignInResult*>(user_data);
			FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
				FSimpleDelegateGraphTask::FDelegate::CreateLambda([=]()
					{
						firebase::auth::SignInResult result = *completed_future.result();
						FFirebaseSignInResult signInResult;
						makeFirebaseSignInResult(result, signInResult);
						
						if (completed_future.error() == 0)
						{
							pThis->OnComplete.Broadcast(signInResult, 0, TEXT(""));
						}
						else
						{
							FString strErrorMsg = UTF8_TO_TCHAR(completed_future.error_message());
							pThis->OnComplete.Broadcast(FFirebaseSignInResult(), completed_future.error(), strErrorMsg);
						}
						pThis->RemoveFromRoot();
					}),
				GET_STATID(STAT_FSimpleDelegateGraphTask_UFirebaseFutureSignInResult_Complete),
						nullptr,
						ENamedThreads::GameThread
						);

		}, this);
}