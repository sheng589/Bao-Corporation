// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FirebaseFunctionLibrary.generated.h"


class UFirebaseFutureVoid;

UENUM(BlueprintType)
enum class AnalyticsEvent : uint8
{
	add_payment_info 	UMETA(DisplayName = "add_payment_info"),
	add_to_cart 	UMETA(DisplayName = "add_to_cart"),
	add_to_wishlist 	UMETA(DisplayName = "add_to_wishlist"),
	app_open 	UMETA(DisplayName = "app_open"),
	begin_checkout 	UMETA(DisplayName = "begin_checkout"),
	campaign_details 	UMETA(DisplayName = "campaign_details"),
	checkout_progress 	UMETA(DisplayName = "checkout_progress"),
	earn_virtual_currency 	UMETA(DisplayName = "earn_virtual_currency"),

	ecommerce_purchase 	UMETA(DisplayName = "ecommerce_purchase"),
	generate_lead 	UMETA(DisplayName = "generate_lead"),
	join_group 	UMETA(DisplayName = "join_group"),
	level_up 	UMETA(DisplayName = "level_up"),
	login 	UMETA(DisplayName = "login"),

	post_score 	UMETA(DisplayName = "post_score"),
	present_offer 	UMETA(DisplayName = "present_offer"),
	purchase_refund 	UMETA(DisplayName = "purchase_refund"),
	remove_from_cart 	UMETA(DisplayName = "remove_from_cart"),

	search 	UMETA(DisplayName = "search"),
	select_content 	UMETA(DisplayName = "select_content"),
	set_checkout_option 	UMETA(DisplayName = "set_checkout_option"),
	share 	UMETA(DisplayName = "share"),

	sign_up 	UMETA(DisplayName = "sign_up"),
	spend_virtual_currency 	UMETA(DisplayName = "spend_virtual_currency"),
	tutorial_begin 	UMETA(DisplayName = "tutorial_begin"),
	tutorial_complete 	UMETA(DisplayName = "tutorial_complete"),
	unlock_achievement 	UMETA(DisplayName = "unlock_achievement"),
	view_item 	UMETA(DisplayName = "view_item"),

	view_item_list 	UMETA(DisplayName = "view_item_list"),
	view_search_results 	UMETA(DisplayName = "view_search_results"),
	level_start 	UMETA(DisplayName = "level_start"),
	level_end 	UMETA(DisplayName = "level_end"),
};


UENUM(BlueprintType)
enum class AnalyticsParameter : uint8
{
	achievement_id 	UMETA(DisplayName = "achievement_id"),

	aclid 	UMETA(DisplayName = "aclid"),
	affiliation 	UMETA(DisplayName = "affiliation"),
	campaign 	UMETA(DisplayName = "campaign"),
	character 	UMETA(DisplayName = "character"),
	checkout_step 	UMETA(DisplayName = "checkout_step"),
	checkout_option 	UMETA(DisplayName = "checkout_option"),
	content 	UMETA(DisplayName = "content"),
	content_type 	UMETA(DisplayName = "content_type"),
	coupon 	UMETA(DisplayName = "coupon"),
	cp1 	UMETA(DisplayName = "cp1"),
	creative_name 	UMETA(DisplayName = "creative_name"),
	creative_slot 	UMETA(DisplayName = "creative_slot"),
	currency 	UMETA(DisplayName = "currency"),
	destination 	UMETA(DisplayName = "destination"),
	end_date 	UMETA(DisplayName = "end_date"),
	flight_number 	UMETA(DisplayName = "flight_number"),
	group_id 	UMETA(DisplayName = "group_id"),
	index 	UMETA(DisplayName = "index"),
	item_brand 	UMETA(DisplayName = "item_brand"),
	item_category 	UMETA(DisplayName = "item_category"),

	item_id 	UMETA(DisplayName = "item_id"),
	item_location_id 	UMETA(DisplayName = "item_location_id"),
	item_name 	UMETA(DisplayName = "item_name"),
	item_list 	UMETA(DisplayName = "item_list"),
	item_variant 	UMETA(DisplayName = "item_variant"),
	level 	UMETA(DisplayName = "level"),
	location 	UMETA(DisplayName = "location"),
	medium 	UMETA(DisplayName = "medium"),
	number_of_nights 	UMETA(DisplayName = "number_of_nights"),
	number_of_passengers 	UMETA(DisplayName = "number_of_passengers"),
	number_of_rooms 	UMETA(DisplayName = "number_of_rooms"),
	origin 	UMETA(DisplayName = "origin"),
	price 	UMETA(DisplayName = "price"),


	quantity 	UMETA(DisplayName = "quantity"),
	score 	UMETA(DisplayName = "score"),
	search_term 	UMETA(DisplayName = "search_term"),
	shipping 	UMETA(DisplayName = "shipping"),
	sign_up_method 	UMETA(DisplayName = "sign_up_method"),
	method 	UMETA(DisplayName = "method"),
	source 	UMETA(DisplayName = "source"),
	start_date 	UMETA(DisplayName = "start_date"),

	tax 	UMETA(DisplayName = "tax"),
	term 	UMETA(DisplayName = "term"),
	transaction_id 	UMETA(DisplayName = "transaction_id"),
	travel_class 	UMETA(DisplayName = "travel_class"),
	value 	UMETA(DisplayName = "value"),

	virtual_currency_name 	UMETA(DisplayName = "virtual_currency_name"),
	level_name 	UMETA(DisplayName = "level_name"),
	success 	UMETA(DisplayName = "success"),
	extend_session 	UMETA(DisplayName = "extend_session"),
};

/**
 * 
 */
UCLASS()
class EASYFIREBASE_API UFirebaseFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:

	UFUNCTION(BlueprintCallable,  Category = "FireBase")
	static bool FireBaseInitialize();

	UFUNCTION(BlueprintCallable, Category = "FireBase|Analytics")
	static void SetUserProperty(const FString& name, const FString& property);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Analytics")
	static void LogStringEvent(AnalyticsEvent name, AnalyticsParameter parameter_name, const FString& parameter_value);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Analytics")
	static void LogInt64Event(AnalyticsEvent name, AnalyticsParameter parameter_name, int64 parameter_value);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Analytics")
	static void LogIntEvent(AnalyticsEvent name, AnalyticsParameter parameter_name, int parameter_value);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Analytics")
	static void LogFloatEvent(AnalyticsEvent name, AnalyticsParameter parameter_name, float parameter_value);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Analytics")
	static void LogEvent(AnalyticsEvent name);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Analytics")
	static void LogCustomStringEvent(const FString& name, const FString& parameter_name, const FString& parameter_value);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Analytics")
	static void LogCustomInt64Event(const FString& name, const FString& parameter_name, int64 parameter_value);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Analytics")
	static void LogCustomIntEvent(const FString& name, const FString& parameter_name, int parameter_value);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Analytics")
	static void LogCustomFloatEvent(const FString& name, const FString& parameter_name, float parameter_value);

	UFUNCTION(BlueprintCallable, Category = "FireBase|Analytics")
	static void LogCustomEvent(const FString& name);
};
