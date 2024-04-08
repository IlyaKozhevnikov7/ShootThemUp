// Shoot Them Up Yata. All Rights Reserved.

#include "STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "STULauncherWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "STUWeaponFXComponent.h"
#include "DrawDebugHelpers.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	Collision->InitSphereRadius(10.f);
	Collision->BodyInstance.bNotifyRigidBodyCollision = true;
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    Collision->bReturnMaterialOnMove = true;
	SetRootComponent(Collision);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	MovementComponent->InitialSpeed = 5000.f;

	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("Weapon FX Component");
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;

	SetLifeSpan(15.f);
}

void ASTUProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
    FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    MovementComponent->StopMovementImmediately();

    UGameplayStatics::ApplyRadialDamage(
        GetWorld(),
        OwnWeapon->GetDamage(),
        GetActorLocation(),
        OwnWeapon->GetDamageRadius(),
        UDamageType::StaticClass(),
        {OwnWeapon},
        OwnWeapon,
        OwnWeapon->GetOwnerController(),
        false, 
        ECC_MAX); // урок 56 костыль (снаряд наносит урон через препятсвия)

    Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
    WeaponFXComponent->PlayImpactFX(Hit);

    //DrawDebugSphere(GetWorld(), GetActorLocation(), OwnWeapon->GetDamageRadius(), 24, FColor::Red, false, 1.5f);
    SetLifeSpan(5.f);

    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
}
