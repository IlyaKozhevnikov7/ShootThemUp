// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUBaseWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUBaseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    
    UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
    UWidgetAnimation* DisplayAnim;

    UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
    UWidgetAnimation* HideAnim;

public:

    virtual void Enable();

    virtual void Disable();
    
};
