// Shoot Them Up Yata. All Rights Reserved.

#include "STUBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "STUCharacterMovementComponent.h"
#include "STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "STUBaseWeapon.h"
#include "STUWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(STULogBaseCharacter, Display, Display);

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer &ObjectInitializer) 
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
    
    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("Health Component");
    WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("Weapon Component");

    LandedDamageVelocity = FVector2D(1000, 1500);
    LandedDamage = FVector2D(15, 100);

    LifeSpanTime = 5.f;
    MaterialTeamColorName = "Paint Color";
}

void ASTUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    UE_LOG(STULogBaseCharacter, Warning, TEXT("BeginPlay"));
    
    HealthComponent->OnDeath.AddDynamic(this, &ASTUBaseCharacter::OnDead);
    HealthComponent->OnHealthChanged.AddDynamic(this, &ASTUBaseCharacter::OnHealthChanged);
    
    LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnLandedHandler);
}

void ASTUBaseCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    
    if (NewController)
    {
        HealthComponent->InitializeComponent();
        WeaponComponent->InitializeComponent();
    }
}

void ASTUBaseCharacter::OnRunning()
{
    bWantsRunning = true;
}

void ASTUBaseCharacter::OnStopRunning()
{
    bWantsRunning = false;
}

void ASTUBaseCharacter::OnDead()
{
    UE_LOG(STULogBaseCharacter, Display, TEXT("OnDead"));
    
    GetCharacterMovement()->DisableMovement();

    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SetLifeSpan(LifeSpanTime);
    WeaponComponent->StopFire();

    if (const auto PlayerMesh = GetMesh())
    {
        PlayerMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        PlayerMesh->SetSimulatePhysics(true);
    }
    else
    {
        PlayAnimMontage(AnimDeath);
    }

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void ASTUBaseCharacter::OnHealthChanged(const float& CurrentHealt, const float& HealthDelta)
{
}

bool ASTUBaseCharacter::IsRunning()
{
    return bWantsRunning && !GetVelocity().IsZero();
}

float ASTUBaseCharacter::GetCharacterDirection() const
{
    if (GetVelocity().IsZero()) return 0.f;

    const FVector VelocityNormal = GetVelocity().GetSafeNormal();

    const float Angle = FVector::DotProduct(GetActorForwardVector(), VelocityNormal);
    const float Sign = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal).GetSignVector().Z; // крос продукт может быть 0 при одинаковых или противоположных вектрах ???????

    return FMath::RadiansToDegrees(FMath::Acos(Angle) * Sign);
} 

void ASTUBaseCharacter::SetTeamColor(const FLinearColor& LinearColor)
{
    if (!GetMesh()) return;
    
    auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);

    if (!MaterialInstance) return;
    MaterialInstance->SetVectorParameterValue(MaterialTeamColorName, LinearColor);
}

void ASTUBaseCharacter::Activate()
{
    if (!WeaponComponent || !GetCharacterMovement()) return;
    
    WeaponComponent->Activate();
    GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void ASTUBaseCharacter::Deactivate()
{
    if (!WeaponComponent || !GetCharacterMovement()) return;
    
    WeaponComponent->Deactivate();
    GetCharacterMovement()->DisableMovement();
}

void ASTUBaseCharacter::OnLandedHandler(const FHitResult& Hit)
{
    const float LandedVelocity = -GetVelocity().Z;

    if (LandedVelocity < LandedDamageVelocity.X) return;
    
    const float Damage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, LandedVelocity);

    TakeDamage(Damage, FPointDamageEvent{}, GetController(), this); // самоубийство
}
