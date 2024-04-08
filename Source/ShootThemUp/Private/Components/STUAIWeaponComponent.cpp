// Shoot Them Up Yata. All Rights Reserved.

#include "STUAIWeaponComponent.h"
#include "STUBaseWeapon.h"

USTUAIWeaponComponent::USTUAIWeaponComponent()
{
    bIsFiring = false;
}

bool USTUAIWeaponComponent::CanFire() const
{
    return Super::CanFire() && CurrentWeapon->CanFire();
}

void USTUAIWeaponComponent::Fire()
{    
    if (!bIsFiring)
    {
        UE_LOG(LogTemp, Display, TEXT("Firing"));
        
        bIsFiring = true;
        Super::Fire();
    }
}

void USTUAIWeaponComponent::StopFire()
{
    UE_LOG(LogTemp, Error, TEXT("StopFire"));
    bIsFiring = false;
    Super::StopFire();
}

void USTUAIWeaponComponent::NextWeapon()
{
    int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

    while (NextIndex != CurrentWeaponIndex)
    {
        const auto NextWeapon = Weapons[NextIndex];

        if (NextWeapon->CanFire() || NextWeapon->HasAmmo())
        {
            Super::NextWeapon();
            return;
        }

        NextIndex = ++NextIndex % Weapons.Num();
    }
}

void USTUAIWeaponComponent::OnStopFire()
{  
    if (CanFire())
    {
        bIsFiring = false;
    }
    else if (CanReload())
    {
        Reload();
    }
    else if (CurrentWeapon->IsFullEmpty() && Weapons.Num() > 1)
    {
        NextWeapon();
    }        
}

bool USTUAIWeaponComponent::NeedAmmo() const
{
    for (const auto Weapon : Weapons)
    {
        if (!Weapon->IsFullEmpty()) return false;
    }

    return true;
}

void USTUAIWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    Super::OnEquipFinished(MeshComp);
    bIsFiring = false;
}

void USTUAIWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
    Super::OnReloadFinished(MeshComp);
    bIsFiring = false;
}
