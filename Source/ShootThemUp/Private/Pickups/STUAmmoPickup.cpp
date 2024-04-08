// Shoot Them Up Yata. All Rights Reserved.

#include "STUAmmoPickup.h"
#include "STUBaseCharacter.h"
#include "STUWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, Display, Display);

ASTUAmmoPickup::ASTUAmmoPickup()
{
	AmmoAmount = 10;
}

bool ASTUAmmoPickup::GivePickupTo(ASTUBaseCharacter* Character)
{
	return Character && Character->GetWeaponComponent()->TryPickupAmmo(WeaponClass, AmmoAmount);
}
