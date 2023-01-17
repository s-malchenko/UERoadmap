// created by s-malchenko

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEROADMAP_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Storage)
	int32 AmmoCapacity;

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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
