// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseQuery.h"
#include "EasyFirebase.h"
#include "FirebaseVariant.h"
#include "FirebaseFutureDataSnapshot.h"
#include "FirebaseValueListener.h"
#include "FirebaseChildListener.h"
#include "FirebaseDatabaseRef.h"

extern firebase::Variant makeVariant(UFirebaseVariant* value);

UFirebaseQuery::UFirebaseQuery()
{

}

UFirebaseQuery::~UFirebaseQuery()
{
	if (mQuery.is_valid())
	{
		for (std::set<firebase::database::ValueListener*>::iterator it = mValueListenerList.begin(); it != mValueListenerList.end(); it++)
		{
			mQuery.RemoveValueListener(*it);
		}

		for (std::set<firebase::database::ChildListener*>::iterator it = mChildListenerList.begin(); it != mChildListenerList.end(); it++)
		{
			mQuery.RemoveChildListener(*it);
		}
	}
}

UFirebaseFutureDataSnapshot* UFirebaseQuery::GetValue()
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:GetValue fail, invalid query"));
		return nullptr;
	}

	UFirebaseFutureDataSnapshot* ret = NewObject<UFirebaseFutureDataSnapshot>();
	ret->mDataSnapshotFuture = mQuery.GetValue();
	
	return ret;
}


UFirebaseFutureDataSnapshot* UFirebaseQuery::GetValueLastResult()
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:GetValueLastResult fail, invalid query"));
		return nullptr;
	}

	UFirebaseFutureDataSnapshot* ret = NewObject<UFirebaseFutureDataSnapshot>();
	ret->mDataSnapshotFuture = mQuery.GetValueLastResult();

	return ret;
}


void UFirebaseQuery::SetKeepSynchronized(bool keep_sync)
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:SetKeepSynchronized fail, invalid query") );
		return;
	}

	mQuery.SetKeepSynchronized(keep_sync);
}


UFirebaseQuery* UFirebaseQuery::OrderByChild(const FString& path)
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:OrderByChild fail, invalid query"));
		return nullptr;
	}

	UFirebaseQuery* ret = NewObject<UFirebaseQuery>();
	ret->mQuery = mQuery.OrderByChild(TCHAR_TO_UTF8(*path) );

	return ret;
}


UFirebaseQuery* UFirebaseQuery::OrderByKey()
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:OrderByKey fail, invalid query"));
		return nullptr;
	}

	UFirebaseQuery* ret = NewObject<UFirebaseQuery>();
	ret->mQuery = mQuery.OrderByKey();

	return ret;
}

UFirebaseQuery* UFirebaseQuery::OrderByPriority()
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:OrderByPriority fail, invalid query"));
		return nullptr;
	}

	UFirebaseQuery* ret = NewObject<UFirebaseQuery>();
	ret->mQuery = mQuery.OrderByPriority();

	return ret;
}

UFirebaseQuery* UFirebaseQuery::OrderByValue()
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:OrderByValue fail, invalid query"));
		return nullptr;
	}

	UFirebaseQuery* ret = NewObject<UFirebaseQuery>();
	ret->mQuery = mQuery.OrderByValue();

	return ret;
}

UFirebaseQuery* UFirebaseQuery::StartAt(UFirebaseVariant* orderValue)
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:StartAt fail, invalid query"));
		return nullptr;
	}

	UFirebaseQuery* ret = NewObject<UFirebaseQuery>();
	ret->mQuery = mQuery.StartAt(makeVariant(orderValue) );

	return ret;
}

UFirebaseQuery* UFirebaseQuery::StartWithKeyAt(UFirebaseVariant* orderValue, const FString& key)
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:StartWithKeyAt fail, invalid query"));
		return nullptr;
	}

	UFirebaseQuery* ret = NewObject<UFirebaseQuery>();
	ret->mQuery = mQuery.StartAt(makeVariant(orderValue), TCHAR_TO_UTF8(*key) );

	return ret;
}

UFirebaseQuery* UFirebaseQuery::EndAt(UFirebaseVariant* orderValue)
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:EndAt fail, invalid query"));
		return nullptr;
	}

	UFirebaseQuery* ret = NewObject<UFirebaseQuery>();
	ret->mQuery = mQuery.EndAt(makeVariant(orderValue));

	return ret;
}

