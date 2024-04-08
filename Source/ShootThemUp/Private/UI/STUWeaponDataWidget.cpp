// Shoot Them Up Yata. All Rights Reserved.

#include "STUWeaponDataWidget.h"
#include "STUBaseWeapon.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUWeaponDataWidget::OnNextWeapon(const ASTUBaseWeapon* Weapon)
{
    Icon->SetBrushFromTexture(Weapon->GetUIData().Icon);
    Icon->SetBrushSize(FVector2D(
        Weapon->GetUIData().Icon->GetSizeX(),
        Weapon->GetUIData().Icon->GetSizeY()));
    
    Crosshair->SetBrushFromTexture(Weapon->GetUIData().Crosshair, true);
}

void USTUWeaponDataWidget::OnUIAmmoDataChanged(const FText& _AmmoData)
{
    AmmoData->SetText(_AmmoData);
}
