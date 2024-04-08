// Shoot Them Up Yata. All Rights Reserved.

#include "STUAmmoPickupDecorator.h"
#include "AIController.h"
#include "STUAIWeaponComponent.h"

USTUAmmoPickupDecorator::USTUAmmoPickupDecorator()
{
    NodeName = "Need Ammo";
}

bool USTUAmmoPickupDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    //UE_LOG(LogTemp, Display, TEXT("USTUAmmoPickupDecorator"));
    
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;
    
    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return false;
    
    const auto WeaponComponent = Pawn->FindComponentByClass<USTUAIWeaponComponent>();

    return WeaponComponent && WeaponComponent->NeedAmmo();
}
