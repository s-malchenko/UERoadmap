// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_PickUpComponent.h"
#include "Kismet/GameplayStatics.h"

void UTP_PickUpComponent::Disable()
{
	// Unregister from the Overlap Event so it is no longer triggered
	OnComponentBeginOverlap.RemoveAll(this);
}

void UTP_PickUpComponent::PlayPickUpSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, PickUpSound, GetOwner()->GetActorLocation());
}

UTP_PickUpComponent::UTP_PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UTP_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
}

void UTP_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AUERoadmapCharacter* Character = Cast<AUERoadmapCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		if (bShouldPlaySound && PickUpSound)
		{
			PlayPickUpSound();
		}

		if (bDisableOnPickUp)
		{
			Disable();
		}
	}
}
