// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
    
    GENERATED_BODY()

private:

    UPROPERTY(VisibleAnywhere)
    int32 TeamID;

    UPROPERTY(VisibleAnywhere)
    FLinearColor TeamColor;

    UPROPERTY(VisibleAnywhere)
    int32 KillNum;

    UPROPERTY(VisibleAnywhere)
    int32 DeathNum;

protected:
    
    ASTUPlayerState();
    
public:
    
    int32 GetTeamID() const { return TeamID; }
    
    const FLinearColor& GetTeamColor() const { return TeamColor; }

    int32 GetKills() const { return KillNum; }

    int32 GetDeaths() const { return DeathNum; }
    
    void SetTeamID(int32 ID) { TeamID = ID; }

    void SetTeamColor(FLinearColor Color) { TeamColor = Color; }
    
    void AddKills() { KillNum++; }
    
    void AddDeath() { DeathNum++; }
};
