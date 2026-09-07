#include "BunkerDoor.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ABunkerDoor::ABunkerDoor()
{
    Hinge = CreateDefaultSubobject<USceneComponent>(TEXT("Hinge"));
    SetRootComponent(Hinge);

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorMesh->SetupAttachment(Hinge);
    DoorMesh->SetRelativeLocation(FVector(0.0f, 70.0f, 130.0f));
    DoorMesh->SetRelativeScale3D(FVector(0.18f, 1.4f, 2.6f));
    DoorMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        DoorMesh->SetStaticMesh(CubeMesh.Object);
    }
}

void ABunkerDoor::BeginPlay()
{
    Super::BeginPlay();
    ClosedRotation = GetActorRotation();
}

void ABunkerDoor::Interact(ASurvivorCharacter* Interactor)
{
    bIsOpen = !bIsOpen;
    SetActorRotation(ClosedRotation + FRotator(0.0f, bIsOpen ? 100.0f : 0.0f, 0.0f));
}

FText ABunkerDoor::GetInteractionText() const
{
    return bIsOpen
        ? NSLOCTEXT("Project20XX", "CloseDoor", "Close blast door")
        : NSLOCTEXT("Project20XX", "OpenDoor", "Open blast door");
}
