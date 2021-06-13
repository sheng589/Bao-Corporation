// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FirebaseVariant.generated.h"


UENUM(BlueprintType)
enum class VariantType : uint8
{
	Null 	UMETA(DisplayName = "Null"),
	Int64 	UMETA(DisplayName = "Int64"),
	Float 	UMETA(DisplayName = "Float"),
	Bool 	UMETA(DisplayName = "Bool"),
	String 	UMETA(DisplayName = "String"),
	Vector 	UMETA(DisplayName = "Vector"),
	Map 	UMETA(DisplayName = "Map"),
};

/**
 * 
 */
UCLASS(BlueprintType)
class EASYFIREBASE_API UFirebaseVariant : public UObject
{
	GENERATED_BODY()
	
public:

	UFirebaseVariant();

	UFUNCTION(BlueprintPure, Category = "FireBase|Variant")
	static UFirebaseVariant* CreateVariantInt64(int64 value);

	UFUNCTION(BlueprintPure, Category = "FireBase|Variant")
	static UFirebaseVariant* CreateVariantFloat(float value);

	UFUNCTION(BlueprintPure, Category = "FireBase|Variant")
	static UFirebaseVariant* CreateVariantBool(bool value);

	UFUNCTION(BlueprintPure, Category = "FireBase|Variant")
	static UFirebaseVariant* CreateVariantString(const FString& value);

	UFUNCTION(BlueprintPure, Category = "FireBase|Variant")
	static UFirebaseVariant* CreateVariantVector(const TArray<UFirebaseVariant*>& value);

	UFUNCTION(BlueprintPure, Category = "FireBase|Variant")
	static UFirebaseVariant* CreateVariantMap(const TMap<FString, UFirebaseVariant*>& value);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Variant")
	VariantType DataType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Variant")
	int64 Int64Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Variant")
	float FloatValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Variant")
	bool BoolValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Variant")
	FString StringValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Variant")
	TArray<UFirebaseVariant*> VectorValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBase|Variant")
	TMap<FString, UFirebaseVariant*> MapValue;
};
