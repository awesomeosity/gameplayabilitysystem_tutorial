// I made this :)


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interfaces/HighlightInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent == nullptr)
		return;
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D AxisValue = InputActionValue.Get<FVector2D>();
	FRotator Rotation{ 0.f, GetControlRotation().Yaw, 0.f };
	FVector ForwardDir = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
	FVector RightDir = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	auto* ControlledPawn = GetPawn<APawn>();
	if (ControlledPawn == nullptr)
		return;

	ControlledPawn->AddMovementInput(ForwardDir, AxisValue.Y);
	ControlledPawn->AddMovementInput(RightDir, AxisValue.X);
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);
	if (CursorHit.bBlockingHit == false)
		return;

	TScriptInterface<IHighlightInterface> HitActor = CursorHit.GetActor();
	if (HitActor == nullptr && HighlightedActor != nullptr)
	{
		HighlightedActor->HighlightActor(false);
		HighlightedActor = nullptr;
	}
	if (HitActor != nullptr && HighlightedActor != HitActor)
	{
		if (HighlightedActor != nullptr)
			HighlightedActor->HighlightActor(false);
	
		HighlightedActor = HitActor;
		HighlightedActor->HighlightActor(true);
	}
}
