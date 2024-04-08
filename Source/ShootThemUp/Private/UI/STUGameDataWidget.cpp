// Shoot Them Up Yata. All Rights Reserved.

#include "STUGameDataWidget.h"
#include "STUGameModeBase.h"
#include "Components/TextBlock.h"

void USTUGameDataWidget::Enable()
{
    if (const auto GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>())
    {
        GameMode->OnUpdateTimer.AddDynamic(this, &USTUGameDataWidget::OnUpdateTimer);
    }
}

void USTUGameDataWidget::Disable()
{
    if (const auto GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>())
    {
        GameMode->OnUpdateTimer.RemoveDynamic(this, &USTUGameDataWidget::OnUpdateTimer);
    }
}

void USTUGameDataWidget::NativeOnInitialized() 
{
    if (const auto GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>())
    {
        GameMode->OnNewRound.AddUObject(this, &USTUGameDataWidget::OnNewRound);
    }

    Super::NativeOnInitialized();
}

void USTUGameDataWidget::OnNewRound(const int32& CurrentRound)
{
    if (Round)
    {
        if (const auto GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>())
        {            
            const int32 TotalRound = GameMode->GetGameData().RoundsNumber;

            FString RoundText = FString::FromInt(CurrentRound);
            RoundText.AppendChar('/');
            RoundText.Append(FString::FromInt(TotalRound));

            Round->SetText(FText::FromString(RoundText));
        }
    }
}

void USTUGameDataWidget::OnUpdateTimer(const int32& NewTime)
{
    if (Timer)
    {
        const FString NewTimeStr = FTimespan::FromSeconds(NewTime).ToString().Mid(4, 5);
        Timer->SetText(FText::FromString(NewTimeStr));
    }   
}
