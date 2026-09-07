#include "ScavengeItem.h"

#include "Components/StaticMeshComponent.h"
#include "SurvivorCharacter.h"
#include "UObject/ConstructorHelpers.h"

AScavengeItem::AScavengeItem()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);
    Mesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    Mesh->SetRelativeScale3D(FVector(0.35f));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        Mesh->SetStaticMesh(CubeMesh.Object);
    }
}

void AScavengeItem::Interact(ASurvivorCharacter* Interactor)
{
    if (Interactor)
    {
        Interactor->AddSupplies(SupplyValue);
        Destroy();
    }
}

FText AScavengeItem::GetInteractionText() const
{
    return FText::Format(NSLOCTEXT("Project20XX", "CollectSupplies", "Collect supplies (+{0})"), FText::AsNumber(SupplyValue));
}
