// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USTUHealthComponent;
class UTextRenderComponent;
class USTUWeaponComponent;
class USoundCue;

UCLASS(HideFunctions = ("Component"))
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bWantsRunning;
    
protected:

    UPROPERTY(VisibleAnywhere, Category = "Component")
    USTUHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, Category = "Component")
    UTextRenderComponent* TextRenderComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USTUWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* AnimDeath;

private:

    UPROPERTY(EditDefaultsOnly, Category = "Death")
    USoundCue* DeathSound;
    
	UPROPERTY(EditAnywhere, Category = "Health")
	FVector2D LandedDamageVelocity;

	UPROPERTY(EditAnywhere, Category = "Health")
	FVector2D LandedDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	float LifeSpanTime;

    FName MaterialTeamColorName;
    
protected:

	ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer);
    
	virtual void BeginPlay() override;

    virtual void PossessedBy(AController* NewController) override;
    
public:

	UFUNCTION(BlueprintCallable, Category = "Health")
	USTUHealthComponent* GetHealthComponent() const { return HealthComponent; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	USTUWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }
    
	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetCharacterDirection() const;
    
    void SetTeamColor(const FLinearColor& LinearColor);

    virtual void Activate();

    virtual void Deactivate();
    
protected:

    UFUNCTION()
    virtual void OnDead();

    UFUNCTION()
    virtual void OnHealthChanged(const float& CurrentHealt, const float& HealthDelta);

    virtual void OnRunning();

    virtual void OnStopRunning();
    
private:
    
    UFUNCTION()
	void OnLandedHandler(const FHitResult& Hit);
};
