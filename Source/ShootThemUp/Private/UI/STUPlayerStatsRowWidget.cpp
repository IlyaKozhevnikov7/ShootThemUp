// Shoot Them Up Yata. All Rights Reserved.

#include "STUPlayerStatsRowWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUPlayerStatsRowWidget::SetName(const FText& Name)
{
    if (NameTextBlock)
    {
        NameTextBlock->SetText(Name);
    }
}

void USTUPlayerStatsRowWidget::SetKillsNum(const FText& KillsNum)
{
    if (KillsNumTextBlock)
    {
        KillsNumTextBlock->SetText(KillsNum);
    }
}

void USTUPlayerStatsRowWidget::SetDeathNum(const FText& DeathNum)
{
    if (DeathNumTextBlock)
    {
        DeathNumTextBlock->SetText(DeathNum);
    }
}

void USTUPlayerStatsRowWidget::SetTeam(const FText& Team)
{
    if (TeamTextBlock)
    {
        TeamTextBlock->SetText(Team);
    }
}

void USTUPlayerStatsRowWidget::SetAsOwner(bool bIsOwner)
{
    if (OwnerIdentifier)
    {
        OwnerIdentifier->SetVisibility(bIsOwner ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
}
