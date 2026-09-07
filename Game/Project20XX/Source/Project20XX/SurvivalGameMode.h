#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivalGameMode.generated.h"

class UStaticMesh;

UCLASS()
class PROJECT20XX_API ASurvivalGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASurvivalGameMode();
    virtual void RestartPlayer(AController* NewPlayer) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TObjectPtr<UStaticMesh> CubeMesh;

    void BuildGrayboxBunker();
    void SpawnCube(const FVector& Location, const FVector& Scale, const FRotator& Rotation = FRotator::ZeroRotator) const;
};
