// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USTUWeaponFXComponent* WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Component")
    UAudioComponent* AudioComponent;
    
    UPROPERTY(EditDefaultsOnly, Category = "VFX")
    UNiagaraSystem* TraceVF;

    UPROPERTY(VisibleDefaultsOnly, Category = "VFX")
    FString TraceFXEndName;
    
    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;
    
	UPROPERTY(EditDefaultsOnly, Category = "Shooting", meta = (ClampMin = "0"))
	float ShootingSpread;

    UPROPERTY(EditDefaultsOnly, Category = "Shooting", meta = (ClampMin = "0"))
    float ZoomFOV;

    bool bHasZoom;

protected:

	ASTURifleWeapon();

public:

	virtual void Fire() override;

	virtual void StopFire() override;
    
	void MakeShot() override;

    virtual void MakeDamage(const FHitResult& Hit) override;

    virtual void Zoom(bool bForceOff = false) override;
    
private:

	virtual void CalculateTrace(FVector& Start, FVector& End) const override;

    void InitMuzzleFX();
    
    void SetMuzzleFXVisibility(bool bVisible);

    void SpawnTraceFX(const FVector& Start, const FVector& End);
};
