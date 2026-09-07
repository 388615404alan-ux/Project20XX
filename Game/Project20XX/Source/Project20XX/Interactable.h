#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class ASurvivorCharacter;

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
    GENERATED_BODY()
};

class PROJECT20XX_API IInteractable
{
    GENERATED_BODY()

public:
    virtual void Interact(ASurvivorCharacter* Interactor) = 0;
    virtual FText GetInteractionText() const = 0;
};
