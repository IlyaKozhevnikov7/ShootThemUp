// Shoot Them Up Yata. All Rights Reserved.

#include "STUGameModeBase.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "STUBaseCharacter.h"
#include "STUBaseWeapon.h"
#include "STUPlayerController.h"
#include "STUHUD.h"
#include "STUPlayerCharacter.h"
#include "STUPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(STULogGameModBase, All, All);

ASTUGameModeBase::ASTUGameModeBase()
{
    DefaultPawnClass = ASTUPlayerCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUHUD::StaticClass();
    PlayerStateClass = ASTUPlayerState::StaticClass();

    CurrentRound = 1;
    RemainingTime = GameData.WaitingToStart;
    MatchState = EMatchState::InProgress;
}

void ASTUGameModeBase::StartPlay()
{
    SpawnBots();
    DistributeByTeams();

    Super::StartPlay();

    NextRound();
}

bool ASTUGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const bool bIsPauseResult = Super::SetPause(PC, CanUnpauseDelegate);

    if (bIsPauseResult)
    {
        PreviousMatchState = MatchState;
        ChangeMatchState(EMatchState::Pause);
    }
    
    return bIsPauseResult;
}

bool ASTUGameModeBase::ClearPause()
{
    const bool bClearPauseResult = Super::ClearPause();

    if (bClearPauseResult)
    {
        ChangeMatchState(PreviousMatchState);
    }

    return bClearPauseResult;
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }

    return DefaultPawnClass;
}

void ASTUGameModeBase::OnKilled(AController* KillerContrller, AController* VictimController) const
{
    auto KillerState = KillerContrller ? KillerContrller->GetPlayerState<ASTUPlayerState>() : nullptr;
    auto VictimState = VictimController ? VictimController->GetPlayerState<ASTUPlayerState>() : nullptr;

    if (!KillerState || !VictimState) return;

    KillerState->AddKills();
    VictimState->AddDeath();
}

void ASTUGameModeBase::RespawnPlayer(AController* Controller)
{
    // TODO может быть эту проверку можно сделать в респаункомпоненте
    if (RemainingTime - GameData.RespawnTime > 0)
    {
        ResetOnePLayer(Controller);
    }
}

void ASTUGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;

    FActorSpawnParameters SpawnParameters;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    for (int32 i = 0; i < GameData.PlayersNumber - 1; i++)
    {
        const auto Controller = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnParameters);
        ResetOnePLayer(Controller);
    }
}

void ASTUGameModeBase::NextRound()
{
    for (const auto Character : TActorRange<ASTUBaseCharacter>(GetWorld()))
    {
        Character->Deactivate();
    }

    RemainingTime = GameData.WaitingToStart;

    ChangeMatchState(EMatchState::WaitingForStart);
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASTUGameModeBase::WaitForStart, 1.25f, true, 0.f);
}

void ASTUGameModeBase::StartRound()
{
    ChangeMatchState(EMatchState::InProgress);
    //ClearLevel();

    for (const auto Character : TActorRange<ASTUBaseCharacter>(GetWorld()))
    {
        Character->Activate();
    }

    RemainingTime = GameData.RoundTime;
    OnUpdateTimer.Broadcast(RemainingTime);
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ASTUGameModeBase::UpdateRoundTime, 1.f, true);
    OnNewRound.Broadcast(CurrentRound);
}

void ASTUGameModeBase::UpdateRoundTime()
{
    if (RemainingTime == 1)
    {
        GetWorldTimerManager().ClearTimer(TimerHandle);
        if (CurrentRound + 1 > GameData.RoundsNumber)
        {
            DecreaseTime();
            FinishGame();
        }
        else
        {
            CurrentRound++;
            ResetPlayers();
            NextRound();
        }
    }
    else
    {
        DecreaseTime();
    }
}

void ASTUGameModeBase::DecreaseTime()
{
    RemainingTime--;
    OnUpdateTimer.Broadcast(RemainingTime);
}

void ASTUGameModeBase::ResetPlayers()
{
    if (!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePLayer(It->Get());
    }
}

void ASTUGameModeBase::ResetOnePLayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Destroy();
    }

    RestartPlayer(Controller);
    SetPlayerTeamColor(Controller);
    Cast<ASTUBaseCharacter>(Controller->GetCharacter())->Activate();
}

void ASTUGameModeBase::DistributeByTeams()
{
    if (!GetWorld()) return;

    int32 TeamID = 0;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        auto PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
        if (!PlayerState) continue;

        PlayerState->SetTeamID(TeamID);

        const auto TeamColor = DefineTeamColorByID(TeamID);
        PlayerState->SetTeamColor(TeamColor);
        SetPlayerTeamColor(Controller);

        TeamID = ++TeamID % GameData.TeamColors.Num(); // TODO если в масиве цветов будет 0 єлементов то будет ошибка (/0)
    }
}

FLinearColor ASTUGameModeBase::DefineTeamColorByID(int32 ID)
{
    return GameData.TeamColors.Num() > ID
        ? GameData.TeamColors[ID]
        : GameData.DefaultTeamColor;
}

void ASTUGameModeBase::SetPlayerTeamColor(AController* Controller)
{
    if (!Controller) return;

    auto Character = Controller->GetPawn<ASTUBaseCharacter>();
    if (!Character) return;

    const auto PlayerState = Controller->GetPlayerState<ASTUPlayerState>();

    Character->SetTeamColor(PlayerState->GetTeamColor());
}

void ASTUGameModeBase::LogTempInfo()
{
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        if (const auto Controller = It->Get())
        {
            if (const auto State = Controller->GetPlayerState<ASTUPlayerState>())
            {
                //UE_LOG(STULogGameModBase, Display, TEXT("%s :: %i | %i"), *Controller->GetName(), State->GetKills(), State->GetDeaths());   
            }
        }
    }
}

void ASTUGameModeBase::ClearLevel()
{
    TArray<AActor*> Actors = GetLevel()->Actors;

    if (Actors.Num() == 0) return;

    for (const auto Actor : Actors)
    {
        if (Actor->IsA<ASTUBaseWeapon>()) continue;
        //{
        //    Actor->Destroy();
        //}
    }
}

void ASTUGameModeBase::FinishGame()
{
    if (!GetWorld()) return;

    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }

    ChangeMatchState(EMatchState::GameOver);
}

void ASTUGameModeBase::ChangeMatchState(const EMatchState& NewState)
{
    if (MatchState == NewState) return;

    UE_LOG(STULogGameModBase, Display, TEXT("ChangeMatchState %s"), *UEnum::GetValueAsString(NewState));

    //PreviousMatchState = MatchState;
    MatchState = NewState;
    OnMatchStateChanged.Broadcast(MatchState);
}

void ASTUGameModeBase::WaitForStart()
{
    OnUpdateTimer.Broadcast(RemainingTime);
    RemainingTime--;

    if (RemainingTime == -1
        && GetWorld()
        && &GetWorld()->GetTimerManager())
    {
        GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
        StartRound();
    }
}
