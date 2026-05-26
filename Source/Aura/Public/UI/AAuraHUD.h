// I made this :)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AAuraHUD.generated.h"

class UAttributeMenuWidgetController;
class UAuraUserWidget;
class UOverlayWidgetController;
class APlayerController;
class APlayerState;
class UAbilitySystemComponent;
class UAttributeSet;

struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class AURA_API AAAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAuraUserWidget> Overlay;

	UFUNCTION(BlueprintCallable)
	UOverlayWidgetController* GetOverlayController(const FWidgetControllerParams& Params);

	UFUNCTION()
	void InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState, UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAuraUserWidget> AttributeMenu;

	UFUNCTION(BlueprintCallable)
	UAttributeMenuWidgetController* GetAttributeMenuController(const FWidgetControllerParams& Params);

	UFUNCTION()
	void InitAttributeMenu(APlayerController* PlayerController, APlayerState* PlayerState, UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet);

protected:

private:
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayControllerClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayClass;
	
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuControllerClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> AttributeMenuClass;
};
