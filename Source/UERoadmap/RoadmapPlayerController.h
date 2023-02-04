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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class URoadmapHUD> HUDWidgetClass;

	UFUNCTION(BlueprintPure)
	URoadmapHUD* GetHUDWidget() const;

protected:
	virtual void BeginPlay() override;

	URoadmapHUD* HUDWidget = nullptr;
};
