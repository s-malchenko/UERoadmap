// created by s-malchenko


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;

	auto* Owner = GetOwner();

	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}

}

void UHealthComponent::TakeDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *InstigatedBy, AActor *DamageCauser)
{
	if (Damage <= 0)
	{
		return;
	}


	Health -= Damage;
}

float UHealthComponent::GetHealth() const
{
	return Health;
}