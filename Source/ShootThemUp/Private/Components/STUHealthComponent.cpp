// Shoot Them Up Yata. All Rights Reserved.

#include "STUHealthComponent.h"
#include "STUGameModeBase.h"
#include "GameFramework/Character.h"
#include "Perception/AISense_Damage.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

DEFINE_LOG_CATEGORY_STATIC(STULogHealthComponent, All, All);

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    bAutoActivate = true;
    
    MaxHealth = 100.f;
    
    bAutoHeal = false;
    bIsImmortal = false;
    HealRate = 0.5f;
    DelayHealAfterDamaged = 5.f;
    HealthModifier = 1.f;
}

bool USTUHealthComponent::TryPickupHealth(const float& HealthAmount)
{
    if (CurrentHealth < MaxHealth)
    {
        SetHealth(CurrentHealth + HealthAmount);
        return true;
    }

    return false;
}

// Инициализация связаная с владельцем происходит здесь
void USTUHealthComponent::InitializeComponent()
{
    CurrentHealth = MaxHealth;

    if (GetOwner())
    {
        GetOwner()->OnTakePointDamage.AddDynamic(this, &USTUHealthComponent::OnTakePointDamage);
        GetOwner()->OnTakeRadialDamage.AddDynamic(this, &USTUHealthComponent::OnTakeRadialDamage);
    }
}

void USTUHealthComponent::InitializeUI() const
{
    OnHealthChanged.Broadcast(CurrentHealth, 0);
}

void USTUHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation,
    UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{    
    const auto PhysicalMaterial = Cast<ACharacter>(GetOwner())->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
    if (DamageModifiers.Contains(PhysicalMaterial))
    {
        Damage *= DamageModifiers[PhysicalMaterial];
    }

    if (const auto Owner = Cast<ACharacter>(GetOwner()))
    {
        if (Owner->GetController() &&
            !Owner->GetController()->IsPlayerController())
        {
            ReportDamageEvent(InstigatedBy, Damage);            
        }
    }
    
    TakeDamage(Damage, InstigatedBy);
}

void USTUHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin,
    FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
    TakeDamage(Damage, InstigatedBy);
}

void USTUHealthComponent::AutoHealUpdate()
{
    SetHealth(CurrentHealth + HealthModifier);

    if (HasMaxHealth())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
    // если HealthDelta < 0, то был был нанесен урон, елси > 0, то был хил 
    const float HealthDelta = NewHealth - CurrentHealth; 
    
    CurrentHealth = FMath::Clamp<float>(NewHealth, 0, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth, HealthDelta);
}

void USTUHealthComponent::PlayDamageCameraShake() const
{
    if (!DamageCameraShake) return;

    if (auto Controller = GetOwner<APawn>()->GetController<APlayerController>())
    {
        Controller->PlayerCameraManager->StartCameraShake(DamageCameraShake);
    }
}

void USTUHealthComponent::OnDied(AController* Killer)
{
    if (!Killer || !GetWorld()) return;
    
    const auto GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();

    if (!GameMode) return;
    
    GameMode->OnKilled(Killer, GetOwner<APawn>()->GetController());    
}

void USTUHealthComponent::TakeDamage(float Damage, AController* InstigatedBy)
{
    if (bIsImmortal || Damage <= 0.f || CurrentHealth == 0 || !GetWorld()) return;
    
    if (Damage >= CurrentHealth)
    {
        SetHealth(0);
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
        OnDied(InstigatedBy);
        OnDeath.Broadcast();
        return;
    }

    if (bAutoHeal)
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::AutoHealUpdate, HealRate, true,
            DelayHealAfterDamaged);
    }

    SetHealth(CurrentHealth - Damage);
    PlayDamageCameraShake();
}

void USTUHealthComponent::ReportDamageEvent(AController* InstigatedBy, float Damage)
{    
    if (!GetWorld() || !GetOwner() || !InstigatedBy->GetPawn()) return;
    
    UAISense_Damage::ReportDamageEvent(
        GetWorld(),
        GetOwner(),
        InstigatedBy->GetPawn(),
        Damage,
        InstigatedBy->GetPawn()->GetActorLocation(),
        GetOwner()->GetActorLocation());
}
