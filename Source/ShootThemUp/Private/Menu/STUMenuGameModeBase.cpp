// Shoot Them Up Yata. All Rights Reserved.

#include "STUMenuGameModeBase.h"
#include "STUMenuHUD.h"
#include "STUMenuPlayerController.h"

ASTUMenuGameModeBase::ASTUMenuGameModeBase()
{
    PlayerControllerClass = ASTUMenuPlayerController::StaticClass();
    HUDClass = ASTUMenuHUD::StaticClass();
}
