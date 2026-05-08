// I made this :)


#include "UI/AAuraHUD.h"

#include "UI/AuraUserWidget.h"
#include "UI/OverlayWidgetController.h"
#include "GameFramework/PlayerController.h"

UOverlayWidgetController* AAAuraHUD::GetOverlayController(const FWidgetControllerParams& Params)
{
	if (OverlayController == nullptr)
	{
		OverlayController = NewObject<UOverlayWidgetController>(this, OverlayControllerClass);
		OverlayController->InitWidgetController(Params);
		OverlayController->BindCallbacksToDependencies();
	}

	return OverlayController;
}

void AAAuraHUD::InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState, UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet)
{
	if (OverlayClass == nullptr)
		return;

	if (OverlayControllerClass == nullptr)
		return;

	auto* OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayClass);
	auto* OutOverlayController = GetOverlayController(FWidgetControllerParams{ AttributeSet, AbilitySystemComponent, PlayerState, PlayerController });

	OverlayWidget->SetWidgetController(OutOverlayController);
	OutOverlayController->BroadcastInitialValues();
	OverlayWidget->AddToViewport();
}