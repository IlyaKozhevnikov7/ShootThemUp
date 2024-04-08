// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;
class ASTUBaseCharacter;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	UStaticMeshComponent* Mesh;

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundCue* TakingAudio;
    
	UPROPERTY(EditAnywhere, Category = "Pickup", meta = (ClampMin = "1"))
	float RespawnTime;

    bool bIsActive;
    
	static float RotationSpeed;
	
	static float Amplitude;
	
	static float Frequency;

	FVector MeshInitialPosition;

protected:

	ASTUBasePickup();

	virtual void Tick(float DeltaSeconds) override;

	virtual bool GivePickupTo(ASTUBaseCharacter* Character) { return false; }

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:

    bool IsActive() const { return bIsActive; }

private: 

	void Respawn();
    
};
