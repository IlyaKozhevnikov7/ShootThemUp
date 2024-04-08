// Shoot Them Up Yata. All Rights Reserved.

#include "STUHealthPickup.h"
#include "STUBaseCharacter.h"
#include "STUHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealhPickup, Display, Display);

ASTUHealthPickup::ASTUHealthPickup()
{
	HealthAmount = 20;
}

bool ASTUHealthPickup::GivePickupTo(ASTUBaseCharacter* Character)
{
	return Character && Character->GetHealthComponent()->TryPickupHealth(HealthAmount);
}