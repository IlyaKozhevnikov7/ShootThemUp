// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STULevelSelectorWidget.generated.h"

class UHorizontalBox;
class UButton;

UCLASS()
class SHOOTTHEMUP_API USTULevelSelectorWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> LevelItemClass;
    
    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItems;
    
public:

    virtual void NativeOnInitialized() override;
    
private:

    void InitializeLevelItems();

};
