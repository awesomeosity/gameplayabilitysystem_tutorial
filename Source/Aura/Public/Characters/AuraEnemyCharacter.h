// I made this :)

#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "Interfaces/HighlightInterface.h"
#include "AuraEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemyCharacter : public AAuraCharacterBase, public IHighlightInterface
{
	GENERATED_BODY()

	
public:
	AAuraEnemyCharacter();

	// IHighlightInterface functions
	virtual void HighlightActor(bool bShouldHighlight) override;
	// IHighlightInterface functions end

};
