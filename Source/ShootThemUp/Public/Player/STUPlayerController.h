// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUPlayerController.generated.h"

enum class EMatchState : uint8;
class USTURespawnComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

    UPROPERTY(VisibleAnywhere, Category = "Component")
    USTURespawnComponent* RespawnComponent;
    
protected:

    ASTUPlayerController();

    virtual void BeginPlay() override;
    
    virtual void SetupInputComponent() override;
    
public:

    USTURespawnComponent* GetRespawnComponent() const { return RespawnComponent; }
    
    virtual void OnPossess(APawn* InPawn) override;

private:

    void OnPause();

    void OnMute();
    
    void OnMatchStateChanged(const EMatchState& NewState);
    
};
