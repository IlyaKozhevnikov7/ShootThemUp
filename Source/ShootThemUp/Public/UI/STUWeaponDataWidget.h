// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUWeaponDataWidget.generated.h"

class UTextBlock;
class UImage;
class ASTUBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API USTUWeaponDataWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UTextBlock* AmmoData;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UImage* Icon;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UImage* Crosshair;
    
public:

    UFUNCTION()
    void OnNextWeapon(const ASTUBaseWeapon* Weapon);

    UFUNCTION()
    void OnUIAmmoDataChanged(const FText& _AmmoData);
    
};
