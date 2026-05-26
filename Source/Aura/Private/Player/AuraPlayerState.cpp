// I made this :)


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/Aura_AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComp = CreateDefaultSubobject<UAura_AbilitySystemComponent>("AbilitySystemComponent");

	constexpr bool bIsReplicated = true;
	AbilitySystemComp->SetIsReplicated(bIsReplicated);
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("Attribute Set");
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AAuraPlayerState, Level);

}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AAuraPlayerState::OnRep_PlayerLevel(int32 OldLevel)
{
}
