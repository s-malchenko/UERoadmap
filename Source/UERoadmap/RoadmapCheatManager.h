// created by s-malchenko

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "RoadmapCheatManager.generated.h"

/**
 * Cheat manager for the game
 */
UCLASS(Within=RoadmapPlayerController)
class UEROADMAP_API URoadmapCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	UFUNCTION(exec)
	void AddAmmo(int32 Count = 100);
};
