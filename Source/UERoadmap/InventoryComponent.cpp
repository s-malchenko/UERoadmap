// created by s-malchenko

#include "InventoryComponent.h"

#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

int32 UInventoryComponent::AddAmmo(int32 Count)
{
	if (StoredAmmo > AmmoCapacity) {
		return 0;
	}

	Count = FGenericPlatformMath::Min(Count, AmmoCapacity - StoredAmmo);
	StoredAmmo += Count;
    return Count;
}

int32 UInventoryComponent::RemoveAmmo(int32 Count)
{
    Count = FGenericPlatformMath::Min(Count, StoredAmmo);
	StoredAmmo -= Count;
	return Count;
}

int32 UInventoryComponent::GetStoredAmmo() const
{
    return StoredAmmo;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}
