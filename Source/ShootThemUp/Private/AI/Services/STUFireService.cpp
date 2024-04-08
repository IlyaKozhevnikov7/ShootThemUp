// Shoot Them Up Yata. All Rights Reserved.

#include "STUFireService.h"
#include "AIController.h"
#include "STUAIWeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUFireService::USTUFireService()
{
    NodeName = "Fire";
}

void USTUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();
    const auto Controller = Cast<AAIController>(OwnerComp.GetAIOwner());

    const bool HasAim = BlackBoard && BlackBoard->GetValueAsObject(EnemyKey.SelectedKeyName);

    if (auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USTUAIWeaponComponent>())
    {
        if (HasAim && WeaponComponent->CanFire())
        {
            //UE_LOG(LogTemp, Display, TEXT("HasAim"));
            WeaponComponent->Fire();
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT("OnStopFire"));
			//WeaponComponent->StopFire();
            WeaponComponent->OnStopFire();
        }
    }
}
