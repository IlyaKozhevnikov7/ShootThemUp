// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUGameOverWidget.generated.h"

enum class EMatchState : uint8;
class UVerticalBox;
class UButton;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public USTUBaseWidget
{
	GENERATED_BODY()

protected:

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatistics;

    UPROPERTY(meta = (BindWidget))
    UButton* PlayAgainButton;
    
    UPROPERTY(meta = (BindWidget))
    UButton* MenuButton;
    
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatsRowClass;

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundCue* DisplaySound;
    
protected:

    virtual void NativeOnInitialized() override;

    virtual void Enable() override;
    
private:

    void OnMatchStateChanged(const EMatchState& NewState);

    void UpdatePlayerStatistics();

    UFUNCTION()
    void OnClickedPlayAgainButton();

    UFUNCTION()
    void OnClickedMenuButton();
};
