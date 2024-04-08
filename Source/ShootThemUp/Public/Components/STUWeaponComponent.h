// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUUIInitializable.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;
class ASTUBaseCharacter;
struct FUIData;

DECLARE_MULTICAST_DELEGATE(FOnClimpEmptySignature); // TODO добавить
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNextWeapon, const ASTUBaseWeapon*, Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIAmmoDataChanged, const FText&, AmmoData);

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASTUBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* ReloadAnim;
};

UCLASS(ClassGroup = "STU", meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent, public ISTUUIInitializable
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnNextWeapon OnNextWeapon;

	// для UI когда происжходить изменения AmmoData или при смене оружия
	UPROPERTY(BlueprintAssignable)
	FOnUIAmmoDataChanged OnUIAmmoDataChanged;
    
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnim;

    UPROPERTY()
	UAnimMontage* CurrentReloadAnim;

	TArray<ASTUBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex;

	FName CurrentWeaponeSocketName;

	FName ArmorySocketName;

	UPROPERTY()
	ASTUBaseCharacter* Character;

	bool bEquipWeaponInProgress;

	bool bReloadpWeaponInProgress;
    
protected:

	USTUWeaponComponent();

    virtual void BeginPlay() override;
    
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    
public:

    const ASTUBaseWeapon* GetCurrentWeapon() const { return CurrentWeapon; }
    
	virtual void Fire();

	virtual void StopFire();

	virtual void NextWeapon();

	void Reload();

	bool TryPickupAmmo(const TSubclassOf<ASTUBaseWeapon>& WeaponClass, const int32& AmmoAmount);

    virtual bool CanFire() const;

	virtual void InitializeComponent() override;

    void OnZoom(bool bForceOff = false);

    void PlayReloadAmin();

    virtual void Deactivate() override;
    
//========================== Begin ISTUUIInitializable Interface 
    
    virtual void InitializeUI() const override;
    
protected:

	bool CanReload() const;

    virtual void OnEquipFinished(USkeletalMeshComponent* MeshComp);

    virtual void OnReloadFinished(USkeletalMeshComponent* MeshComp);
    
private:

	void SpawnWeapons();

	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, const FName& SocketName);

	void InitAminations();
    
	void PlayEquipAmin();
    
};
