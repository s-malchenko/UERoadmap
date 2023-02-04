// created by s-malchenko

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

// Delegate that will be called when stored ammo count has changed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, int32, AmmoLeft, int32, AmmoDelta);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEROADMAP_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Storage)
	int32 AmmoCapacity;

	UPROPERTY(BlueprintAssignable)
	FOnAmmoChanged OnAmmoChanged;

	// Returns count of actually added ammo
	UFUNCTION(BlueprintCallable, Category=Storage)
	int32 AddAmmo(int32 Count);

	// Returns count of actually removed ammo
	UFUNCTION(BlueprintCallable, Category=Storage)
	int32 RemoveAmmo(int32 Count);

	// Returns count of currently stored ammo
	UFUNCTION(BlueprintCallable, Category=Storage)
	int32 GetStoredAmmo() const;

private:
	int32 StoredAmmo = 0;
};
