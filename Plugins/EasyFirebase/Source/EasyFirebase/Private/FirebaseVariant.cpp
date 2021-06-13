// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseVariant.h"

UFirebaseVariant::UFirebaseVariant():DataType(VariantType::Null), Int64Value(0), FloatValue(0.0f), BoolValue(false)
{
}


UFirebaseVariant* UFirebaseVariant::CreateVariantInt64(int64 value)
{
	UFirebaseVariant* ret = NewObject<UFirebaseVariant>();
	ret->DataType = VariantType::Int64;
	ret->Int64Value = value;

	return ret;
}

UFirebaseVariant* UFirebaseVariant::CreateVariantFloat(float value)
{
	UFirebaseVariant* ret = NewObject<UFirebaseVariant>();
	ret->DataType = VariantType::Float;
	ret->FloatValue = value;

	return ret;
}

UFirebaseVariant* UFirebaseVariant::CreateVariantBool(bool value)
{
	UFirebaseVariant* ret = NewObject<UFirebaseVariant>();
	ret->DataType = VariantType::Bool;
	ret->BoolValue = value;

	return ret;
}

UFirebaseVariant* UFirebaseVariant::CreateVariantString(const FString& value)
{
	UFirebaseVariant* ret = NewObject<UFirebaseVariant>();
	ret->DataType = VariantType::String;
	ret->StringValue = value;

	return ret;
}

UFirebaseVariant* UFirebaseVariant::CreateVariantVector(const TArray<UFirebaseVariant*>& value)
{
	UFirebaseVariant* ret = NewObject<UFirebaseVariant>();
	ret->DataType = VariantType::Vector;
	ret->VectorValue = value;

	return ret;
}

UFirebaseVariant* UFirebaseVariant::CreateVariantMap(const TMap<FString, UFirebaseVariant*>& value)
{
	UFirebaseVariant* ret = NewObject<UFirebaseVariant>();
	ret->DataType = VariantType::Map;
	ret->MapValue = value;

	return ret;
}
