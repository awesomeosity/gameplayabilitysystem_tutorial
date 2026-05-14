// I made this :)


#include "AbilitySystem/Aura_AbilitySystemComponent.h"

void UAura_AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAura_AbilitySystemComponent::EffectApplied);
}

void UAura_AbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                 const FGameplayEffectSpec& EffectSpec,
                                                 FActiveGameplayEffectHandle ActiveGameplayEffect)
{
	FGameplayTagContainer OutTags;
	EffectSpec.GetAllAssetTags(OutTags);
	
	EffectAssetTags.Broadcast(OutTags);
}
