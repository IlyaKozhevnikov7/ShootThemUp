// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUWeaponChangeService.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUWeaponChangeService : public UBTService
{
	GENERATED_BODY()

private:

    UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Probability;
    
    UPROPERTY(EditAnywhere)
    FBlackboardKeySelector OwnerKey;
    
protected:
    
    USTUWeaponChangeService();
    
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
   
};
