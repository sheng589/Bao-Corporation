// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseDatabaseRef.h"
#include "firebase/app.h"
#include "firebase/database.h"
#include "firebase/database/database_reference.h"
#include "FirebaseFutureVoid.h"
#include "EasyFirebase.h"

extern firebase::Variant makeVariant(UFirebaseVariant* value);

extern ::firebase::App* g_firebaseApp;

UFirebaseDatabaseRef::UFirebaseDatabaseRef()
{
}

void UFirebaseDatabaseRef::setDatabaseRef(firebase::database::DatabaseReference ref)
{
	mDatabaseRef = ref;
	mQuery = ref;
}

UFirebaseDatabaseRef* UFirebaseDatabaseRef::GetRootDatabaseRef()
{
	firebase::database::Database *database = firebase::database::Database::GetInstance(g_firebaseApp);
	firebase::database::DatabaseReference dbref = database->GetReference();

	UFirebaseDatabaseRef* ret = NewObject<UFirebaseDatabaseRef>();
	ret->setDatabaseRef(dbref);

	return ret;
}

FString UFirebaseDatabaseRef::Key()
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:Key error: self is invalid") );
		return TEXT("");
	}

	FString strRet = UTF8_TO_TCHAR(mDatabaseRef.key() );

	return strRet;
}

bool UFirebaseDatabaseRef::IsRoot()
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:IsRoot error: self is invalid"));
		return false;
	}

	return mDatabaseRef.is_root();
}

bool UFirebaseDatabaseRef::IsDatabaseValid()
{
	return mDatabaseRef.is_valid();
}

UFirebaseDatabaseRef* UFirebaseDatabaseRef::GetParent()
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:GetParent error: self is invalid"));
		return nullptr;
	}

	UFirebaseDatabaseRef* ret = NewObject<UFirebaseDatabaseRef>();
	ret->setDatabaseRef(mDatabaseRef.GetParent());

	return ret;
}

UFirebaseDatabaseRef* UFirebaseDatabaseRef::GetRoot()
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:GetRoot error: self is invalid"));
		return nullptr;
	}

	UFirebaseDatabaseRef* ret = NewObject<UFirebaseDatabaseRef>();
	ret->setDatabaseRef(mDatabaseRef.GetRoot());

	return ret;
}


UFirebaseDatabaseRef* UFirebaseDatabaseRef::Child(const FString& path)
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:Child error: self is invalid"));
		return nullptr;
	}

	UFirebaseDatabaseRef* ret = NewObject<UFirebaseDatabaseRef>();
	ret->setDatabaseRef(mDatabaseRef.Child(TCHAR_TO_UTF8(*path) ) );

	return ret;
}

UFirebaseDatabaseRef* UFirebaseDatabaseRef::PushChild()
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:PushChild error: self is invalid"));
		return nullptr;
	}

	UFirebaseDatabaseRef* ret = NewObject<UFirebaseDatabaseRef>();
	ret->setDatabaseRef(mDatabaseRef.PushChild());

	return ret;
}

UFirebaseFutureVoid* UFirebaseDatabaseRef::RemoveValue()
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:RemoveValue error: self is invalid"));
		return nullptr;
	}

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = mDatabaseRef.RemoveValue();

	return ret;
}

UFirebaseFutureVoid* UFirebaseDatabaseRef::RemoveValueLastResult()
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:RemoveValueLastResult error: self is invalid"));
		return nullptr;
	}

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = mDatabaseRef.RemoveValueLastResult();

	return ret;
}

UFirebaseFutureVoid* UFirebaseDatabaseRef::SetPriority(UFirebaseVariant* variant)
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:SetPriority error: self is invalid"));
		return nullptr;
	}

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = mDatabaseRef.SetPriority(makeVariant(variant) );

	return ret;
}

UFirebaseFutureVoid* UFirebaseDatabaseRef::SetPriorityLastResult()
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:SetPriorityLastResult error: self is invalid"));
		return nullptr;
	}

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = mDatabaseRef.SetPriorityLastResult();

	return ret;
}

UFirebaseFutureVoid* UFirebaseDatabaseRef::SetValue(UFirebaseVariant* variant)
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:SetValue error: self is invalid"));
		return nullptr;
	}

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = mDatabaseRef.SetValue(makeVariant(variant));

	return ret;
}

UFirebaseFutureVoid* UFirebaseDatabaseRef::SetValueLastResult()
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:SetValueLastResult error: self is invalid"));
		return nullptr;
	}

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = mDatabaseRef.SetValueLastResult();

	return ret;
}

UFirebaseFutureVoid* UFirebaseDatabaseRef::SetValueAndPriority(UFirebaseVariant* value, UFirebaseVariant* priority)
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:SetValueAndPriority error: self is invalid"));
		return nullptr;
	}

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = mDatabaseRef.SetValueAndPriority(makeVariant(value), makeVariant(priority) );

	return ret;
}

UFirebaseFutureVoid* UFirebaseDatabaseRef::SetValueAndPriorityLastResult()
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:SetValueAndPriorityLastResult error: self is invalid"));
		return nullptr;
	}

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = mDatabaseRef.SetValueAndPriorityLastResult();

	return ret;
}

UFirebaseFutureVoid* UFirebaseDatabaseRef::UpdateChildren(UFirebaseVariant* values)
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:UpdateChildren error: self is invalid"));
		return nullptr;
	}

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = mDatabaseRef.UpdateChildren(makeVariant(values));

	return ret;
}

UFirebaseFutureVoid* UFirebaseDatabaseRef::UpdateChildrenLastResult()
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:UpdateChildrenLastResult error: self is invalid"));
		return nullptr;
	}

	UFirebaseFutureVoid* ret = NewObject<UFirebaseFutureVoid>();
	ret->mVoidFuture = mDatabaseRef.UpdateChildrenLastResult();

	return ret;
}

FString UFirebaseDatabaseRef::Url()
{
	if (!mDatabaseRef.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDatabaseRef:Url error: self is invalid"));
		return TEXT("");
	}

	FString strRet =  UTF8_TO_TCHAR(mDatabaseRef.url().c_str() );

	return strRet;
}

void UFirebaseDatabaseRef::GoOffline()
{
	mDatabaseRef.GoOffline();
}

void UFirebaseDatabaseRef::GoOnline()
{
	mDatabaseRef.GoOnline();
}