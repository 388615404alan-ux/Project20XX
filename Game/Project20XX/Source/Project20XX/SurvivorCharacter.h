#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivorCharacter.generated.h"

class UCameraComponent;
class IInteractable;

UCLASS()
class PROJECT20XX_API ASurvivorCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASurvivorCharacter();

    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    void AddSupplies(int32 Amount);

private:
    UPROPERTY(VisibleAnywhere, Category = "Camera")
    TObjectPtr<UCameraComponent> FirstPersonCamera;

    UPROPERTY(VisibleAnywhere, Category = "Survival")
    int32 Supplies = 0;

    UPROPERTY(EditDefaultsOnly, Category = "Interaction")
    float InteractionDistance = 350.0f;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void Interact();
    IInteractable* GetInteractableInView() const;
};
