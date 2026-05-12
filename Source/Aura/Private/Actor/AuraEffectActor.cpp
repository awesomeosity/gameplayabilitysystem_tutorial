// I made this :)


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootSceneComponent"));
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor)
{
	auto* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetAbilitySystemComponent == nullptr)
		return;
	
	if (AppliedEffectOnOverlap == nullptr)
		return;
	
	auto EffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	auto EffectSpec = TargetAbilitySystemComponent->MakeOutgoingSpec(AppliedEffectOnOverlap, Level, EffectContextHandle);
	auto SavedHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
	
	if (EffectSpec.Data.Get()->Duration == FGameplayEffectConstants::INFINITE_DURATION)
	{
		SavedHandles.Add({TargetAbilitySystemComponent, SavedHandle});
	}
}

void AAuraEffectActor::RemoveEffectFromTarget(AActor* TargetActor, int32 StackCount)
{
	if (AppliedEffectOnOverlap == nullptr)
		return;
	
	auto* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetAbilitySystemComponent == nullptr)
		return;
	
	const auto& SavedHandle = SavedHandles.FindChecked(TargetAbilitySystemComponent);
	if (SavedHandle.IsValid() == false)
		return;
	
	TargetAbilitySystemComponent->RemoveActiveGameplayEffect(SavedHandle, StackCount);
}