// I made this :)


#include "Characters/AuraEnemyCharacter.h"

AAuraEnemyCharacter::AAuraEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemyCharacter::HighlightActor(bool bShouldHighlight)
{
	if (bShouldHighlight)
	{
		GetMesh()->SetRenderCustomDepth(true);
		GetMesh()->SetCustomDepthStencilValue(250);

		WeaponMesh->SetRenderCustomDepth(true);
		WeaponMesh->SetCustomDepthStencilValue(250);
	}
	else
	{
		GetMesh()->SetRenderCustomDepth(false);
		WeaponMesh->SetRenderCustomDepth(false);
	}
}