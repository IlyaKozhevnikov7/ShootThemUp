// Shoot Them Up Yata. All Rights Reserved.

#include "STUMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASTUMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget(GetWorld(), MenuWidgetClass);

        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
        }
    }
}
