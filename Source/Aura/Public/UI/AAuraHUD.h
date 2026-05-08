// I made this :)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AAuraHUD.generated.h"

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

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UOverlayWidgetController> OverlayController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayControllerClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayClass;

	UFUNCTION(BlueprintCallable)
	UOverlayWidgetController* GetOverlayController(const FWidgetControllerParams& Params);

	UFUNCTION()
	void InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState, UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet);

protected:

private:

};
