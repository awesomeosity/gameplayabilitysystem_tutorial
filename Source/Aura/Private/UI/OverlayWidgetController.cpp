// I made this :)


#include "UI/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Aura_AbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AuraAttributes = Cast<UAuraAttributeSet>(AttributeSet);
	if (AuraAttributes == nullptr)
		return;

	OnHealthChanged.Broadcast(AuraAttributes->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributes->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributes->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributes->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	auto* AuraAttributes = Cast<UAuraAttributeSet>(AttributeSet);
	if (AuraAttributes == nullptr)
		return;
	
	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	});
	
	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	});
	
	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnManaChanged.Broadcast(Data.NewValue);
	});
	
	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AuraAttributes->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxManaChanged.Broadcast(Data.NewValue);
	});
	
	auto* AuraAbilitySystemComp = Cast<UAura_AbilitySystemComponent>(AbilitySystemComp);
	if (AuraAbilitySystemComp == nullptr)
		return;
	
	AuraAbilitySystemComp->EffectAssetTags.AddLambda([this](const FGameplayTagContainer& EffectTags)
	{
		for (const auto& Tag : EffectTags)
		{
			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			if (Tag.MatchesTag(MessageTag))
			{
				auto* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageDataTable, Tag);
				MessageWidgetRowDelegate.Broadcast(*Row);
			}
		}
	});
}