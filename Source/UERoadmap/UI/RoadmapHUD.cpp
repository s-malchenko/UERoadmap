// created by s-malchenko

#include "RoadmapHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void URoadmapHUD::ShowPauseMenu()
{
    if (!PauseMenuWidget.IsValid())
    {
        if (!PauseMenuClass)
        {
            return;
        }

        PauseMenuWidget = CreateWidget(this, PauseMenuClass, TEXT("PauseMenu"));

        if (PauseMenuWidget.IsValid())
        {
            PauseMenuWidget->AddToViewport();
        }
    }

    if (PauseMenuWidget.IsValid())
    {
        PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);
        PauseMenuWidget->SetFocus();
        SetUIInputEnabled(true);
        return;
    }
}

void URoadmapHUD::HidePauseMenu()
{
    if (PauseMenuWidget.IsValid())
    {
        PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
        SetUIInputEnabled(false);
        return;
    }
}

void URoadmapHUD::SetUIInputEnabled(bool bEnabled)
{
    auto* PlayerController = GetOwningPlayer();

    if (PlayerController)
    {
        if (bEnabled)
        {
            PlayerController->SetInputMode(FInputModeGameAndUI());
        }
        else
        {
            PlayerController->SetInputMode(FInputModeGameOnly());
        }

        PlayerController->bShowMouseCursor = bEnabled;
        PlayerController->bEnableClickEvents = bEnabled;
        PlayerController->bEnableMouseOverEvents = bEnabled;
    }
}
