// EasyFirebase - unreal engine 4 firebase plugin Copyright (C) 2020 feixuwu <feixuwu@outlook.com> All Rights Reserved.


#include "FirebaseDataSnapshot.h"
#include "EasyFirebase.h"
#include "firebase/variant.h"
#include "FirebaseVariant.h"


UFirebaseDataSnapshot::UFirebaseDataSnapshot()
{
}

bool UFirebaseDataSnapshot::Exists()
{
	return mDataSnapshot.exists();
}

UFirebaseDataSnapshot* UFirebaseDataSnapshot::Child(const FString& path)
{
	if (!mDataSnapshot.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDataSnapshot:Child self is nullptr:%s"), *path);
		return nullptr;
	}

	firebase::database::DataSnapshot child = mDataSnapshot.Child(TCHAR_TO_UTF8(*path));

	UFirebaseDataSnapshot* ret = NewObject<UFirebaseDataSnapshot>();
	ret->mDataSnapshot = child;

	return ret;
}

TArray<UFirebaseDataSnapshot*> UFirebaseDataSnapshot::Children()
{
	TArray<UFirebaseDataSnapshot*> ret;
	if (!mDataSnapshot.is_valid())
	{
		UE_LOG(FireBase, Error, TEXT("UFirebaseDataSnapshot:Children self is invalid"));
		return ret;
	}

	auto childList = mDataSnapshot.children();
	for (size_t i = 0; i < childList.size(); i++)
	{
		UFirebaseDataSnapshot* tmp = NewObject<UFirebaseDataSnapshot>();
		tmp->mDataSnapshot = childList[i];
		ret.Add(tmp);
	}

	return ret;
}

int64 UFirebaseDataSnapshot::ChildrenCount()
{
	if (!mDataSnapshot.is_valid())
	{
		return -1;
	}

	return (int64)mDataSnapshot.children_count();
}

bool UFirebaseDataSnapshot::HasChildren()
{
	if (!mDataSnapshot.is_valid())
	{
		return false;
	}

	return mDataSnapshot.has_children();
}

FString UFirebaseDataSnapshot::Key()
{
	if (!mDataSnapshot.is_valid())
	{
		return TEXT("");
	}

	if (mDataSnapshot.key() != nullptr)
	{
		return FString(UTF8_TO_TCHAR(mDataSnapshot.key()));
	}

	return TEXT("");
}

firebase::Variant makeVariant(UFirebaseVariant* value)
{
	firebase::Variant setValue;

	if (value->DataType == VariantType::Int64)
	{
		setValue = firebase::Variant::FromInt64(value->Int64Value);
	}
	else if (value->DataType == VariantType::Bool)
	{
		setValue = firebase::Variant(value->BoolValue);
	}
	else if (value->DataType == VariantType::Float)
	{
		setValue = firebase::Variant(value->FloatValue);
	}
	else if (value->DataType == VariantType::String)
	{
		std::string strValue = TCHAR_TO_UTF8(*(value->StringValue));
		setValue = firebase::Variant(strValue);
	}
	else if (value->DataType == VariantType::Vector)
	{
		std::vector<firebase::Variant> valueList;
		for (int i = 0; i < value->VectorValue.Num(); i++)
		{
			valueList.push_back(makeVariant(value->VectorValue[i]));
		}
		setValue = firebase::Variant(valueList);
	}
	else if (value->DataType == VariantType::Map)
	{
		std::map<std::string, firebase::Variant> mapValue;
		for (auto it = value->MapValue.CreateConstIterator(); it; ++it)
		{
			std::string strValue = TCHAR_TO_UTF8(*(it->Key));

			firebase::Variant tmpvalue = makeVariant(it->Value);
			mapValue[strValue] = tmpvalue;
		}
		setValue = firebase::Variant(mapValue);
	}

	return setValue;
}

UFirebaseVariant* makeFirebaseVariant(firebase::Variant v)
{
	UFirebaseVariant* ret = NewObject<UFirebaseVariant>();
	if (v.type() == firebase::Variant::Type::kTypeInt64)
	{
		ret->DataType = VariantType::Int64;
		ret->Int64Value = (int)(v.int64_value());
	}
	else if (v.type() == firebase::Variant::Type::kTypeBool)
	{
		ret->DataType = VariantType::Bool;
		ret->BoolValue = v.bool_value();
	}
	else if (v.type() == firebase::Variant::Type::kTypeDouble)
	{
		ret->DataType = VariantType::Float;
		ret->FloatValue = (float)v.double_value();
	}
	else if (v.type() == firebase::Variant::Type::kTypeMutableString || v.type() == firebase::Variant::Type::kTypeStaticString)
	{
		ret->DataType = VariantType::String;
		ret->StringValue = UTF8_TO_TCHAR(v.string_value());
	}
	else if (v.type() == firebase::Variant::Type::kTypeVector)
	{
		ret->DataType = VariantType::Vector;
		const std::vector<firebase::Variant>& tmpList = v.vector();
		TArray<UFirebaseVariant*> valueList;
		for (size_t i = 0; i < tmpList.size(); i++)
		{
			valueList.Add(makeFirebaseVariant(tmpList[i]));
		}

		ret->DataType = VariantType::Vector;
		ret->VectorValue = valueList;
	}
	else if (v.type() == firebase::Variant::Type::kTypeMap)
	{
		ret->DataType = VariantType::Map;
		const std::map<firebase::Variant, firebase::Variant> tmpMap = v.map();
		TMap<FString, UFirebaseVariant*> valueMap;
		for (std::map<firebase::Variant, firebase::Variant>::const_iterator it = tmpMap.begin(); it != tmpMap.end(); it++)
		{
			firebase::Variant tmpKey = it->first;
			if (tmpKey.type() != firebase::Variant::Type::kTypeMutableString && tmpKey.type() != firebase::Variant::Type::kTypeStaticString)
			{
				continue;
			}

			FString strKey = UTF8_TO_TCHAR(tmpKey.string_value());
			valueMap.Add(strKey, makeFirebaseVariant(it->second));
			//valueMap[strKey] = makeFirebaseVariant(it->second);
		}

		ret->MapValue = valueMap;
	}

	return ret;
}

UFirebaseVariant* UFirebaseDataSnapshot::Value()
{
	if (!mDataSnapshot.is_valid())
	{
		return nullptr;
	}

	firebase::Variant result = mDataSnapshot.value();
	UFirebaseVariant* ret = makeFirebaseVariant(result);

	return ret;
}

UFirebaseVariant* UFirebaseDataSnapshot::Priority()
{
	if (!mDataSnapshot.is_valid())
	{
		return nullptr;
	}

	firebase::Variant result = mDataSnapshot.priority();
	UFirebaseVariant* ret = makeFirebaseVariant(result);

	return ret;
}

bool UFirebaseDataSnapshot::HasChild(const FString& path)
{
	if (!mDataSnapshot.is_valid())
	{
		return false;
	}

	return mDataSnapshot.HasChild(TCHAR_TO_UTF8(*path) );
}

bool UFirebaseDataSnapshot::IsValid()
{
	return mDataSnapshot.is_valid();
}