// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUMenuWidget.generated.h"

class UButton;
class USTULevelSelectorWidget;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public USTUBaseWidget
{
	GENERATED_BODY()

protected:
    
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundCue* StarGameSound;
    
    //UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    //USTULevelSelectorWidget* LevelSelector;
    
private:
    
    FName SelectedLevelName;

public:

    void SetSelectedLevelName(const FName& NewName) { SelectedLevelName = NewName; }
    
protected:

    virtual void NativeOnInitialized() override;

    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

    virtual void Disable() override;
    
private:
    
    UFUNCTION()
    void OnClickedStartGameButton();
    
    UFUNCTION()
    void OnClickedQuitGameButton();
};
