// Shoot Them Up Yata. All Rights Reserved.

#include "STUPlayerController.h"
#include "STUBaseCharacter.h"
#include "STUGameInstance.h"
#include "STUGameModeBase.h"
#include "STUHealthComponent.h"
#include "STURespawnComponent.h"
#include "STUSoundFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(STULogPlayerController, All, All);

ASTUPlayerController::ASTUPlayerController()
{   
    PrimaryActorTick.bTickEvenWhenPaused = true;
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("Respawn Component");
}

void ASTUPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        if (const auto GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>())
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged);
        }
    }
}

void ASTUPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnPause).bExecuteWhenPaused = true;
    InputComponent->BindAction("Mute", IE_Pressed, this, &ASTUPlayerController::OnMute).bExecuteWhenPaused = true;
}

void ASTUPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    //UE_LOG(STULogPlayerController, Display, TEXT("OnPossess %s"), InPawn ? *InPawn->GetName() : *FString("aboba"));
    
    if (const auto HealthComponent = InPawn->FindComponentByClass<USTUHealthComponent>())
    {
        HealthComponent->OnDeath.AddDynamic(RespawnComponent, &USTURespawnComponent::StartRespawnTimer);
    }
}

void ASTUPlayerController::OnPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    const auto GameMode = GetWorld()->GetAuthGameMode();
    
    if (GameMode->IsPaused())
    {
        GameMode->ClearPause();
    }
    else
    {
        GameMode->SetPause(this);   
    }
}

void ASTUPlayerController::OnMute()
{
    if (!GetWorld()) return;

    const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if (!GameInstance) return;

    USTUSoundFunctionLibrary::ToggleSoundClassVolume(GameInstance->GetMasterSoundClass());
}

void ASTUPlayerController::OnMatchStateChanged(const EMatchState& NewState)
{
    if (NewState == EMatchState::InProgress
        || NewState == EMatchState::WaitingForStart)
    {
        bShowMouseCursor = false;
        SetInputMode(FInputModeGameOnly());
    }
    else
    {
        bShowMouseCursor = true;
        
        // GameAndUI для того что бы можно было убирать паузу через клавиатуру
        SetInputMode(FInputModeGameAndUI());
    }
}
