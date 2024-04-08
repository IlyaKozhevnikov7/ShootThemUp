// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBasePickup.h"
#include "STUHealthPickup.generated.h"

class ASTUBaseCharacter;

UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickup
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "Pickup")
	int32 HealthAmount;

protected:

	ASTUHealthPickup();

	virtual bool GivePickupTo(ASTUBaseCharacter* Character) override;

};
