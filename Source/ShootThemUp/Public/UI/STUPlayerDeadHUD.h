// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUPlayerDeadHUD.generated.h"

class UCanvasPanel;
class UTextBlock;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerDeadHUD : public USTUBaseWidget
{
	GENERATED_BODY()

protected:

    UPROPERTY(meta = (BindWidget))
    UCanvasPanel* MainCanvasPanel;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* RespawnTime;
    
public:

    virtual bool Initialize() override;
    
    virtual void NativeOnInitialized() override;
    
    UFUNCTION()
    void OnDeath();

private:

    void OnRespawnTimerTick(const int32& LeftTime);
    
};
