#include "SurvivorCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interactable.h"

ASurvivorCharacter::ASurvivorCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
    GetCharacterMovement()->MaxWalkSpeed = 420.0f;
    GetCharacterMovement()->BrakingDecelerationWalking = 1800.0f;
    GetCharacterMovement()->AirControl = 0.2f;

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
    FirstPersonCamera->SetRelativeLocation(FVector(-10.0f, 0.0f, 64.0f));
    FirstPersonCamera->bUsePawnControlRotation = true;

    bUseControllerRotationYaw = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ASurvivorCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!IsLocallyControlled() || !GEngine)
    {
        return;
    }

    FString Status = FString::Printf(TEXT("WASD move | Mouse look | Space jump | E interact     Supplies: %d"), Supplies);
    if (const IInteractable* Target = GetInteractableInView())
    {
        Status += FString::Printf(TEXT("\n[E] %s"), *Target->GetInteractionText().ToString());
    }

    GEngine->AddOnScreenDebugMessage(1001, 0.0f, FColor::White, Status);
}

void ASurvivorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASurvivorCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASurvivorCharacter::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ASurvivorCharacter::Turn);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASurvivorCharacter::LookUp);
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);
    PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &ASurvivorCharacter::Interact);
}

void ASurvivorCharacter::AddSupplies(int32 Amount)
{
    Supplies = FMath::Max(0, Supplies + Amount);
}

void ASurvivorCharacter::MoveForward(float Value)
{
    AddMovementInput(GetActorForwardVector(), Value);
}

void ASurvivorCharacter::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void ASurvivorCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void ASurvivorCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void ASurvivorCharacter::Interact()
{
    if (IInteractable* Target = GetInteractableInView())
    {
        Target->Interact(this);
    }
}

IInteractable* ASurvivorCharacter::GetInteractableInView() const
{
    if (!FirstPersonCamera || !GetWorld())
    {
        return nullptr;
    }

    const FVector Start = FirstPersonCamera->GetComponentLocation();
    const FVector End = Start + FirstPersonCamera->GetForwardVector() * InteractionDistance;
    FHitResult Hit;
    FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(InteractionTrace), false, this);

    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, QueryParams))
    {
        return Cast<IInteractable>(Hit.GetActor());
    }

    return nullptr;
}
