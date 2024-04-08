// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUUIInitializable.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, const float&, CurrentHealt, const float&, HealthDelta);

UCLASS(ClassGroup = "STU", meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent, public ISTUUIInitializable
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeath; // TODO попробовать привязать анимацию смерти к событию 

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChanged;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Health", meta = (ClampMin = "0"))
	float MaxHealth;

    UPROPERTY(VisibleInstanceOnly, Category = "Health")
	float CurrentHealth;

    UPROPERTY(EditDefaultsOnly, Category = "Health")
    bool bIsImmortal; 
    
	UPROPERTY(EditDefaultsOnly, Category = "Heal", meta = (EditCondition = "!bIsImmortal"))
	bool bAutoHeal;

	UPROPERTY(EditDefaultsOnly, Category = "Heal", meta = (ClampMin = "0.01", EditCondition = "bAutoHeal && !bIsImmortal"))
	float HealRate;

	UPROPERTY(EditDefaultsOnly, Category = "Heal", meta = (ClampMin = "0.1", EditCondition = "bAutoHeal && !bIsImmortal"))
	float DelayHealAfterDamaged;

	UPROPERTY(EditDefaultsOnly, Category = "Heal", meta = (ClampMin = "1", EditCondition = "bAutoHeal && !bIsImmortal"))
	float HealthModifier;

    UPROPERTY(EditDefaultsOnly, Category = "Damage ")
    TMap<UPhysicalMaterial*, float> DamageModifiers;
    
    UPROPERTY(EditDefaultsOnly, Category = "Camera Shake")
    TSubclassOf<UCameraShakeBase> DamageCameraShake;

	FTimerHandle HealTimerHandle;

protected:

	USTUHealthComponent();
    
public:

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return CurrentHealth == 0; }

    bool HasMaxHealth() const { return CurrentHealth == MaxHealth; }
    
	float GetCurrentHealth() const { return CurrentHealth; }

	float GetHealthPercent() const { return CurrentHealth / MaxHealth; }

	bool TryPickupHealth(const float& HealthAmount);
    
	virtual void InitializeComponent() override;

//========================== Begin ISTUUIInitializable Interface 
    
    void InitializeUI() const override;
    
private:

    UFUNCTION()
    void OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

    UFUNCTION()
    void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);
    
	void AutoHealUpdate();

	void SetHealth(float NewHealth);

    void PlayDamageCameraShake() const;

    void OnDied(AController* Killer);

    void TakeDamage(float Damage, AController* InstigatedBy);

    void ReportDamageEvent(AController* InstigatedBy, float Damage);
};
