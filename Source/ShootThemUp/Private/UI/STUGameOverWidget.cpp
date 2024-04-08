// Shoot Them Up Yata. All Rights Reserved.

#include "STUGameOverWidget.h"
#include "EngineUtils.h"
#include "STUGameInstance.h"
#include "STUGameModeBase.h"
#include "STUPlayerState.h"
#include "STUPlayerStatsRowWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

void USTUGameOverWidget::NativeOnInitialized()
{
    if (GetWorld() && GetWorld()->GetAuthGameMode<ASTUGameModeBase>())
    {
        GetWorld()->GetAuthGameMode<ASTUGameModeBase>()->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);   
    }

    if (PlayAgainButton)
    {
        PlayAgainButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnClickedPlayAgainButton);
    }

    if (MenuButton)
    {
        MenuButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnClickedMenuButton);
    }
    
    Super::NativeOnInitialized();
}

void USTUGameOverWidget::Enable()
{
    if (DisplaySound)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), DisplaySound);
    }
    
    Super::Enable();
}

void USTUGameOverWidget::OnMatchStateChanged(const EMatchState& NewState)
{
    if (NewState != EMatchState::GameOver) return;

    UpdatePlayerStatistics();
}

void USTUGameOverWidget::UpdatePlayerStatistics()
{
    if (!GetWorld() || !PlayerStatistics) return;

    PlayerStatistics->ClearChildren();
    
    for (const auto Player : TActorRange<AController>(GetWorld()))
    {
        if (!Player) continue;

        const auto PlayerState = Player->GetPlayerState<ASTUPlayerState>();
        if (!PlayerState) continue;
        
        const auto NewRow = CreateWidget<USTUPlayerStatsRowWidget>(GetWorld(), PlayerStatsRowClass);
        if (!NewRow) continue;
        
        NewRow->SetKillsNum(FText::FromString(FString::FromInt(PlayerState->GetKills())));
        NewRow->SetDeathNum(FText::FromString(FString::FromInt(PlayerState->GetDeaths())));
        NewRow->SetTeam(FText::FromString(FString::FromInt(PlayerState->GetTeamID())));

        if (!Player->IsPlayerController())
        {
            NewRow->SetAsOwner(false);   
            NewRow->SetName(FText::FromString("BOT"));
        }
        else
        {
            NewRow->SetAsOwner(Player->GetName() == GetOwningPlayer()->GetName());
            //NewRow->SetName(FText::FromString(Player->GetName()));
            NewRow->SetName(FText::FromString("Player"));
        } 
        
        PlayerStatistics->AddChild(NewRow);
    }
}

void USTUGameOverWidget::OnClickedPlayAgainButton()
{
    if (!GetWorld()) return;
    
    UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)));
}

void USTUGameOverWidget::OnClickedMenuButton()
{
    if (GetWorld())
    {
        const auto MenuName = GetWorld()->GetGameInstance<USTUGameInstance>()->GetMenuName();
        UGameplayStatics::OpenLevel(this, MenuName);
    }
}
