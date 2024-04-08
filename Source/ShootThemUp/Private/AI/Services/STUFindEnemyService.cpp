// Shoot Them Up Yata. All Rights Reserved.

#include "STUFindEnemyService.h"
#include "STUAIController.h"
#include "STUAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUFindEnemyService::USTUFindEnemyService()
{
    NodeName = "Find Enemy";
}

void USTUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();
    const auto Controller = Cast<ASTUAIController>(OwnerComp.GetAIOwner());

    if (Controller && BlackBoard)
    {
        BlackBoard->SetValueAsObject(EnemyKey.SelectedKeyName, Controller->GetSTUAIPerceptionComponent()->GetNearestActor());
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
