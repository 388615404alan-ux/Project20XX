#include "SurvivalGameMode.h"

#include "BunkerDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "ScavengeItem.h"
#include "SurvivorCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASurvivalGameMode::ASurvivalGameMode()
{
    DefaultPawnClass = ASurvivorCharacter::StaticClass();

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeAsset.Succeeded())
    {
        CubeMesh = CubeAsset.Object;
    }
}

void ASurvivalGameMode::BeginPlay()
{
    Super::BeginPlay();
    BuildGrayboxBunker();
}

void ASurvivalGameMode::RestartPlayer(AController* NewPlayer)
{
    Super::RestartPlayer(NewPlayer);

    if (NewPlayer && NewPlayer->GetPawn())
    {
        NewPlayer->SetControlRotation(FRotator::ZeroRotator);
        NewPlayer->GetPawn()->SetActorLocationAndRotation(
            FVector(0.0f, -500.0f, 110.0f),
            FRotator::ZeroRotator,
            false,
            nullptr,
            ETeleportType::TeleportPhysics);
    }
}

void ASurvivalGameMode::BuildGrayboxBunker()
{
    if (!GetWorld() || !CubeMesh)
    {
        return;
    }

    // Twenty-metre concrete test chamber.
    SpawnCube(FVector(0.0f, 0.0f, -10.0f), FVector(20.0f, 20.0f, 0.2f));
    SpawnCube(FVector(0.0f, 0.0f, 310.0f), FVector(20.0f, 20.0f, 0.2f));
    SpawnCube(FVector(-1010.0f, 0.0f, 150.0f), FVector(0.2f, 20.0f, 3.0f));
    SpawnCube(FVector(0.0f, -1010.0f, 150.0f), FVector(20.0f, 0.2f, 3.0f));
    SpawnCube(FVector(0.0f, 1010.0f, 150.0f), FVector(20.0f, 0.2f, 3.0f));

    // East wall is split to leave a doorway.
    SpawnCube(FVector(1010.0f, -570.0f, 150.0f), FVector(0.2f, 8.6f, 3.0f));
    SpawnCube(FVector(1010.0f, 570.0f, 150.0f), FVector(0.2f, 8.6f, 3.0f));
    SpawnCube(FVector(1010.0f, 0.0f, 290.0f), FVector(0.2f, 2.8f, 0.2f));

    GetWorld()->SpawnActor<ABunkerDoor>(FVector(990.0f, -140.0f, 0.0f), FRotator::ZeroRotator);

    const FVector ItemLocations[] =
    {
        FVector(250.0f, -250.0f, 25.0f),
        FVector(-300.0f, 180.0f, 25.0f),
        FVector(550.0f, 420.0f, 25.0f)
    };

    for (const FVector& Location : ItemLocations)
    {
        GetWorld()->SpawnActor<AScavengeItem>(Location, FRotator::ZeroRotator);
    }
}

void ASurvivalGameMode::SpawnCube(const FVector& Location, const FVector& Scale, const FRotator& Rotation) const
{
    AStaticMeshActor* Cube = GetWorld()->SpawnActor<AStaticMeshActor>(Location, Rotation);
    if (!Cube)
    {
        return;
    }

    UStaticMeshComponent* Mesh = Cube->GetStaticMeshComponent();
    Mesh->SetStaticMesh(CubeMesh);
    Mesh->SetWorldScale3D(Scale);
    Mesh->SetMobility(EComponentMobility::Static);
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
