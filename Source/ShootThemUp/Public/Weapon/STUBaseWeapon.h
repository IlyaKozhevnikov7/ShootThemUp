// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	int32 Clip;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	int32 Ammo;
};

USTRUCT(BlueprintType)
struct FUIData
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Crosshair;
};

UCLASS(BlueprintType)
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	USkeletalMeshComponent* Mesh;
    
	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	FAmmoData DefaultAmmoData;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FUIData UIData;

    UPROPERTY(EditDefaultsOnly, Category = "VFX")
    UNiagaraSystem* MuzzleFX;

    UPROPERTY()
    AController* Controller;

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundCue* FiringSound;
    
    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundCue* NoAmmoSound;
    
    UPROPERTY(VisibleDefaultsOnly, Category = "Socket")
    FName MuzzleSocketName;

    UPROPERTY(EditDefaultsOnly, Category = "Shooting", meta = (ClampMin = "1000"))
    float ShotLength;

    UPROPERTY(EditDefaultsOnly, Category = "Shooting", meta = (ClampMin = "1"))
    int32 Damage;

    UPROPERTY(EditDefaultsOnly, Category = "Shooting", meta = (ClampMin = "0.05"))
    float FiringRate;

    FTimerHandle RateOfFireTimer;
    
	//FOnClimpEmptySignature OnClimpEmpty;

private:

    FCollisionQueryParams CollisionParams;
    
	bool bNeedRecharge;
    
    UPROPERTY(VisibleInstanceOnly, Category = "Ammo Data")
	FAmmoData CurrentAmmoData;

protected:
	
	ASTUBaseWeapon();
    
	virtual void Tick(float DeltaTime) override;

public:

	virtual void PreInitializeComponents() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	const FUIData& GetUIData() const { return UIData; }

	FText GetUIAmmoData() const { return FText::FromString(FString::Printf(TEXT("%i / %i"), CurrentAmmoData.Clip, CurrentAmmoData.Ammo)); }

    AController* GetOwnerController() const { return Controller; }
    
	bool CanFire() const;

	virtual void Fire();

	virtual void StopFire();

	void PickedUp(ACharacter* Character);

	int32 GetDamage() const { return Damage; }

	bool IsFullClips() const { return CurrentAmmoData.Clip == DefaultAmmoData.Clip; }

	bool IsFullAmmo() const { return CurrentAmmoData.Ammo == DefaultAmmoData.Ammo; }

    bool IsFullEmpty() const { return CurrentAmmoData.Ammo == 0 && CurrentAmmoData.Clip == 0; }
    
	bool HasAmmo() const { return CurrentAmmoData.Ammo != 0; }

	void ForceReload();

	void AddAmmo(const int32& AmmoAmount);

    virtual void Zoom(bool bForceOff = false) {}
    
protected:

	FVector GetMuzzleLocation() const { return Mesh->GetSocketLocation(MuzzleSocketName); }

	virtual void MakeShot();

	virtual void MakeDamage(const FHitResult& Hit) {}

	virtual void CalculateTrace(FVector& Start, FVector& End) const;

	bool MakeHit(FHitResult& Hit, const FVector& Start, const FVector& End);

	void ChangeCurrentAmmo();

	virtual void Reload();

    void StopFireAI();
    
    UNiagaraComponent* SpawnMuzzleFX() const;

    void ChangeUIAmmoData() const;
};
