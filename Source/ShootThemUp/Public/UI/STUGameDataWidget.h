// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUGameDataWidget.generated.h"

class UTextBlock;

UCLASS()
class SHOOTTHEMUP_API USTUGameDataWidget : public USTUBaseWidget
{
    GENERATED_BODY()
    
protected:
    
    UPROPERTY(meta = (BindWidget))
    UTextBlock* Timer;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Round;

public:

    virtual void Enable() override;

    virtual void Disable() override;

protected:

    virtual void NativeOnInitialized() override;

private:
    
    UFUNCTION()
    void OnUpdateTimer(const int32& NewTime);

    void OnNewRound(const int32& CurrentRound);

};
