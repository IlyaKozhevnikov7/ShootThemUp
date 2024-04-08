// Shoot Them Up Yata. All Rights Reserved.

#include "STURespawnComponent.h"
#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(STULogRespawnComponent, All, All);

USTURespawnComponent::USTURespawnComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTURespawnComponent::StartRespawnTimer()
{    
    if (!GetWorld()) return;
    
    const auto GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
    if (!GameMode) return;

    RespawnLeftTime = GameMode->GetGameData().RespawnTime;
    
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerTickHandle, this, &USTURespawnComponent::RespawnTimerTick, 1.f, true, 0);
}

void USTURespawnComponent::RespawnRequest()
{
    if (!GetWorld() || !GetOwner()) return;
    const auto GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();

    if (!GameMode) return;
    
    GameMode->RespawnPlayer(GetOwner<AController>());
}

void USTURespawnComponent::RespawnTimerTick()
{
    OnRespawnTimerTick.Broadcast(RespawnLeftTime);
    
    if (--RespawnLeftTime == -1)
    {
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerTickHandle);
        RespawnRequest();
    }
}

