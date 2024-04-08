// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTUProjectile;

UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	TSubclassOf<ASTUProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Shooting", meta = (ClampMin = "200"))
	float DamageRadius;

    float LastFireTime;
    
protected:

	ASTULauncherWeapon();

	virtual void Fire() override;

    virtual void StopFire() override;
    
public:

	float GetDamageRadius() const { return DamageRadius; }

protected:
    
	virtual void MakeShot() override;

    virtual void Reload() override;

    void LaunchProjectile();
};
