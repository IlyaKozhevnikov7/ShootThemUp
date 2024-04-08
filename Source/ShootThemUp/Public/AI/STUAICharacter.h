// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseCharacter.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;
class USTUHealthBarWidget;

UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()
    
protected:
    
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UBehaviorTree* BehaviorTree;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UWidgetComponent* HealthBarComponent;

    UPROPERTY()
    USTUHealthBarWidget* HealthBarWidget;
    
protected:

    ASTUAICharacter(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;
    
    virtual void Tick(float DeltaSeconds) override;
    
public:

    UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

protected:

    virtual void OnDead() override;

    virtual void OnHealthChanged(const float& CurrentHealt, const float& HealthDelta) override;
    
};
