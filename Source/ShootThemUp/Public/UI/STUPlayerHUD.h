// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUPlayerHUD.generated.h"

class UProgressBar;
class USTUPlayerDeadHUD;
class USTUWeaponDataWidget;
class USTUHealthComponent;
class USTUWeaponComponent;
class USTUGameDataWidget;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUD : public USTUBaseWidget
{
	GENERATED_BODY()

protected:

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY(meta = (BindWidget))
    USTUWeaponDataWidget* WeaponData;
    
    UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (BindWidget))
    USTUPlayerDeadHUD* DeathHUD;
    
    UPROPERTY(meta = (BindWidget))
    USTUGameDataWidget* GameData;
    
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	USTUHealthComponent* HealthComponent;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	USTUWeaponComponent* WeaponComponent;

public:
    
    // аргумент нужен для сигнатуры OnNewPawn в контроллере
    void Init(APawn* NewPawn);

    virtual void Enable() override;
    
    virtual void Disable() override;
    
protected:
    
    virtual void NativeOnInitialized() override;

private:
    
    UFUNCTION()
	void OnHealthChanged(const float& CurrentHealt, const float& HealthDelta);
};
