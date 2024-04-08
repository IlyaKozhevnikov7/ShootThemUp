// Shoot Them Up Yata. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseCharacter.h"
#include "STUPlayerCharacter.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerCharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()

private:
    
    UPROPERTY(VisibleAnywhere, Category = "Component")
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, Category = "Component")
    UCameraComponent* Camera;

protected:

    ASTUPlayerCharacter(const FObjectInitializer& ObjectInitializer);
    
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

    void InitializeUI() const;
    
protected:
    
    virtual void OnDead() override;

    virtual void OnRunning() override;

    virtual void OnStopRunning() override;

    virtual void Activate() override;
    
    virtual void Deactivate() override;
    
private:

    void MoveForward(float Value);

    void MoveRight(float Value);    
    
};
