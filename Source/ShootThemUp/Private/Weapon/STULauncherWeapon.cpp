// Shoot Them Up Yata. All Rights Reserved.

#include "STULauncherWeapon.h"
#include "STUProjectile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ASTULauncherWeapon::ASTULauncherWeapon()
{
	ShotLength = 7500.f;
	FiringRate = 3.f;
	Damage = 100;
	DamageRadius = 300.f;
    FiringRate = 2.f;
    LastFireTime = 0;
    
	DefaultAmmoData.Clip = 2;
	DefaultAmmoData.Ammo = 6;
}

void ASTULauncherWeapon::Fire()
{   
    if (FPlatformTime::Seconds() - LastFireTime > FiringRate)
    {
        MakeShot();
        LastFireTime = FPlatformTime::Seconds();
    }

    StopFireAI();
}

void ASTULauncherWeapon::StopFire()
{
    // при отжатии мыши ничего не должно происходить
}

void ASTULauncherWeapon::MakeShot()
{
	if (!GetWorld()) return;

    if (!CanFire())
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), NoAmmoSound, Mesh->GetSocketLocation(MuzzleSocketName));
        StopFireAI();
        return;        
    }
    
	ChangeCurrentAmmo();
	LaunchProjectile();
    SpawnMuzzleFX();
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), FiringSound, Mesh->GetSocketLocation(MuzzleSocketName));
    
    Super::MakeShot();
}

void ASTULauncherWeapon::Reload()
{
    Super::Reload();
    LastFireTime = FPlatformTime::Seconds();
}

void ASTULauncherWeapon::LaunchProjectile()
{
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleLocation());
    ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);

    if (!Projectile) return;

    FHitResult Hit;
    FVector Start, End;

    CalculateTrace(Start, End);
	
    End = MakeHit(Hit, Start, End) ? Hit.ImpactPoint : End;

    const FVector ShotDirection = (End - GetMuzzleLocation()).GetSafeNormal();

    Projectile->SetWeapon(this);
    Projectile->SetShotDirection(ShotDirection);
    Projectile->FinishSpawning(SpawnTransform);
}