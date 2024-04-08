// Shoot Them Up Yata. All Rights Reserved.

#include "STUBasePickup.h"
#include "Components/SphereComponent.h"
#include "STUBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, Display, Display);

float ASTUBasePickup::RotationSpeed = 0.5f;
float ASTUBasePickup::Amplitude = 15.f;
float ASTUBasePickup::Frequency = 3.f;

ASTUBasePickup::ASTUBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Collision = CreateDefaultSubobject<USphereComponent>("Collison");
	Collision->InitSphereRadius(50.f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->AddRelativeLocation(FVector::ZeroVector);
    
	RespawnTime = 5.f;
    bIsActive = true;
	MeshInitialPosition = Mesh->GetRelativeLocation();
}

void ASTUBasePickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
    
	Mesh->AddWorldRotation(FRotator(0.f, RotationSpeed, 0.f));

	FVector MeshNewLocation = Mesh->GetRelativeLocation();
	MeshNewLocation.Z = MeshInitialPosition.Z + Amplitude * FMath::Sin(Frequency * GetWorld()->GetTimeSeconds());
	Mesh->SetRelativeLocation(MeshNewLocation);
    
    //UE_LOG(LogBasePickup, Display, TEXT("%f"), Frequency * GetWorld()->GetTimeSeconds());
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (GivePickupTo(Cast<ASTUBaseCharacter>(OtherActor)))
	{
		GetRootComponent()->SetVisibility(false, true);
		Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

		FTimerHandle RespawnTimerHandle;
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);
	    bIsActive = false;
	    
        if (TakingAudio) UGameplayStatics::PlaySoundAtLocation(GetWorld(), TakingAudio, GetActorLocation());
	}
}

void ASTUBasePickup::Respawn()
{
	GetRootComponent()->SetVisibility(true, true);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    bIsActive = true;
}
