// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUGameInstance.generated.h"

USTRUCT()
struct FLevelItemData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    FName Name;
        
    UPROPERTY(EditDefaultsOnly)
    FName DisplayName;

    UPROPERTY(EditDefaultsOnly)
    UTexture2D* Icon;
};

UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()
    
private:

    UPROPERTY(EditDefaultsOnly)
    FName MenuName;

    UPROPERTY(EditDefaultsOnly)
    TArray<FLevelItemData> LevelItemData;

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundClass* MasterSoundClass;
    
public:

    const FName& GetMenuName() const { return MenuName; }

    USoundClass* GetMasterSoundClass() const { return MasterSoundClass; }
    
    const TArray<FLevelItemData>& GetLevelItemData() const { return LevelItemData; }
    
};
