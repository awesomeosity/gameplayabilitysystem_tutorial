// I made this :)


#include "UI/AuraWidgetController.h"

UAuraWidgetController::UAuraWidgetController()
{

}

void UAuraWidgetController::InitWidgetController(const FWidgetControllerParams& Params)
{
	AttributeSet = Params.AttributeSet;
	AbilitySystemComp = Params.AbilitySystemComp;
	PlayerState = Params.PlayerState;
	PlayerController = Params.PlayerController;
}

void UAuraWidgetController::BroadcastInitialValues()
{

}

void UAuraWidgetController::BindCallbacksToDependencies()
{

}
