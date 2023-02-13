// created by s-malchenko

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoWidget.generated.h"

/**
 *
 */
UCLASS()
class UEROADMAP_API UAmmoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void SetClipAmmo(int32 Ammo);

	UFUNCTION(BlueprintNativeEvent)
	void SetInventoryAmmo(int32 Ammo);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	int32 ClipAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	int32 InventoryAmmo = 0;
};
