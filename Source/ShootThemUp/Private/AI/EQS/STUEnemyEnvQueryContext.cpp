// Shoot Them Up Yata. All Rights Reserved.

#include "STUEnemyEnvQueryContext.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

USTUEnemyEnvQueryContext::USTUEnemyEnvQueryContext(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    EnemyActorKeyName = "Enemy";
}

void USTUEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
    const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);

    if (!Blackboard) return;

    const auto ContextActor = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKeyName));

    if (!ContextActor) return;
    
    UEnvQueryItemType_Actor::SetContextHelper(ContextData, ContextActor);
}
