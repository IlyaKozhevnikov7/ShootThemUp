// Shoot Them Up Yata. All Rights Reserved.

#include "STUHealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Curves/CurveLinearColor.h"

void USTUHealthBarWidget::ChangeHealth(const float HealthPercent)
{
    if (!HealthBar) return;

    HealthBar->SetPercent(HealthPercent);    
    HealthBar->SetFillColorAndOpacity(Color->GetLinearColorValue(HealthPercent));
}
