// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTUAIPerceptionComponent;
class USTURespawnComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController
{
    GENERATED_BODY()

private:

    UPROPERTY(VisibleAnywhere, Category = "Component")
    USTUAIPerceptionComponent* STUAIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, Category = "Component")
    USTURespawnComponent* RespawnComponent;
    
    FName EnemyActorKeyName;
    
protected:

    ASTUAIController();

    virtual void BeginPlay() override;
    
    virtual void Tick(float DeltaSeconds) override;

public:

    USTUAIPerceptionComponent* GetSTUAIPerceptionComponent() const { return STUAIPerceptionComponent; }

private:

    virtual void OnPossess(APawn* InPawn) override;

    AActor* GetNearestActor() const;
};
