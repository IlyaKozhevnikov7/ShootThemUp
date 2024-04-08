// Shoot Them Up Yata. All Rights Reserved.

#include "STUCameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

USTUCameraComponent::USTUCameraComponent()
{
    ShapeComponent = CreateDefaultSubobject<USphereComponent>("Shape Component");
    ShapeComponent->InitSphereRadius(5.f);
    ShapeComponent->SetupAttachment(this);
    //ShapeComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    
    ShapeComponent->OnComponentBeginOverlap.AddDynamic(this, &USTUCameraComponent::OnBeginOverlap);
    ShapeComponent->OnComponentEndOverlap.AddDynamic(this, &USTUCameraComponent::OnEndOverlap);
}

void USTUCameraComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (Cast<UPrimitiveComponent>(GetOwner<ACharacter>()->GetCapsuleComponent()) == OtherComp)
    {
        HideOwner(true);
    }
}

void USTUCameraComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
    if (Cast<UPrimitiveComponent>(GetOwner<ACharacter>()->GetCapsuleComponent()) == OtherComp)
    {
        HideOwner(false);
    }
}

void USTUCameraComponent::HideOwner(const bool bHide) const
{
    TArray<USceneComponent*> Children;
    const auto Mesh = GetOwner<ACharacter>()->GetMesh();

    Mesh->GetChildrenComponents(true, Children);
    Mesh->SetOwnerNoSee(bHide);

    for (const auto Child : Children)
    {
        //Cast<UPrimitiveComponent>(Child)->SetOwnerNoSee(bHide); // TODO не работает (вілетает)
    }
}
