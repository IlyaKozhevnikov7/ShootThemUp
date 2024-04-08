// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUPauseWidget.generated.h"

class UButton;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API USTUPauseWidget : public USTUBaseWidget
{
	GENERATED_BODY()

private:
    
    UPROPERTY(meta = (BindWidget))
    UButton* ContinueButton;

    UPROPERTY(meta = (BindWidget))
    UButton* MenuButton;

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundCue* DisplaySound;
    
public:
    
    virtual bool Initialize() override;

protected:

    virtual void Enable() override;

private:

    UFUNCTION()
    void OnClickedContinueButton();

    UFUNCTION()
    void OnClickedMenuButton();
};
