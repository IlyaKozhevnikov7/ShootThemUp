// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUGameInstance.h" // for FLevelItemData
#include "Blueprint/UserWidget.h"
#include "STULevelItemWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;

UCLASS(Blueprintable)
class SHOOTTHEMUP_API USTULevelItemWidget : public UUserWidget
{
	GENERATED_BODY()
    
protected:
    
    UPROPERTY(meta = (BindWidget))
    UButton* SelectedButton;
    
    UPROPERTY(meta = (BindWidget))
    UImage* Icon;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DisplayName;

private:    
    
    FName LevelName;

    static USTULevelItemWidget* SelectedItem; // TODO запоминать только имя уровня, а не все данные
    
public:

    UFUNCTION(BlueprintCallable)
    bool IsSelected() const { return SelectedItem == this; }
    
    virtual void NativeOnInitialized() override;
    
    void SetData(const FLevelItemData& NewData);
    
    static FName GetSelectedLevelName();

    static void ClearSelectedItem();

protected:

    UFUNCTION(BlueprintImplementableEvent)
    void OnSelected();

    UFUNCTION(BlueprintImplementableEvent)
    void OnUnSelected();
    
private:
    
    UFUNCTION()
    void OnClickedSelectoedButton();
    
};
