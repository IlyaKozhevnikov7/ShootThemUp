// Shoot Them Up Yata. All Rights Reserved.

#include "STUAnimNotify.h"

void USTUAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    //UE_LOG(LogTemp, Display, TEXT("Notify"));
	OnNotify.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}