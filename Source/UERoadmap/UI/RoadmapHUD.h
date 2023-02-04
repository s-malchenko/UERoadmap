// created by s-malchenko

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoadmapHUD.generated.h"

/**
 * HUD widget
 */
UCLASS()
class UEROADMAP_API URoadmapHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta=(BindWidgetOptional))
	class UAmmoWidget* AmmoWidget;
};
