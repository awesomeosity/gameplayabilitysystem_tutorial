// I made this :)


#include "Characters/AuraEnemyCharacter.h"
#include "AbilitySystem/Aura_AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEnemyCharacter::AAuraEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComp = CreateDefaultSubobject<UAura_AbilitySystemComponent>("AbilitySystemComponent");

	constexpr bool bIsReplicated = true;
	AbilitySystemComp->SetIsReplicated(bIsReplicated);
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	PrimaryAttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("Attribute Set");
}

void AAuraEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEnemyCharacter::HighlightActor(bool bShouldHighlight)
{
	if (bShouldHighlight)
	{
		GetMesh()->SetRenderCustomDepth(true);
		GetMesh()->SetCustomDepthStencilValue(250);

		WeaponMesh->SetRenderCustomDepth(true);
		WeaponMesh->SetCustomDepthStencilValue(250);
	}
	else
	{
		GetMesh()->SetRenderCustomDepth(false);
		WeaponMesh->SetRenderCustomDepth(false);
	}
}

int32 AAuraEnemyCharacter::GetPlayerLevel() const
{
	return Level;
}

void AAuraEnemyCharacter::SetUpAbilitySystemComp()
{
	Super::SetUpAbilitySystemComp();
	
	AbilitySystemComp->InitAbilityActorInfo(this, this);
	auto* AuraAbilityComp = Cast<UAura_AbilitySystemComponent>(AbilitySystemComp);
	if (AuraAbilityComp == nullptr)
		return;
	
	AuraAbilityComp->AbilityActorInfoSet();
}
