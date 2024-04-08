// Shoot Them Up Yata. All Rights Reserved.

#include "STUWeaponChangeService.h"
#include "AIController.h"
#include "STUAIWeaponComponent.h"
#include "STUBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(STULogWeaponChangeService, All, All);

USTUWeaponChangeService::USTUWeaponChangeService()
{
    NodeName = "Weapon Change";
    Probability = 0.5f;
}

void USTUWeaponChangeService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = Cast<AAIController>(OwnerComp.GetAIOwner());

    if (auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<USTUAIWeaponComponent>())
    {
        if ((!WeaponComponent->GetCurrentWeapon()->CanFire() && !WeaponComponent->GetCurrentWeapon()->HasAmmo())
            || Probability > FMath::FRand())
        {
            UE_LOG(STULogWeaponChangeService, Display, TEXT("want NextWeapon"))
            WeaponComponent->NextWeapon();   
        }
    }
}

