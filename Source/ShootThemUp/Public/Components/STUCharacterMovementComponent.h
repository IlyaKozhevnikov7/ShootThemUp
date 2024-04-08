// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

class ASTUBaseCharacter;

UCLASS()
class SHOOTTHEMUP_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "5.0"))
	float RunModifier;

	UPROPERTY()
    ASTUBaseCharacter* Character;

public:

	USTUCharacterMovementComponent();

	virtual void BeginPlay() override;

	virtual float GetMaxSpeed() const override;
	
};
