// Shoot Them Up Yata. All Rights Reserved.

#include "STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Sound/SoundCue.h"

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

    ShotLight = CreateDefaultSubobject<UPointLightComponent>("Shot Light");
}

void USTUWeaponFXComponent::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Display, TEXT("%s"), *GetOwner()->GetName());
    
    //ShotLight->SetupAttachment()
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    auto ImpactData = DefaultImpactData;

    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMaterial = Hit.PhysMaterial.Get();
        if (ImpactDatas.Contains(PhysMaterial))
        {
            ImpactData = ImpactDatas[PhysMaterial];
        }
    }
 
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

    if (auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
                  ImpactData.DecalData.Material,
                  ImpactData.DecalData.Size,
                  Hit.ImpactPoint,
                  Hit.ImpactNormal.Rotation()))
    {
        Decal->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
    }

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.Sound, Hit.ImpactPoint);
}



