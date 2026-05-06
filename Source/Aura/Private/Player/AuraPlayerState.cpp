// I made this :)


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/Aura_AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComp = CreateDefaultSubobject<UAura_AbilitySystemComponent>("AbilitySystemComponent");

	constexpr bool bIsReplicated = true;
	AbilitySystemComp->SetIsReplicated(bIsReplicated);
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("Attribute Set");
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}