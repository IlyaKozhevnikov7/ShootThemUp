// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUFindEnemyService.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUFindEnemyService : public UBTService
{
	GENERATED_BODY()

private:

    UPROPERTY(EditAnywhere)
    FBlackboardKeySelector EnemyKey;

protected:

    USTUFindEnemyService();

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
