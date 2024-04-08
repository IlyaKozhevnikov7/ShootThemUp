// Shoot Them Up Yata. All Rights Reserved.

#include "AI/EQS/EnvQueryTest_PickupIsActive.h"
#include "STUBasePickup.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"

UEnvQueryTest_PickupIsActive::UEnvQueryTest_PickupIsActive(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickupIsActive::RunTest(FEnvQueryInstance& QueryInstance) const
{
    UObject* DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);

    const bool bWantsBeTakeble = BoolValue.GetValue();
    
    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const auto Pickup = Cast<ASTUBasePickup>(ItemActor);

        if (!Pickup) continue;

        It.SetScore(TestPurpose, FilterType, Pickup->IsActive(), bWantsBeTakeble);
    }
}
