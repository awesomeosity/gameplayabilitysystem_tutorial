// I made this :)


#include "Characters/AuraPlayerCharacter.h"
#include "AbilitySystem/Aura_AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerState.h"

AAuraPlayerCharacter::AAuraPlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Camera Arm");
	SpringArm->SetupAttachment(GetRootComponent());

	MainCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	MainCamera->SetupAttachment(SpringArm);

	auto* CharacterMovementComp = GetCharacterMovement();
	if (CharacterMovementComp == nullptr)
		return;

	CharacterMovementComp->bOrientRotationToMovement = true;
	CharacterMovementComp->RotationRate = FRotator{ 0.f, 400.f, 0.f };
	CharacterMovementComp->bConstrainToPlane = true;
	CharacterMovementComp->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	SetUpAbilitySystemComp();
}

void AAuraPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	SetUpAbilitySystemComp();
}

void AAuraPlayerCharacter::SetUpAbilitySystemComp()
{
	auto* AuraPlayerState = GetPlayerState<AAuraPlayerState>();

	if (AuraPlayerState == nullptr)
		return;

	AbilitySystemComp = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	AbilitySystemComp->InitAbilityActorInfo(AuraPlayerState, this);
}
