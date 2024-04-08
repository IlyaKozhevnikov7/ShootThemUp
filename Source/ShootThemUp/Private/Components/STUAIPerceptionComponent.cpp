// Shoot Them Up Yata. All Rights Reserved.

#include "STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUHealthComponent.h"
#include "STUPlayerState.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Sight.h"

void USTUAIPerceptionComponent::BeginPlay()
{
    Super::BeginPlay();

    Controller = Cast<AAIController>(GetOwner());
}

AActor* USTUAIPerceptionComponent::GetNearestActor() const
{
    TArray<AActor*> SeenActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), SeenActors);

    if (SeenActors.Num() == 0)
    {
        GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), SeenActors);
        if (SeenActors.Num() == 0) return nullptr;
    }
    
    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;
    
    AActor* BestActor = nullptr;
    float BestDistance = FLT_MAX;
    
    for (const auto& SeenActor : SeenActors)
    {
        const auto HealthComponent = SeenActor->FindComponentByClass<USTUHealthComponent>();

        if (HealthComponent && !HealthComponent->IsDead() && IsEnemy(Cast<APawn>(SeenActor)->GetController()))
        {
            const float Distance = (SeenActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (Distance < BestDistance)
            {
                BestDistance = Distance;
                BestActor = SeenActor;
            }
        }
    }
    
    return BestActor;
}

bool USTUAIPerceptionComponent::IsEnemy(AController* PercieveController) const
{
    if (!PercieveController) return false;

    const auto PercieveState = PercieveController->GetPlayerState<ASTUPlayerState>();
    if (!PercieveState) return false;
    
    const auto OwnState = Controller->GetPlayerState<ASTUPlayerState>();
    if (!OwnState) return false;

    return OwnState->GetTeamID() != PercieveState->GetTeamID();
}
