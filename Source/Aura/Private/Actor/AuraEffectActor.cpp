// I made this :)


#include "Actor/AuraEffectActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Hitbox = CreateDefaultSubobject<USphereComponent>("Hitbox");
	Hitbox->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Hitbox->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Hitbox->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
}

void AAuraEffectActor::OnOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	auto* AbilityActor = Cast<IAbilitySystemInterface>(OtherActor);
	if (AbilityActor == nullptr)
		return;

	const auto* AbilitySystemComp = AbilityActor->GetAbilitySystemComponent();
	if (AbilitySystemComp == nullptr)
		return;

	const auto* AuraAttributeSet = Cast<UAuraAttributeSet>(AbilitySystemComp->GetAttributeSet(UAuraAttributeSet::StaticClass()));
	if (AuraAttributeSet == nullptr)
		return;

	//TODO: Change this to apply a gameplay effect.
	UAuraAttributeSet* MutableAuraAttribute = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
	MutableAuraAttribute->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
	MutableAuraAttribute->SetMana(AuraAttributeSet->GetMana() - 25.f);
	Destroy();
}

void AAuraEffectActor::EndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
)
{

}
