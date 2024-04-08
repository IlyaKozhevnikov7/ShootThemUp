// Shoot Them Up Yata. All Rights Reserved.

#include "STUWeaponComponent.h"
#include "STUBaseWeapon.h"
#include "STUBaseCharacter.h"
#include "STUEquipFinishedAnimNotify.h"
#include "STUReloadFinishedAnimNotify.h"
#include "AnimUtils.h"
#include "STUPlayerHUD.h"
#include "VisualLogger/VisualLogger.h"

DEFINE_LOG_CATEGORY_STATIC(STULogWeaponComponent, All, All);

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

    bAutoActivate = true;
    
	CurrentWeaponIndex = 0;
	CurrentWeaponeSocketName = "WeaponSocket";
	ArmorySocketName = "ArmorySocket";
	bEquipWeaponInProgress = false;
	bReloadpWeaponInProgress = false;
}

void USTUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;

	for (auto Weapon : Weapons)
	{	    
	    // TODO Реализовать что бы про рестарте раунда и смерти оружия по разному уничтожались (Смерть: выпадали из перса, Рестарт: уничтожались) 
        //if (EndPlayReason == EEndPlayReason::LevelTransition) 
        //{
        //    Weapon->Destroy();   
        //}
	    //else
	    //{
	    //    Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	    //}
	    Weapon->Destroy();   
	}

	Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::Fire()
{    
	if (!CanFire()) return;
	CurrentWeapon->Fire();
}

void USTUWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void USTUWeaponComponent::NextWeapon()
{
	if (bEquipWeaponInProgress || bReloadpWeaponInProgress) return;

	if (CurrentWeapon)
	{
		StopFire();
		AttachWeaponToSocket(CurrentWeapon, ArmorySocketName);
	}

    CurrentWeapon->Zoom(true);
    
	CurrentWeapon = Weapons[++CurrentWeaponIndex %= Weapons.Num()];
	AttachWeaponToSocket(CurrentWeapon, CurrentWeaponeSocketName);

	CurrentReloadAnim = WeaponData[CurrentWeaponIndex].ReloadAnim; // можно (или даже нужно 62 урок) испольховать FindByPredicate
	OnNextWeapon.Broadcast(CurrentWeapon);
	OnUIAmmoDataChanged.Broadcast(CurrentWeapon->GetUIAmmoData());

	PlayEquipAmin();
}

void USTUWeaponComponent::Reload()
{
	if (!CanReload()) return;
    
	StopFire();
	CurrentWeapon->ForceReload();
	Character->PlayAnimMontage(CurrentReloadAnim);
}

bool USTUWeaponComponent::CanFire() const
{
	return CurrentWeapon && !bReloadpWeaponInProgress && !bEquipWeaponInProgress && IsActive();
}

// Инициализация связаная с владельцем происходит здесь
void USTUWeaponComponent::InitializeComponent()
{
	Character = Cast<ASTUBaseCharacter>(GetOwner());
    
	SpawnWeapons();
	InitAminations();
}

void USTUWeaponComponent::OnZoom(bool bForceOff /*= false*/)
{
    if (!bForceOff)
    {
        if (!CurrentWeapon || bReloadpWeaponInProgress || bEquipWeaponInProgress) return;   
    }
    
    CurrentWeapon->Zoom(bForceOff);
}

void USTUWeaponComponent::PlayReloadAmin()
{
    Character->PlayAnimMontage(CurrentReloadAnim);
    bReloadpWeaponInProgress = true;
}

void USTUWeaponComponent::Deactivate()
{
    Super::Deactivate();

    UE_LOG(LogTemp, Display, TEXT("USTUWeaponComponent::Deactivate"));
    OnZoom(true);   
}

void USTUWeaponComponent::InitializeUI() const
{
    //UE_LOG(STULogWeaponComponent, Display, TEXT("USTUWeaponComponent InitUI"));
    OnNextWeapon.Broadcast(CurrentWeapon);
    OnUIAmmoDataChanged.Broadcast(CurrentWeapon->GetUIAmmoData());
}

bool USTUWeaponComponent::CanReload() const
{
	return CurrentWeapon && !CurrentWeapon->IsFullClips() && CurrentWeapon->HasAmmo() && !bReloadpWeaponInProgress && !bEquipWeaponInProgress;
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    if (Character->GetMesh() != MeshComp) return;
    
    bEquipWeaponInProgress = false;
}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
    if (Character->GetMesh() != MeshComp) return;
	  
    OnUIAmmoDataChanged.Broadcast(CurrentWeapon->GetUIAmmoData());
    bReloadpWeaponInProgress = false;
}

void USTUWeaponComponent::SpawnWeapons()
{
	if (!GetWorld() || !Character) return;

	for (const auto& OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClass);
		if (!Weapon) continue;

		Weapon->PickedUp(Character);
		AttachWeaponToSocket(Weapon, ArmorySocketName);
		Weapons.Add(Weapon);
	}
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, const FName& SocketName)
{
	if (!Weapon || !Character->GetMesh()) return;

	if (!CurrentWeapon) // выполнится один раз при начальном спауне оружия
	{
		Weapon->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, CurrentWeaponeSocketName); 
		CurrentReloadAnim = WeaponData[CurrentWeaponIndex].ReloadAnim;
		CurrentWeapon = Weapon;
		PlayEquipAmin();
		OnNextWeapon.Broadcast(CurrentWeapon); // вынести все что выше в метод (+ nextweapon)
		OnUIAmmoDataChanged.Broadcast(CurrentWeapon->GetUIAmmoData());
		return;
	}

	Weapon->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
}

void USTUWeaponComponent::InitAminations()
{
	const auto Notify = AnimUtils::FindNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnim);

	if (Notify)
	{
		Notify->OnNotify.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
	}

	for (const auto Weapon : WeaponData)
	{
		const auto newNotify = AnimUtils::FindNotifyByClass<USTUReloadFinishedAnimNotify>(Weapon.ReloadAnim);

		if (newNotify)
		{
			newNotify->OnNotify.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
		}
	}
}

void USTUWeaponComponent::PlayEquipAmin()
{
	Character->PlayAnimMontage(EquipAnim);
	bEquipWeaponInProgress = true;
}

bool USTUWeaponComponent::TryPickupAmmo(const TSubclassOf<ASTUBaseWeapon>& WeaponClass, const int32& AmmoAmount)
{
	for (const auto& Weapon : Weapons)
	{
		if (Weapon->IsA(WeaponClass) && !Weapon->IsFullAmmo())
		{
			Weapon->AddAmmo(AmmoAmount);
			OnUIAmmoDataChanged.Broadcast(CurrentWeapon->GetUIAmmoData());
			return true;
		}
	}

	return false;
}