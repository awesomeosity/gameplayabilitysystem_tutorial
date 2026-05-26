// I made this :)


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/AAuraHUD.h"
#include "UI/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(UObject* WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	GetWidgetControllerParams(WorldContextObject, WidgetControllerParams);	
	auto* AuraHUD = GetAAAuraHUD(WorldContextObject);
	return AuraHUD->GetOverlayController(WidgetControllerParams);
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(UObject* WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	GetWidgetControllerParams(WorldContextObject, WidgetControllerParams);	
	auto* AuraHUD = GetAAAuraHUD(WorldContextObject);
	return AuraHUD->GetAttributeMenuController(WidgetControllerParams);
}

AAAuraHUD* UAuraAbilitySystemLibrary::GetAAAuraHUD(const UObject* WorldContextObject)
{
	auto* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (PlayerController == nullptr)
		return {};
	
	auto* AuraPlayerController = Cast<AAuraPlayerController>(PlayerController);
	if (AuraPlayerController == nullptr)
		return {};
	
	auto* HUD = PlayerController->GetHUD();
	if (HUD == nullptr)
		return {};
	
	auto* AuraHUD = Cast<AAAuraHUD>(HUD);
	if (AuraHUD == nullptr)
		return {};
	
	return AuraHUD;
}

void UAuraAbilitySystemLibrary::GetWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutParams)
{
	if (WorldContextObject == nullptr)
		return;
	
	auto* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (PlayerController == nullptr)
		return;
	
	auto* AuraPlayerController = Cast<AAuraPlayerController>(PlayerController);
	if (AuraPlayerController == nullptr)
		return;
	
	auto* AuraPlayerState = AuraPlayerController->GetPlayerState<AAuraPlayerState>();
	if (AuraPlayerState == nullptr)
		return;
	
	auto* AuraAbilitySystem = AuraPlayerState->GetAbilitySystemComponent();
	if (AuraAbilitySystem == nullptr)
		return;
	
	auto* AuraAttributeSet = AuraPlayerState->GetAttributeSet();
	if (AuraAttributeSet == nullptr)
		return;

	OutParams.AbilitySystemComp = AuraAbilitySystem;
	OutParams.AttributeSet = AuraAttributeSet;
	OutParams.PlayerController = AuraPlayerController;
	OutParams.PlayerState = AuraPlayerState;
	return;
}
