// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRespawnTimerTickSignature, const int32&);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTURespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:

    FOnRespawnTimerTickSignature OnRespawnTimerTick;
    
private:

    int32 RespawnLeftTime;
    
    FTimerHandle RespawnTimerHandle;

    FTimerHandle RespawnTimerTickHandle;
    
protected:	

	USTURespawnComponent();

public:

    UFUNCTION()
    void StartRespawnTimer();

private:
    
    void RespawnRequest();

    // Метод для UI
    void RespawnTimerTick();
};
