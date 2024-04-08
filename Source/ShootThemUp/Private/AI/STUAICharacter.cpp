// Shoot Them Up Yata. All Rights Reserved.

#include "STUAICharacter.h"
#include "AIController.h"
#include "STUAIWeaponComponent.h"
#include "STUHealthBarWidget.h"
#include "STUHealthComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USTUAIWeaponComponent>("Weapon Component"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.bCanEverTick = true;
    
    bUseControllerRotationYaw = false;
    if (const auto MovementComponent = GetCharacterMovement())
    {
        MovementComponent->bUseControllerDesiredRotation = true;
        MovementComponent->RotationRate = FRotator(175.f, 100.f, 0.f);
    }

    HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>("Health Bar");
    HealthBarComponent->SetupAttachment(GetRootComponent());
    HealthBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void ASTUAICharacter::BeginPlay()
{
    Super::BeginPlay();

    HealthBarWidget = Cast<USTUHealthBarWidget>(HealthBarComponent->GetUserWidgetObject());
    HealthBarComponent->SetVisibility(false, true);
}

void ASTUAICharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    if (HealthComponent->HasMaxHealth()) return;
    
    const auto Player = GetWorld()->GetFirstPlayerController();
    if (!Player) return;
    
    const auto PlayerPawn = Player->GetPawnOrSpectator();
    if (!PlayerPawn) return;

    const bool bNewVisibility = FVector::Distance(GetActorLocation(), PlayerPawn->GetActorLocation()) > 1500.f;
    HealthBarComponent->SetVisibility(!bNewVisibility, true);
}

void ASTUAICharacter::OnDead()
{    
    Super::OnDead();

    const auto Contr = Cast<AAIController>(GetController());

    if (Contr && Contr->BrainComponent)
    {
        Contr->BrainComponent->Cleanup();
    }
    
    SetActorTickEnabled(false);
    HealthBarComponent->SetVisibility(false, true);
}

void ASTUAICharacter::OnHealthChanged(const float& CurrentHealt, const float& HealthDelta)
{
    if (!HealthComponent || !HealthBarWidget) return;
    
    HealthBarWidget->ChangeHealth(HealthComponent->GetHealthPercent());

    HealthBarComponent->SetVisibility(!HealthComponent->HasMaxHealth(), true);
}

