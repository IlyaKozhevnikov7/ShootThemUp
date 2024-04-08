// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere)
	int32 Damage;

	UPROPERTY(EditAnywhere)
	float Radius;

	UPROPERTY(EditAnywhere)
	FColor Color;

	UPROPERTY(EditAnywhere)
	bool bDoFullDamage;

    UPROPERTY()
	USceneComponent* SceneComponent;

protected:	

	ASTUDevDamageActor();

public:	

	virtual void Tick(float DeltaTime) override;

};
