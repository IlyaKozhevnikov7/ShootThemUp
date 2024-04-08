// Shoot Them Up Yata. All Rights Reserved.

#include "STUMenuWidget.h"
#include "STULevelItemWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void USTUMenuWidget::NativeOnInitialized()
{
    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnClickedQuitGameButton);
    }

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnClickedStartGameButton);
    }
    
    Super::NativeOnInitialized();
}

void USTUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if (Animation == HideAnim)
    {
        UGameplayStatics::OpenLevel(this, USTULevelItemWidget::GetSelectedLevelName());
        USTULevelItemWidget::ClearSelectedItem();
    }
}

void USTUMenuWidget::Disable()
{   
    UGameplayStatics::PlaySound2D(GetWorld(), StarGameSound);
    Super::Disable();
}

void USTUMenuWidget::OnClickedStartGameButton()
{
    if (USTULevelItemWidget::GetSelectedLevelName() != NAME_None)
    {
        Disable();
    }
}

void USTUMenuWidget::OnClickedQuitGameButton()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
