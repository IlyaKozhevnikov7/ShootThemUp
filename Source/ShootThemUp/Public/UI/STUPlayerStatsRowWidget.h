// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUPlayerStatsRowWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerStatsRowWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

    UPROPERTY(meta = (BindWidget))
    UTextBlock* NameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsNumTextBlock;
    
    UPROPERTY(meta = (BindWidget))
    UTextBlock* DeathNumTextBlock;
    
    UPROPERTY(meta = (BindWidget))
    UTextBlock* TeamTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* OwnerIdentifier;

public:

    void SetName(const FText& Name);

    void SetKillsNum(const FText& KillsNum);

    void SetDeathNum(const FText& DeathNum);
    
    void SetTeam(const FText& Team);

    void SetAsOwner(bool bIsOwner);
};
