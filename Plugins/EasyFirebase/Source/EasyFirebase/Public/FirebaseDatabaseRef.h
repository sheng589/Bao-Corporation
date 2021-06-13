// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FirebaseQuery.h"
#include "firebase/database/database_reference.h"
#include "FirebaseDatabaseRef.generated.h"

class UFirebaseFutureVoid;
class UFirebaseVariant;
/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseDatabaseRef : public UFirebaseQuery
{
	GENERATED_BODY()
	
public:

	UFirebaseDatabaseRef();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DatabaseReference")
	static UFirebaseDatabaseRef* GetRootDatabaseRef();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DatabaseReference")
	FString Key();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DatabaseReference")
	bool IsRoot();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DatabaseReference")
	bool IsDatabaseValid();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DatabaseReference")
	UFirebaseDatabaseRef* GetParent();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DatabaseReference")
	UFirebaseDatabaseRef* GetRoot();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DatabaseReference")
	UFirebaseDatabaseRef* Child(const FString& path);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|DatabaseReference")
	UFirebaseDatabaseRef* PushChild();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|DatabaseReference")
	UFirebaseFutureVoid* RemoveValue();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DatabaseReference")
	UFirebaseFutureVoid* RemoveValueLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|DatabaseReference")
	UFirebaseFutureVoid* SetPriority(UFirebaseVariant* variant);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|DatabaseReference")
	UFirebaseFutureVoid* SetPriorityLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|DatabaseReference")
	UFirebaseFutureVoid* SetValue(UFirebaseVariant* variant);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|DatabaseReference")
	UFirebaseFutureVoid* SetValueLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|DatabaseReference")
	UFirebaseFutureVoid* SetValueAndPriority(UFirebaseVariant* value, UFirebaseVariant* priority);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|DatabaseReference")
	UFirebaseFutureVoid* SetValueAndPriorityLastResult();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|DatabaseReference")
	UFirebaseFutureVoid* UpdateChildren(UFirebaseVariant* values);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|DatabaseReference")
	UFirebaseFutureVoid* UpdateChildrenLastResult();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DatabaseReference")
	FString Url();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|DatabaseReference")
	void GoOffline();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Database|DatabaseReference")
	void GoOnline();

	void setDatabaseRef(firebase::database::DatabaseReference ref);

private:

	firebase::database::DatabaseReference mDatabaseRef;
};
