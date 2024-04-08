// Shoot Them Up Yata. All Rights Reserved.

#include "STUNextLocationTask.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUNextLocationTask, Display, Display)

USTUNextLocationTask::USTUNextLocationTask()
{
    Radius = 2500.f;
    bSelfCenter = true;
    NodeName = "Next Location";
}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
   
    if (!Blackboard || !Pawn) return EBTNodeResult::Failed;

    const auto NavSystem = UNavigationSystemV1::GetCurrent(Pawn);

    if (!NavSystem) return EBTNodeResult::Failed;

    FVector Center = Pawn->GetNavAgentLocation();
    
    if (!bSelfCenter)
    {
        Center = Cast<AActor>(Blackboard->GetValueAsObject(CenterActor.SelectedKeyName))->GetActorLocation();
    }
    
    FNavLocation RandomLocation;
    if (!NavSystem->GetRandomReachablePointInRadius(Center, Radius, RandomLocation)) return EBTNodeResult::Failed;

    Blackboard->SetValueAsVector(NextLocation.SelectedKeyName, RandomLocation.Location);
    return  EBTNodeResult::Succeeded;
}
