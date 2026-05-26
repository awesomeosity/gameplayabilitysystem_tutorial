// I made this :)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class AAAuraHUD;
struct FWidgetControllerParams;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintPure, Category = "AbilitySystemLibrary|Widget Controller")
	static UOverlayWidgetController* GetOverlayWidgetController(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "AbilitySystemLibrary|Widget Controller")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(UObject* WorldContextObject);
	
protected:
	static AAAuraHUD* GetAAAuraHUD(const UObject* WorldContextObject);
	static void GetWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutParams);
};
