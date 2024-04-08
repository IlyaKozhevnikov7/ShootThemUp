// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUWaitForStartWidget.generated.h"

class UTextBlock;

UCLASS()
class SHOOTTHEMUP_API USTUWaitForStartWidget : public USTUBaseWidget
{
	GENERATED_BODY()

protected:

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Timer;
    
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* CountdownAnim;
    
public:

    virtual void Enable() override;
    
    virtual void Disable() override;

private:

    UFUNCTION()
    void OnUpdataTimer(const int32& NewTime);

    const FText ConvertToValid(const int32& NewTime);
};
