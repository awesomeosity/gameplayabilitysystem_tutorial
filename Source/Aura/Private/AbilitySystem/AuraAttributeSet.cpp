// I made this :)


#include "AbilitySystem/AuraAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(25.f);
	InitMaxMana(50.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties EffectProperties = ConstructEffectProperties(Data);
	
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, MaxMana);
}

FEffectProperties UAuraAttributeSet::ConstructEffectProperties(const struct FGameplayEffectModCallbackData& Data)
{
	auto Context = Data.EffectSpec.GetContext();
	
	auto* SourceAbilitySystemComponent = Context.GetOriginalInstigatorAbilitySystemComponent();
	if (SourceAbilitySystemComponent == nullptr)
		return {};
	
	auto* SourceAvatarActor = SourceAbilitySystemComponent->GetAvatarActor();
	if (SourceAvatarActor == nullptr)
		return {};
	
	auto* SourceCharacter = Cast<ACharacter>(SourceAvatarActor);
	
	AController* SourceController = SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
	if (SourceController == nullptr)
	{
		if (SourceCharacter != nullptr)
			SourceController = SourceCharacter->GetController();
	}
	
	auto* TargetInfo = Data.Target.AbilityActorInfo.Get();
	if (TargetInfo == nullptr)
		return {};
		
	AController* TargetController = TargetInfo->PlayerController.Get();
	auto* TargetCharacter = Cast<ACharacter>(TargetInfo->AbilitySystemComponent->GetAvatarActor());
	if (TargetController == nullptr && TargetCharacter != nullptr)
	{
		if (TargetCharacter != nullptr)
			TargetController = TargetCharacter->GetController();
	}
	
	FEffectProperties EffectProperties{
		.EffectContext = Context,
		.SourceAbilitySystemComponent = SourceAbilitySystemComponent,
		.SourceAvatarActor = SourceAvatarActor,
		.SourceController = SourceController,
		.SourceCharacter = SourceCharacter,
		.TargetAbilitySystemComponent = TargetInfo->AbilitySystemComponent.Get(),
		.TargetAvatarActor = TargetInfo->AvatarActor.Get(),
		.TargetController = TargetController,
		.TargetCharacter = TargetCharacter
	};
	
	return EffectProperties;
}