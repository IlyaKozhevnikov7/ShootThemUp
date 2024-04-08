// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupIsActive.generated.h"

UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_PickupIsActive : public UEnvQueryTest
{
	GENERATED_BODY()

protected:
    
    UEnvQueryTest_PickupIsActive(const FObjectInitializer& ObjectInitializer);
    
public:
    
    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
    
};
