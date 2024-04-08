// Shoot Them Up Yata. All Rights Reserved.

#include "STUDevDamageActor.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ASTUDevDamageActor::ASTUDevDamageActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 1;
	Radius = 500.f;
	Color = FColor::Red;
	bDoFullDamage = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root Component");
	SetRootComponent(SceneComponent);
}

void ASTUDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 50, Color);
	UGameplayStatics::ApplyRadialDamage(
	    GetWorld(),
	    Damage,
	    GetActorLocation(),
	    Radius,
	    nullptr,
	    {},
	    this,
	    nullptr,
	    bDoFullDamage,
	    ECollisionChannel::ECC_WorldStatic);
}


