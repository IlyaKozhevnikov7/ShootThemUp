// Shoot Them Up Yata. All Rights Reserved.

#include "STUBaseWeapon.h"
#include "Engine/World.h"
#include "STUBaseCharacter.h"
#include "STUWeaponComponent.h"
#include "DrawDebugHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "STUAIWeaponComponent.h"
#include "Components/PointLightComponent.h"

DEFINE_LOG_CATEGORY_STATIC(STULogBaseWeapon, All, All);

ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	SetRootComponent(Mesh);
    
	MuzzleSocketName = "MuzzleSocket";

	bNeedRecharge = false;
}

void ASTUBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// правельное направдение из дула
	//DrawDebugLine(
	//	GetWorld(),
	//	GetMuzzleLocation(),
	//	GetMuzzleLocation() + Mesh->GetSocketRotation(MuzzleSocketName).Vector() * ShotLength,
	//	FColor::Purple,
	//	false,
	//	0.1, 
	//	0,
	//	2);
}

void ASTUBaseWeapon::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	CurrentAmmoData = DefaultAmmoData;
}

void ASTUBaseWeapon::Fire()
{
}

void ASTUBaseWeapon::StopFire()
{
    if (Controller->IsPlayerController() /*!CanFire() && HasAmmo()*/)
    {
        Reload();   
    }
}

void ASTUBaseWeapon::PickedUp(ACharacter* Character)
{
    Super::SetOwner(Character);
    
	Controller = Character->GetController();
	CollisionParams.AddIgnoredActor(Character);
    CollisionParams.bReturnPhysicalMaterial = true;
}

void ASTUBaseWeapon::ForceReload()
{
	bNeedRecharge = true;
	Reload();
}

void ASTUBaseWeapon::AddAmmo(const int32& AmmoAmount)
{
	CurrentAmmoData.Ammo = FMath::Clamp<int32>(CurrentAmmoData.Ammo + AmmoAmount, CurrentAmmoData.Ammo, DefaultAmmoData.Ammo);
}

void ASTUBaseWeapon::MakeShot()
{
    if (const auto WeaponComponent = GetOwner()->FindComponentByClass<USTUWeaponComponent>())
    {
        WeaponComponent->OnUIAmmoDataChanged.Broadcast(GetUIAmmoData());   
    }
}

void ASTUBaseWeapon::CalculateTrace(FVector& Start, FVector& End) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    
	Start = ViewLocation;
	End = Start + ViewRotation.Vector() * ShotLength;
}

bool ASTUBaseWeapon::MakeHit(FHitResult& Hit, const FVector& Start, const FVector& End)
{
    
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, CollisionParams))
	{
		//DrawDebugLine(GetWorld(), GetMuzzleLocation(), Hit.ImpactPoint, FColor::Red, false, 0.5f, 0, 2.f);
		//DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 7.5f, 24, FColor::Red, false, 3.f);
		return true;
	}

	//DrawDebugLine(GetWorld(), GetMuzzleLocation(), End, FColor::Red, false, 0.5f, 0, 2.f);
	return false;
}

void ASTUBaseWeapon::ChangeCurrentAmmo()
{
	CurrentAmmoData.Clip--;

	if (CurrentAmmoData.Clip == 0 && CurrentAmmoData.Ammo != 0) bNeedRecharge = true;
}

bool ASTUBaseWeapon::CanFire() const 
{
	return CurrentAmmoData.Clip > 0;
}

void ASTUBaseWeapon::Reload()
{
	if (bNeedRecharge)
	{
		Cast<ASTUBaseCharacter>(GetOwner())->GetWeaponComponent()->PlayReloadAmin();
	    Zoom(true);
	    
		if (CurrentAmmoData.Ammo < DefaultAmmoData.Clip - CurrentAmmoData.Clip)
		{
			CurrentAmmoData.Clip += CurrentAmmoData.Ammo;
			CurrentAmmoData.Ammo = 0;
		}
		else
		{
			CurrentAmmoData.Ammo -= DefaultAmmoData.Clip - CurrentAmmoData.Clip;
			CurrentAmmoData.Clip = DefaultAmmoData.Clip;
		}

		bNeedRecharge = false;
	}
}

void ASTUBaseWeapon::StopFireAI()
{
    if (!Controller->IsPlayerController() && Controller->GetPawn())
    {
        if (const auto WC = Controller->GetPawn()->FindComponentByClass<USTUAIWeaponComponent>())
        {
            UE_LOG(LogTemp, Display, TEXT("ReloadAI"));

			WC->OnStopFire();
        }
    }
}

UNiagaraComponent* ASTUBaseWeapon::SpawnMuzzleFX() const
{
    return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX,
        Mesh,
        MuzzleSocketName,
        FVector::ZeroVector,
        FRotator::ZeroRotator,
        EAttachLocation::SnapToTarget,
        true);
}

void ASTUBaseWeapon::ChangeUIAmmoData() const
{
    Cast<ASTUBaseCharacter>(GetOwner())->GetWeaponComponent()->OnUIAmmoDataChanged.Broadcast(GetUIAmmoData());
}
