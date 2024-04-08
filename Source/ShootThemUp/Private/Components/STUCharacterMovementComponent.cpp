// Shoot Them Up Yata. All Rights Reserved.

#include "STUCharacterMovementComponent.h"
#include "STUBaseCharacter.h"

USTUCharacterMovementComponent::USTUCharacterMovementComponent()
{
    RunModifier = 2.f;
}

void USTUCharacterMovementComponent::BeginPlay()
{
    Character = Cast<ASTUBaseCharacter>(GetPawnOwner());
}

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
    if (!Character) return 0.f;
    
    return Character->IsRunning() ? MaxWalkSpeed * RunModifier : MaxWalkSpeed;
}
