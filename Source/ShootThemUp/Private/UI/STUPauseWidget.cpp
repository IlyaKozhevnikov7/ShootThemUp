// Shoot Them Up Yata. All Rights Reserved.

#include "STUPauseWidget.h"
#include "STUGameInstance.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

bool USTUPauseWidget::Initialize()
{
    const bool bInitializeResult = Super::Initialize();

    if (ContinueButton)
    {
        ContinueButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClickedContinueButton);   
    }
    
    if (MenuButton)
    {
        MenuButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClickedMenuButton);   
    }
    
    return bInitializeResult;
}

void USTUPauseWidget::Enable()
{
    if (DisplaySound)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), DisplaySound);
    }
    
    Super::Enable();
}

void USTUPauseWidget::OnClickedContinueButton()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    
    GetWorld()->GetAuthGameMode()->ClearPause();
}

void USTUPauseWidget::OnClickedMenuButton()
{
    if (GetWorld())
    {
        const auto MenuName = GetWorld()->GetGameInstance<USTUGameInstance>()->GetMenuName();
        UGameplayStatics::OpenLevel(this, MenuName);
    }
}