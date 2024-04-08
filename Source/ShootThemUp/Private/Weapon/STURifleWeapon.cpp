// Shoot Them Up Yata. All Rights Reserved.

#include "STURifleWeapon.h"
#include "AIController.h"
#include "STUWeaponFXComponent.h"
#include "DrawDebugHelpers.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "STUBaseCharacter.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(STULogRifleWeapon, All, All);

ASTURifleWeapon::ASTURifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("Weapon FX Component");
    AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio Component");
    AudioComponent->SetupAttachment(GetRootComponent(), MuzzleSocketName);
    AudioComponent->SetAutoActivate(false);
    
	ShotLength = 10000.f;
	FiringRate = 0.1f;
	Damage = 25;
	ShootingSpread = 2.f;
    ZoomFOV = 50.f;
    bHasZoom = false;
    
	DefaultAmmoData.Clip = 30;
	DefaultAmmoData.Ammo = 90;

    TraceFXEndName = "TraceEnd";
}

void ASTURifleWeapon::Fire()
{   
    InitMuzzleFX();
    AudioComponent->Play();
	GetWorldTimerManager().SetTimer(RateOfFireTimer, this, &ASTURifleWeapon::MakeShot, FiringRate, true, 0.f);
}

void ASTURifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(RateOfFireTimer);
    SetMuzzleFXVisibility(false);
    AudioComponent->Stop();
	Super::StopFire();
}

void ASTURifleWeapon::MakeShot()
{   
	if (!CanFire())
	{
		GetWorldTimerManager().ClearTimer(RateOfFireTimer);
	    SetMuzzleFXVisibility(false);
	    AudioComponent->Stop();
	   
	    UGameplayStatics::PlaySoundAtLocation(GetWorld(), NoAmmoSound, Mesh->GetSocketLocation(MuzzleSocketName));

	    StopFireAI();
	    
		return;
	}
    
	ChangeCurrentAmmo();
    
	FHitResult Hit;
	FVector Start, End;    
	CalculateTrace(Start, End);
    
	if (MakeHit(Hit, Start, End))
	{
	    End = Hit.ImpactPoint;
	    MakeDamage(Hit);
	    WeaponFXComponent->PlayImpactFX(Hit);
	}
    
    SpawnTraceFX(GetMuzzleLocation(), End);
    Super::MakeShot();
}

void ASTURifleWeapon::MakeDamage(const FHitResult& Hit)
{	
    if (const auto DamagedPlayer = Cast<ASTUBaseCharacter>(Hit.Actor))
	{        
        FPointDamageEvent PointDamageEvent;
        PointDamageEvent.HitInfo = Hit;
        
		DamagedPlayer->TakeDamage(Damage, PointDamageEvent, Controller, this);
	}
}

void ASTURifleWeapon::Zoom(bool bForceOff /*= false*/)
{
	if (!Controller->IsPlayerController()) return;

    const auto CameraManager = Cast<APlayerController>(Controller)->PlayerCameraManager;

    if (bForceOff && CameraManager)
    {
        CameraManager->SetFOV(CameraManager->DefaultFOV);
        bHasZoom = false;
        return;
    }
    
    if (CameraManager)
    {
        bHasZoom = !bHasZoom;
        CameraManager->SetFOV(bHasZoom ? ZoomFOV : CameraManager->DefaultFOV);
    }
}

void ASTURifleWeapon::CalculateTrace(FVector& Start, FVector& End) const
{       
    if (Controller->IsPlayerController())
    {
        FVector ViewLocation;
        FRotator ViewRotation;
        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
        
        Start = ViewLocation;
        End = Start + (FMath::VRandCone(ViewRotation.Vector(), FMath::DegreesToRadians(ShootingSpread))) * ShotLength;
    }
    else
    {
        Start = GetMuzzleLocation();
        End = Start + Mesh->GetSocketRotation(MuzzleSocketName).Vector() * ShotLength;
    }
}

void ASTURifleWeapon::InitMuzzleFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    
    SetMuzzleFXVisibility(true);

    if (!CanFire() && GetWorld())
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), NoAmmoSound, Mesh->GetSocketLocation(MuzzleSocketName));
    }
}

void ASTURifleWeapon::SetMuzzleFXVisibility(bool bVisible)
{
    if (!MuzzleFXComponent) return;

    MuzzleFXComponent->SetPaused(!bVisible);
    MuzzleFXComponent->SetVisibility(bVisible);
}

void ASTURifleWeapon::SpawnTraceFX(const FVector& Start, const FVector& End)
{
    if (const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceVF, Start))
    {        
        TraceFXComponent->SetNiagaraVariableVec3(TraceFXEndName, End);
    }
}
