// Shoot Them Up Yata. All Rights ReservedС.

#include "STUPlayerHUD.h"

#include "STUGameDataWidget.h"
#include "STUHealthComponent.h"
#include "STUPlayerCharacter.h"
#include "STUPlayerDeadHUD.h"
#include "STUWeaponComponent.h"
#include "STUWeaponDataWidget.h"
#include "Components/ProgressBar.h"

DEFINE_LOG_CATEGORY_STATIC(STULogPlayerHUD, All, All);

void USTUPlayerHUD::Init(APawn* NewPawn)
{    
    if (NewPawn)
    {
        NativeOnInitialized();
    }
    else
    {
        HealthComponent = nullptr;
        WeaponComponent = nullptr;
    }
}

void USTUPlayerHUD::Enable()
{
    Super::Enable();
    
    if (GameData)
    {
        GameData->Enable();   
    }
}

void USTUPlayerHUD::Disable()
{
    Super::Disable();
    
    if (GameData)
    {
        GameData->Disable();   
    }
}

void USTUPlayerHUD::NativeOnInitialized()
{    
    if (const auto Owner = GetOwningPlayerPawn<ASTUPlayerCharacter>())
    {        
        HealthComponent = Owner->GetHealthComponent();
        WeaponComponent = Owner->GetWeaponComponent();

        HealthComponent->OnHealthChanged.AddDynamic(this, &USTUPlayerHUD::OnHealthChanged);
        HealthComponent->OnDeath.AddDynamic(DeathHUD, &USTUPlayerDeadHUD::OnDeath);
        
        WeaponComponent->OnNextWeapon.AddDynamic(WeaponData, &USTUWeaponDataWidget::OnNextWeapon);
        WeaponComponent->OnUIAmmoDataChanged.AddDynamic(WeaponData, &USTUWeaponDataWidget::OnUIAmmoDataChanged);
        
        Super::NativeOnInitialized();

        DeathHUD->NativeOnInitialized();
        Owner->InitializeUI();
    }
}

void USTUPlayerHUD::OnHealthChanged(const float& CurrentHealt, const float& HealthDelta)
{
	HealthBar->SetPercent(HealthComponent->GetHealthPercent());
	
	HealthBar->SetFillColorAndOpacity(FLinearColor(1 - HealthComponent->GetHealthPercent(), HealthComponent->GetHealthPercent(), 0.f));
}
