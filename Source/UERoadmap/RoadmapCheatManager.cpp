// created by s-malchenko


#include "RoadmapCheatManager.h"
#include "InventoryComponent.h"

void URoadmapCheatManager::AddAmmo(int32 Count)
{
    APawn* MyPawn = GetPlayerController()->GetPawn();

    if (UInventoryComponent* Inventory = MyPawn->FindComponentByClass<UInventoryComponent>())
    {
        Inventory->AddAmmo(Count);
    }
}
