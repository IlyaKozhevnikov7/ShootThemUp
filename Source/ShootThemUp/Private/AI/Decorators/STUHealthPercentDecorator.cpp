// Shoot Them Up Yata. All Rights Reserved.

#include "AI/Decorators/STUHealthPercentDecorator.h"
#include "AIController.h"
#include "STUHealthComponent.h"

USTUHealthPercentDecorator::USTUHealthPercentDecorator()
{
    NodeName = "Need Health";
    HealthPercent = 0.4;
}

bool USTUHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{    
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return false;

    const auto HealthComponent = Pawn->FindComponentByClass<USTUHealthComponent>();
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
