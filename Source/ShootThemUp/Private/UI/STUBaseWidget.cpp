// Shoot Them Up Yata. All Rights Reserved.

#include "STUBaseWidget.h"

void USTUBaseWidget::Enable()
{
    if (DisplayAnim)
    {
        PlayAnimationForward(DisplayAnim);   
    }
}

void USTUBaseWidget::Disable()
{
    if (HideAnim)
    {
        PlayAnimationForward(HideAnim);   
    }
}