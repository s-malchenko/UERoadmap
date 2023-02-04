// created by s-malchenko

#include "RoadmapPlayerController.h"

#include "UI/RoadmapHUD.h"

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
        }
    }
}
