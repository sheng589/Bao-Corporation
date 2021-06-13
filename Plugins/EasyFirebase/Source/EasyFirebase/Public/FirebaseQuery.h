// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "firebase/database/query.h"
#include <set>
#include "FirebaseQuery.generated.h"


class UFirebaseFutureDataSnapshot;
class UFirebaseVariant;
class UFirebaseValueListener;
class UFirebaseDatabaseRef;
class UFirebaseChildListener;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class EASYFIREBASE_API UFirebaseQuery : public UObject
{
	GENERATED_BODY()
	
public:

	UFirebaseQuery();
	
	~UFirebaseQuery();
	
	UFUNCTION(BlueprintPure, Category = "FireBase|Database|Query")
	UFirebaseFutureDataSnapshot* GetValue();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|Query")
	UFirebaseFutureDataSnapshot* GetValueLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	void SetKeepSynchronized(bool keep_sync);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseQuery* OrderByChild(const FString& path);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseQuery* OrderByKey();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseQuery* OrderByPriority();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseQuery* OrderByValue();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseQuery* StartAt(UFirebaseVariant* orderValue);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseQuery* StartWithKeyAt(UFirebaseVariant* orderValue, const FString& key);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseQuery* EndAt(UFirebaseVariant* orderValue);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseQuery* EndWithKeyAt(UFirebaseVariant* orderValue, const FString& key);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseQuery* EqualTo(UFirebaseVariant* orderValue);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseQuery* EqualWithKeyTo(UFirebaseVariant* orderValue, const FString& key);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseQuery* LimitToFirst(int64 limit);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseQuery* LimitToLast(int64 limit);

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|Query")
	bool isValid();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseValueListener* AddValueListener();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	void RemoveValueListener(UFirebaseValueListener* listner);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	void RemoveAllValueListeners();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|Query")
	UFirebaseDatabaseRef* GetReference();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	UFirebaseChildListener* AddChildListener();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	void RemoveChildListener(UFirebaseChildListener* listener);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|Query")
	void RemoveAllChildListeners();

	firebase::database::Query mQuery;

private:
	
	std::set<firebase::database::ValueListener*> mValueListenerList;
	std::set< firebase::database::ChildListener*> mChildListenerList;
};
