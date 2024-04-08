// Shoot Them Up Yata. All Rights Reserved.

#include "STUHUD.h"
#include "STUGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUD.h"

DEFINE_LOG_CATEGORY_STATIC(STULogHUD, All, All);

void ASTUHUD::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(STULogHUD, Display, TEXT("HUD BeginPLay"));

    InitializeWidgets();
        
    if (GetWorld())
    {
        const auto GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();

        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASTUHUD::OnMatchStateChanged);
        }
    }
}

void ASTUHUD::OnMatchStateChanged(const EMatchState& NewState)
{
    UE_LOG(STULogHUD, Display, TEXT("OnMatchStateChanged HUD %s"), *GameWidgets[NewState]->GetName());
    
    if (GameWidgets[NewState])
    {
        GameWidgets[NewState]->Enable();
        
        if (CurrentWidget)
        {
            CurrentWidget->Disable();
        }

        CurrentWidget = GameWidgets[NewState];
    }    
}

void ASTUHUD::InitializeWidgets()
{
    const auto PlayerHud = CreateWidget<USTUBaseWidget>(GetWorld(), PlayerWidgetClass);
    
    GameWidgets.Add(EMatchState::WaitingForStart, CreateWidget<USTUBaseWidget>(GetWorld(), WaitForStartWidgetClass));
    GameWidgets.Add(EMatchState::InProgress, PlayerHud);
    GameWidgets.Add(EMatchState::Pause, CreateWidget<USTUBaseWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EMatchState::GameOver, CreateWidget<USTUBaseWidget>(GetWorld(), GameOverWidgetClass));

    for (const auto Widget : GameWidgets)
    {
        if (Widget.Value)
        {
            Widget.Value->AddToViewport();
            Widget.Value->SetVisibility(ESlateVisibility::Collapsed);
        }
    }

    // TODO перенести в USTUPlayerHUD
    GetOwningPlayerController()->GetOnNewPawnNotifier().AddUObject(Cast<USTUPlayerHUD>(PlayerHud), &USTUPlayerHUD::Init);
}
