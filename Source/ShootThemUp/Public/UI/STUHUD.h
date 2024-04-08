// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUHUD.generated.h"

enum class EMatchState : uint8;
class USTUPlayerHUD;
class USTUBaseWidget;

UCLASS()
class SHOOTTHEMUP_API ASTUHUD : public AHUD
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USTUBaseWidget> PlayerWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<USTUBaseWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<USTUBaseWidget> WaitForStartWidgetClass;
    
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<USTUBaseWidget> GameOverWidgetClass;
    
    UPROPERTY()
    USTUBaseWidget* CurrentWidget;

    TMap<EMatchState, USTUBaseWidget*> GameWidgets;

protected:
    
	virtual void BeginPlay() override;
    
private:

    void OnMatchStateChanged(const EMatchState& NewState);

    void InitializeWidgets();
};


