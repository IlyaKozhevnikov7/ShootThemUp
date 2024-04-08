// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUAmmoPickupDecorator.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUAmmoPickupDecorator : public UBTDecorator
{
	GENERATED_BODY()

protected:
    
    USTUAmmoPickupDecorator();
    
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