UFirebaseQuery* UFirebaseQuery::EndWithKeyAt(UFirebaseVariant* orderValue, const FString& key)
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:EndWithKeyAt fail, invalid query"));
		return nullptr;
	}

	UFirebaseQuery* ret = NewObject<UFirebaseQuery>();
	ret->mQuery = mQuery.EndAt(makeVariant(orderValue), TCHAR_TO_UTF8(*key));

	return ret;
}

UFirebaseQuery* UFirebaseQuery::EqualTo(UFirebaseVariant* orderValue)
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:EqualTo fail, invalid query"));
		return nullptr;
	}

	UFirebaseQuery* ret = NewObject<UFirebaseQuery>();
	ret->mQuery = mQuery.EqualTo(makeVariant(orderValue));

	return ret;
}

UFirebaseQuery* UFirebaseQuery::EqualWithKeyTo(UFirebaseVariant* orderValue, const FString& key)
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:EqualWithKeyTo fail, invalid query"));
		return nullptr;
	}

	UFirebaseQuery* ret = NewObject<UFirebaseQuery>();
	ret->mQuery = mQuery.EqualTo(makeVariant(orderValue), TCHAR_TO_UTF8(*key) );

	return ret;
}

UFirebaseQuery* UFirebaseQuery::LimitToFirst(int64 limit)
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:LimitToFirst fail, invalid query"));
		return nullptr;
	}

	UFirebaseQuery* ret = NewObject<UFirebaseQuery>();
	ret->mQuery = mQuery.LimitToFirst((size_t)limit);

	return ret;
}

UFirebaseQuery* UFirebaseQuery::LimitToLast(int64 limit)
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:LimitToFirst fail, invalid query"));
		return nullptr;
	}

	UFirebaseQuery* ret = NewObject<UFirebaseQuery>();
	ret->mQuery = mQuery.LimitToLast((size_t)limit);

	return ret;
}

bool UFirebaseQuery::isValid()
{
	return mQuery.is_valid();
}

UFirebaseValueListener* UFirebaseQuery::AddValueListener()
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:AddValueListener fail, invalid query"));
		return nullptr;
	}

	UFirebaseValueListener* pListener = NewObject<UFirebaseValueListener>();
	mQuery.AddValueListener(pListener->mValueListenerImp.Get() );

	mValueListenerList.insert(pListener->mValueListenerImp.Get() );

	return pListener;
}

void UFirebaseQuery::RemoveValueListener(UFirebaseValueListener* listner)
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:RemoveValueListener fail, invalid query"));
		return;
	}

	if (!listner)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:RemoveValueListener fail, listner is null"));
		return;
	}

	mQuery.RemoveValueListener(listner->mValueListenerImp.Get() );
}

void UFirebaseQuery::RemoveAllValueListeners()
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:RemoveAllValueListeners fail, invalid query"));
		return;
	}

	mQuery.RemoveAllValueListeners();
}

UFirebaseDatabaseRef* UFirebaseQuery::GetReference()
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:GetReference fail, invalid query"));
		return nullptr;
	}

	UFirebaseDatabaseRef* pRet = NewObject<UFirebaseDatabaseRef>();
	pRet->setDatabaseRef(mQuery.GetReference() );

	return pRet;
}


UFirebaseChildListener* UFirebaseQuery::AddChildListener()
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:AddChildListener fail, invalid query"));
		return nullptr;
	}

	UFirebaseChildListener* pChildListener = NewObject<UFirebaseChildListener>();
	mQuery.AddChildListener(pChildListener->mChildListenerImp.Get());

	mChildListenerList.insert(pChildListener->mChildListenerImp.Get());

	return pChildListener;
}

void UFirebaseQuery::RemoveChildListener(UFirebaseChildListener* listener)
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:RemoveChildListener fail, invalid query"));
		return;
	}

	if (!listener)
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:RemoveChildListener fail, listener is null"));
		return;
	}
	
	mQuery.RemoveChildListener(listener->mChildListenerImp.Get());
}


void UFirebaseQuery::RemoveAllChildListeners()
{
	if (!mQuery.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseQuery:RemoveAllChildListeners fail, invalid query"));
		return;
	}

	mQuery.RemoveAllChildListeners();
}