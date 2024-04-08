// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateTimerSignature, const int32&, NewTime);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewRoundSignature, const int32&);

class AAIController;

UENUM()
enum class EMatchState : uint8
{
    WaitingForStart = 0,
    InProgress,
    Pause,
    GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, const EMatchState&);

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_USTRUCT_BODY()

public:
    
    UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "20"))
    int32 PlayersNumber = 20;

    UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
    int32 RoundsNumber = 3;

    UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
    int32 RoundTime = 3;

    UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "0", ClampMax = "15"))
    int32 WaitingToStart = 3;
    
    // количество команд зависит от количеста цветов
    //UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "2"))
    //int32 TeamsNumber = 2;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TArray<FLinearColor> TeamColors;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FLinearColor DefaultTeamColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, Category = "Game | Respawn", meta = (ClampMin = "0"))
    float RespawnTime = 3.f;
};

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintAssignable)
    FOnUpdateTimerSignature OnUpdateTimer;

    FOnNewRoundSignature OnNewRound;

    FOnMatchStateChangedSignature OnMatchStateChanged;
    
private:

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

    int32 CurrentRound;

    int32 RemainingTime;

    EMatchState MatchState;

    EMatchState PreviousMatchState;
    
    FTimerHandle TimerHandle;
    
protected:

    ASTUGameModeBase();
    
public:

    virtual void StartPlay() override;
    
    FGameData GetGameData() const { return GameData; }

    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
    
    virtual bool ClearPause() override;
    
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    void OnKilled(AController* KillerContrller, AController* VictimController) const;
    
    void RespawnPlayer(AController* Controller);

private:
    
    void SpawnBots();

    void NextRound();
    
    void StartRound();

    void UpdateRoundTime();

    void DecreaseTime();

    void ResetPlayers();

    void ResetOnePLayer(AController* Controller);

    void DistributeByTeams();
    
    FLinearColor DefineTeamColorByID(int32 ID);

    void SetPlayerTeamColor(AController* Controller);

    void LogTempInfo();

    void ClearLevel();

    void FinishGame();

    void ChangeMatchState(const EMatchState& NewState);

    void WaitForStart();
};
