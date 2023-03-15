// created by s-malchenko

#include "RoadmapPlayerController.h"

#include "EnhancedInputComponent.h"
#include "RoadmapCheatManager.h"
#include "UI/RoadmapHUD.h"


ARoadmapPlayerController::ARoadmapPlayerController(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
    CheatClass = URoadmapCheatManager::StaticClass();
}

URoadmapHUD *ARoadmapPlayerController::GetHUDWidget() const
{
    return HUDWidget;
}

void ARoadmapPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (HUDWidgetClass)
    {
        HUDWidget = CreateWidget<URoadmapHUD>(this, HUDWidgetClass, TEXT("HUD"));

        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
            HUDWidget->SetUIInputEnabled(false);
        }
    }
}

void ARoadmapPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (!InputComponent)
    {
        return;
    }

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(TogglePauseAction, ETriggerEvent::Triggered, this, &ARoadmapPlayerController::ToggleGamePause);
	}
}

void ARoadmapPlayerController::ToggleGamePause()
{
    const bool bIsPaused = !IsPaused();
    SetPause(bIsPaused);

    if (HUDWidget)
    {
        bIsPaused ? HUDWidget->ShowPauseMenu() : HUDWidget->HidePauseMenu();
    }
}
