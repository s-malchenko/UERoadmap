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

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UUserWidget* ReticleWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseMenuClass;

	UFUNCTION(BlueprintCallable)
	void ShowPauseMenu();

	UFUNCTION(BlueprintCallable)
	void HidePauseMenu();

	void SetUIInputEnabled(bool bEnabled);

private:
	TWeakObjectPtr<UUserWidget> PauseMenuWidget;
};
