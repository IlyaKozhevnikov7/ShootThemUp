// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "STUAIPerceptionComponent.generated.h"

UCLASS(ClassGroup = "STU", meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

private:

    UPROPERTY()
    AAIController* Controller;

protected:
    
    virtual void BeginPlay() override;
    
public:
    
    AActor* GetNearestActor() const;

private:

    bool IsEnemy(AController* PercieveController) const;
};
