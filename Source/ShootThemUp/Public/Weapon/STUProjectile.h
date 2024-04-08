// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class ASTULauncherWeapon;
class USTUWeaponFXComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY()
	ASTULauncherWeapon* OwnWeapon;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USTUWeaponFXComponent* WeaponFXComponent;

private:

	FVector ShotDirection;

protected:

	ASTUProjectile();

	virtual void BeginPlay() override;

public:

	void SetShotDirection(const FVector Direction) { ShotDirection = Direction; }

	void SetWeapon(ASTULauncherWeapon* Weapon) { OwnWeapon = Weapon; }

private:

    virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
    
};
