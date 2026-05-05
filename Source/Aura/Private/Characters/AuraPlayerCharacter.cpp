// I made this :)


#include "Characters/AuraPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
