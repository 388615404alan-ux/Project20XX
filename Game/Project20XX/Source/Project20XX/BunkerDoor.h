#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "BunkerDoor.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class PROJECT20XX_API ABunkerDoor : public AActor, public IInteractable
{
    GENERATED_BODY()

public:
    ABunkerDoor();

    virtual void BeginPlay() override;
    virtual void Interact(ASurvivorCharacter* Interactor) override;
    virtual FText GetInteractionText() const override;

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USceneComponent> Hinge;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> DoorMesh;

    FRotator ClosedRotation;
    bool bIsOpen = false;
};
