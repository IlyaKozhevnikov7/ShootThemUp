// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBasePickup.h"
#include "STUAmmoPickup.generated.h"

class ASTUBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickup : public ASTUBasePickup
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditInstanceOnly, Category = "Pickup")
	TSubclassOf<ASTUBaseWeapon> WeaponClass;

	UPROPERTY(EditInstanceOnly, Category = "Pickup", meta = (ClampMin = "0"))
	int32 AmmoAmount;

protected:

	ASTUAmmoPickup();

	virtual bool GivePickupTo(ASTUBaseCharacter* Character) override;

};
