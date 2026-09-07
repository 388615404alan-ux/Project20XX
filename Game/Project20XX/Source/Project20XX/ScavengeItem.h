#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "ScavengeItem.generated.h"

class UStaticMeshComponent;

UCLASS()
class PROJECT20XX_API AScavengeItem : public AActor, public IInteractable
{
    GENERATED_BODY()

public:
    AScavengeItem();

    virtual void Interact(ASurvivorCharacter* Interactor) override;
    virtual FText GetInteractionText() const override;

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> Mesh;

    UPROPERTY(EditAnywhere, Category = "Survival")
    int32 SupplyValue = 1;
};
