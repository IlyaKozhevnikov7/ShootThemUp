// Shoot Them Up Yata. All Rights Reserved.

#include "STUAIController.h"
#include "STUAICharacter.h"
#include "STUAIPerceptionComponent.h"
#include "STUHealthComponent.h"
#include "STURespawnComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(STULogAIController, All, All);

ASTUAIController::ASTUAIController()
{
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.bCanEverTick = true;
    bWantsPlayerState = true;

    //STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("AI Perception Component");

    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("Respawn Component");
    
    EnemyActorKeyName = "Enemy";
}

void ASTUAIController::BeginPlay()
{
    Super::BeginPlay();
    
    STUAIPerceptionComponent = FindComponentByClass<USTUAIPerceptionComponent>();
    SetPerceptionComponent(*STUAIPerceptionComponent);
}

void ASTUAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    SetFocus(GetNearestActor());
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    
    if (const auto STUCharacter = Cast<ASTUAICharacter>(InPawn))
    {
        RunBehaviorTree(STUCharacter->GetBehaviorTree());
    }

    if (const auto HealthComponent = InPawn->FindComponentByClass<USTUHealthComponent>())
    {
        HealthComponent->OnDeath.AddDynamic(RespawnComponent, &USTURespawnComponent::StartRespawnTimer);
    }
}

AActor* ASTUAIController::GetNearestActor() const
{
    if (GetBlackboardComponent())
    {
        return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(EnemyActorKeyName));
    }

    return nullptr;
}
