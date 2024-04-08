// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STUNextLocationTask.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

private:

    UPROPERTY(EditAnywhere)
    float Radius;

    UPROPERTY(EditAnywhere)
    bool bSelfCenter;

    UPROPERTY(EditAnywhere, meta = (EditCondition = "!bSelfCenter"))
    FBlackboardKeySelector CenterActor;
    
    UPROPERTY(EditAnywhere, Category = "Key Selector")
    FBlackboardKeySelector NextLocation; 
    
public:

    USTUNextLocationTask();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    
};
