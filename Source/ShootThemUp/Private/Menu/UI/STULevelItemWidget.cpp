// Shoot Them Up Yata. All Rights Reserved.

#include "STULevelItemWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

USTULevelItemWidget* USTULevelItemWidget::SelectedItem = nullptr;

void USTULevelItemWidget::NativeOnInitialized()
{
    // !!! ÍÅ ÒÐÎÃÀÒÜ !!! ÑÒÀÒÈ×ÅÑÊÎÅ ÏÎËÅ ÇÀÍÓËßÅÒÜÑß ÏÐÎ ÐÅÑÒÀÐÒÅ ÌÅÍÞ
    //if (SelectedItem) SelectedItem = nullptr;

    if (SelectedButton)
    {
        SelectedButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnClickedSelectoedButton);
    }

    Super::NativeOnInitialized();
}

void USTULevelItemWidget::SetData(const FLevelItemData& NewData)
{
    if (DisplayName)
    {
        DisplayName->SetText(FText::FromName(NewData.DisplayName));
    }
    
    if (Icon)
    {
        Icon->SetBrushFromTexture(NewData.Icon);
    }

    LevelName = NewData.Name;
}

FName USTULevelItemWidget::GetSelectedLevelName()
{
    return SelectedItem ? SelectedItem->LevelName : NAME_None;
}

void USTULevelItemWidget::ClearSelectedItem()
{
    SelectedItem = nullptr;
}

void USTULevelItemWidget::OnClickedSelectoedButton()
{
    if (SelectedItem != this)
    {
        if (SelectedItem != nullptr)
        {
            SelectedItem->OnUnSelected();
        }
        
        SelectedItem = this;
        OnSelected();
    }
}
