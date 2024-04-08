// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "STUUIInitializable.generated.h"

UINTERFACE(MinimalAPI)
class USTUUIInitializable : public UInterface
{
	GENERATED_BODY()
};

class SHOOTTHEMUP_API ISTUUIInitializable
{
	GENERATED_BODY()

public:

	virtual void InitializeUI() const { }

};
