// Shoot Them Up Yata. All Rights Reserved.

#include "STULevelSelectorWidget.h"
#include "STUGameInstance.h"
#include "STULevelItemWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"

void USTULevelSelectorWidget::NativeOnInitialized()
{    
    InitializeLevelItems();
    
    Super::NativeOnInitialized();
}

void USTULevelSelectorWidget::InitializeLevelItems()
{
    LevelItems->ClearChildren();
    
    if (!LevelItems || !GetWorld()) return;
    const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    
    if (!GameInstance) return;
    if (GameInstance->GetLevelItemData().Num() == 0) return;
    
    for (const auto LevelData : GameInstance->GetLevelItemData())
    {
        const auto NewLevelItem = CreateWidget<USTULevelItemWidget>(GetWorld(), LevelItemClass);
        if (!NewLevelItem) continue;

        NewLevelItem->SetData(LevelData);
        NewLevelItem->SetPadding(FMargin(10.f));
        LevelItems->AddChild(NewLevelItem);
    }
}
