// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "firebase/database/data_snapshot.h"
#include "FirebaseDataSnapshot.generated.h"

class UFirebaseVariant;

/**
 * 
 */
UCLASS(BlueprintType)
class EASYFIREBASE_API UFirebaseDataSnapshot : public UObject
{
	GENERATED_BODY()
	
public:

	UFirebaseDataSnapshot();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DataSnapshot")
	bool Exists();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DataSnapshot")
	UFirebaseDataSnapshot* Child(const FString& path);

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DataSnapshot")
	TArray<UFirebaseDataSnapshot*> Children();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DataSnapshot")
	int64 ChildrenCount();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DataSnapshot")
	bool HasChildren();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DataSnapshot")
	FString Key();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DataSnapshot")
	UFirebaseVariant* Value();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DataSnapshot")
	UFirebaseVariant* Priority();

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DataSnapshot")
	bool HasChild(const FString& path);

	UFUNCTION(BlueprintPure, Category = "FireBase|Database|DataSnapshot")
	bool IsValid();
	
	firebase::database::DataSnapshot mDataSnapshot;
};
