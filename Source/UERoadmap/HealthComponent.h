// created by s-malchenko

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// Delegate that will be called when actual damage is taken
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageTaken);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEROADMAP_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100;

	UFUNCTION(BlueprintPure)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewHealth);

	UPROPERTY(BlueprintAssignable)
	FOnDamageTaken OnDamageTaken;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	float Health;
};
