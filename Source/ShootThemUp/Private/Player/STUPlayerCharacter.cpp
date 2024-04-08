// Shoot Them Up Yata. All Rights Reserved.

#include "STUPlayerCharacter.h"
#include "STUWeaponComponent.h"
#include "STUCameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY_STATIC(STULogPlayerCharacter, Display, Display);

ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bWantsRunning = false;
    
    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->bUsePawnControlRotation = true;
    SpringArm->SocketOffset = FVector(0.f, 75.f, 75.f);

    Camera = CreateDefaultSubobject<USTUCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm);
}

void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (!PlayerInputComponent) { UE_LOG(STULogPlayerCharacter, Error, TEXT("PlayerInputComponent is null")); return;  }
    if (!WeaponComponent) { UE_LOG(STULogPlayerCharacter, Error, TEXT("WeaponComponent is null")); return; }
   
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUPlayerCharacter::OnRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUPlayerCharacter::OnStopRunning);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Fire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("WeaponChange", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Recharge", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);

    //DECLARE_DELEGATE_OneParam(FOnZoomSignature, bool);
    //PlayerInputComponent->BindAction<FOnZoomSignature>("Zoom", IE_Pressed, WeaponComponent, &USTUWeaponComponent::OnZoom, false);
    
    PlayerInputComponent->BindAxis("MoveForward", this, &ASTUPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ACharacter::AddControllerYawInput);
}

void ASTUPlayerCharacter::InitializeUI() const
{
    const TArray<UActorComponent*> Components = GetComponentsByInterface(USTUUIInitializable::StaticClass());

    for (const auto Component : Components)
    {
        Cast<ISTUUIInitializable>(Component)->InitializeUI();
    }
}

void ASTUPlayerCharacter::OnRunning()
{
    bWantsRunning = true;
}

void ASTUPlayerCharacter::OnStopRunning()
{
    bWantsRunning = false;
}

void ASTUPlayerCharacter::Activate()
{
    Super::Activate();

    if (GetController<APlayerController>() && GetController<APlayerController>()->InputComponent)
    {
        DECLARE_DELEGATE_OneParam(FOnZoomSignature, bool);
        InputComponent->BindAction<FOnZoomSignature>("Zoom", IE_Pressed, WeaponComponent, &USTUWeaponComponent::OnZoom, false);
    }
}

void ASTUPlayerCharacter::Deactivate()
{
    Super::Deactivate();
    
    if (Controller && Controller->InputComponent)
    {
        InputComponent->RemoveActionBinding("Zoom", IE_Pressed);
    }
}

void ASTUPlayerCharacter::OnDead()
{
    Super::OnDead();
    
    if (Controller)
    {
        WeaponComponent->OnZoom(true);        
        Controller->ChangeState(NAME_Spectating);
    }
}

void ASTUPlayerCharacter::MoveForward(float Value)
{
    if (Value != 0)
    {
        AddMovementInput(GetActorForwardVector(), Value);   
    }
}

void ASTUPlayerCharacter::MoveRight(float Value)
{
    if (Value != 0)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}
