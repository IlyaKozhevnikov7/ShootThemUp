// Shoot Them Up Yata. All Rights Reserved.

#include "STUWaitForStartWidget.h"
#include "STUGameModeBase.h"
#include "Components/TextBlock.h"

DEFINE_LOG_CATEGORY_STATIC(STULogWaitForStartWidget, All, All);

void USTUWaitForStartWidget::Enable()
{
    SetVisibility(ESlateVisibility::HitTestInvisible);
    
    if (const auto GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>())
    {
        UE_LOG(STULogWaitForStartWidget, Display, TEXT("WaitForStartWidget::Enable"));
        GameMode->OnUpdateTimer.AddDynamic(this, &USTUWaitForStartWidget::OnUpdataTimer);
    }
}

void USTUWaitForStartWidget::Disable()
{
    SetVisibility(ESlateVisibility::Collapsed);
    
    if (const auto GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>())
    {
        UE_LOG(STULogWaitForStartWidget, Display, TEXT("WaitForStartWidget::Disable"));
        GameMode->OnUpdateTimer.RemoveDynamic(this, &USTUWaitForStartWidget::OnUpdataTimer);
    }
}

void USTUWaitForStartWidget::OnUpdataTimer(const int32& NewTime)
{
    if (Timer)
    {
        UE_LOG(STULogWaitForStartWidget, Display, TEXT("OnUpdataTimer"));
        Timer->SetText(ConvertToValid(NewTime));
        PlayAnimationForward(CountdownAnim);
    }
}

const FText USTUWaitForStartWidget::ConvertToValid(const int32& NewTime)
{
    return FText::FromString(FString::FromInt(NewTime));
}


