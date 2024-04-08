// Shoot Them Up Yata. All Rights Reserved.

#include "STUPlayerDeadHUD.h"
#include "STUPlayerController.h"
#include "STURespawnComponent.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

bool USTUPlayerDeadHUD::Initialize()
{
    const bool bResult = Super::Initialize();

    const auto Owner = GetOwningPlayer<ASTUPlayerController>();
    if (Owner)
    {
        Owner->GetRespawnComponent()->OnRespawnTimerTick.AddUObject(this, &USTUPlayerDeadHUD::OnRespawnTimerTick);
    }

    return bResult;
}

void USTUPlayerDeadHUD::NativeOnInitialized()
{
    //UE_LOG(LogTemp, Display, TEXT("OnInitialized DeadHUD"));
    MainCanvasPanel->SetVisibility(ESlateVisibility::Collapsed);
    
    Super::NativeOnInitialized();
}

void USTUPlayerDeadHUD::OnRespawnTimerTick(const int32& LeftTime)
{
    RespawnTime->SetText(FText::FromString(FString::FromInt(LeftTime)));
}

void USTUPlayerDeadHUD::OnDeath()
{
    // доделать анимацию
    MainCanvasPanel->SetVisibility(ESlateVisibility::HitTestInvisible);
}

