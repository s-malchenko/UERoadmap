// Copyright Epic Games, Inc. All Rights Reserved.

#include "UERoadmapCharacter.h"

#include "InventoryComponent.h"
#include "UERoadmapProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "RoadmapPlayerController.h"
#include "UI/RoadmapHUD.h"
#include "UI/AmmoWidget.h"

//////////////////////////////////////////////////////////////////////////
// AUERoadmapCharacter

void AUERoadmapCharacter::InventoryAmmoDelegate(int32 AmmoLeft, int32 AmmoDelta)
{
	if (!PlayerController)
	{
		return;
	}

	URoadmapHUD* Hud = PlayerController->GetHUDWidget();

	if (!Hud || !Hud->AmmoWidget)
	{
		return;
	}

	Hud->AmmoWidget->SetInventoryAmmo(AmmoLeft);
}

void AUERoadmapCharacter::ClipAmmoDelegate(int32 ClipAmmo)
{
	if (!PlayerController)
	{
		return;
	}

	URoadmapHUD* Hud = PlayerController->GetHUDWidget();

	if (!Hud || !Hud->AmmoWidget)
	{
		return;
	}

	Hud->AmmoWidget->SetClipAmmo(ClipAmmo);
}

void AUERoadmapCharacter::RefreshReticleWidget()
{
	if (PlayerController)
	{
		if (URoadmapHUD* HudWidget = PlayerController->GetHUDWidget())
		{
			if (HudWidget->ReticleWidget)
			{
				HudWidget->ReticleWidget->SetVisibility(bHasRifle ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
			}
		}
	}
}

AUERoadmapCharacter::AUERoadmapCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void AUERoadmapCharacter::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();

	PlayerController = Cast<ARoadmapPlayerController>(Controller);

	//Add Input Mapping Context
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (InventoryComponent)
	{
		if (InventoryCapacityOverride >=0)
		{
			InventoryComponent->AmmoCapacity = InventoryCapacityOverride;
		}

		InventoryComponent->OnAmmoChanged.AddDynamic(this, &AUERoadmapCharacter::InventoryAmmoDelegate);
	}

	RefreshReticleWidget();
}

void AUERoadmapCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (InventoryComponentClass)
	{
		InventoryComponent = NewObject<UInventoryComponent>(this, InventoryComponentClass, TEXT("Inventory"));
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AUERoadmapCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUERoadmapCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUERoadmapCharacter::Look);
	}
}


void AUERoadmapCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AUERoadmapCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AUERoadmapCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
	RefreshReticleWidget();
}

bool AUERoadmapCharacter::GetHasRifle()
{
	return bHasRifle;
}