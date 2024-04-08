// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "STUCameraComponent.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API USTUCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
	
private:

    UPROPERTY(EditDefaultsOnly)
    USphereComponent* ShapeComponent;

protected:

    USTUCameraComponent();

private:

    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void HideOwner(const bool bHide) const;
};
