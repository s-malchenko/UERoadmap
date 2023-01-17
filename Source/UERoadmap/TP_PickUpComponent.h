// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "UERoadmapCharacter.h"
#include "TP_PickUpComponent.generated.h"

// Declaration of the delegate that will be called when someone picks this up
// The character picking this up is the parameter sent with the notification
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AUERoadmapCharacter*, PickUpCharacter);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UEROADMAP_API UTP_PickUpComponent : public USphereComponent
{
	GENERATED_BODY()

public:

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPickUp OnPickUp;

	/** Auto disable on first pickup */
	UPROPERTY(EditAnywhere, Category="Interaction")
	bool bDisableOnPickUp = true;

	/** Play pick up sound automatically */
	UPROPERTY(EditAnywhere, Category="Interaction")
	bool bShouldPlaySound = true;

	/** Sound to play while attempting to fire empty weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	USoundBase* PickUpSound;

	/** Disable this component*/
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void Disable();

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void PlayPickUpSound();

	UTP_PickUpComponent();
protected:

	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** Code for when something overlaps this component */
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};