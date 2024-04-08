// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponFXComponent.generated.h"

class UNiagaraSystem;
class USoundCue;
class UPointLightComponent;

USTRUCT(BlueprintType)
struct FDecalData
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly)
    UMaterial* Material;

    UPROPERTY(EditDefaultsOnly)
    FVector Size = FVector(10.f);

    UPROPERTY(EditDefaultsOnly, meta = (MinClamp = "0"))
    float LifeTime = 20.f;

    UPROPERTY(EditDefaultsOnly, meta = (MinClamp = "0"))
    float FadeOutTime = 3.f;       
    
};

USTRUCT(BlueprintType)
struct FImpactData
{
    GENERATED_BODY()

public:
    
    UPROPERTY(EditDefaultsOnly)
    UNiagaraSystem* Effect;

    UPROPERTY(EditDefaultsOnly)
    FDecalData DecalData;

    UPROPERTY(EditDefaultsOnly)
    USoundCue* Sound;
};

UCLASS(ClassGroup = "STU", meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Niagara")
	FImpactData DefaultImpactData;

    UPROPERTY(EditDefaultsOnly, Category = "Light")
    UPointLightComponent* ShotLight;
    
    UPROPERTY(EditDefaultsOnly, Category = "Niagara")
    TMap<UPhysicalMaterial*, FImpactData> ImpactDatas;
    
protected:

	USTUWeaponFXComponent();

    virtual void BeginPlay() override;
    
public:

	void PlayImpactFX(const FHitResult& Hit);

};
