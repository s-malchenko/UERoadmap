// created by s-malchenko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RoadmapPlayerController.generated.h"

/**
 * Player controller
 */
UCLASS()
class UEROADMAP_API ARoadmapPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ARoadmapPlayerController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=UI)
	TSubclassOf<class URoadmapHUD> HUDWidgetClass;

	UFUNCTION(BlueprintPure)
	URoadmapHUD* GetHUDWidget() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	class UInputAction* TogglePauseAction;

	UFUNCTION(BlueprintCallable)
	void ToggleGamePause();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	URoadmapHUD* HUDWidget = nullptr;
};
