// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/STUWeaponComponent.h"
#include "STUAIWeaponComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE(FNeedChangeWeapon);

UCLASS()
class SHOOTTHEMUP_API USTUAIWeaponComponent : public USTUWeaponComponent
{
	GENERATED_BODY()

public:

    bool bIsFiring;

protected:
    
    USTUAIWeaponComponent();
    
public:

    virtual bool CanFire() const override;
    
    virtual void Fire() override;

    virtual void StopFire() override;
    
    virtual void NextWeapon() override;

    void OnStopFire();
    
    bool NeedAmmo() const;

protected:

    virtual void OnEquipFinished(USkeletalMeshComponent* MeshComp) override;

    virtual void OnReloadFinished(USkeletalMeshComponent* MeshComp) override;
};
