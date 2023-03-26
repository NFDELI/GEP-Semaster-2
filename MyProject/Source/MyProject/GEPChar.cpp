// Fill out your copyright notice in the Description page of Project Settings.
#include "GEPChar.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Fireable.h"
#include "Weapon_Base.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AGEPChar::AGEPChar()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(GetCapsuleComponent());
	_Camera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	_Camera->bUsePawnControlRotation = true;

	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachPoint"));
	_WeaponAttachPoint->SetupAttachment(_Camera);
}

void AGEPChar::Init_Implementation()
{
	if(_DefaultWeapon)
	{
		//Spawning Gun for player to use.
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = this;
		TObjectPtr<AActor> spawnedGun = GetWorld()->SpawnActor(_DefaultWeapon, &_WeaponAttachPoint->GetComponentTransform(), spawnParams);
		spawnedGun->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
		if(UKismetSystemLibrary::DoesImplementInterface(spawnedGun, UFireable::StaticClass()))
		{
			//Linking gun so player can shoot it.
			_FireableRef = spawnedGun;
		}
	}
}

void AGEPChar::BeginPlay()
{
	Super::BeginPlay();

	if(_DefaultWeapon)
	{
		//Spawning Gun for player to use.
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = this;
		TObjectPtr<AActor> spawnedGun = GetWorld()->SpawnActor(_DefaultWeapon, &_WeaponAttachPoint->GetComponentTransform(), spawnParams);
		spawnedGun->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
		if(UKismetSystemLibrary::DoesImplementInterface(spawnedGun, UFireable::StaticClass()))
		{
			//Linking gun so player can shoot it.
			_FireableRef = spawnedGun;
		}
	}

	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			//Turning On Controllers.
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void AGEPChar::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AGEPChar::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGEPChar::Shoot()
{
	if(_FireableRef)
	{
		IFireable::Execute_Fire(_FireableRef);
	}
}

void AGEPChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if(UEnhancedInputComponent* EnchancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnchancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnchancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnchancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGEPChar::Move);
		
		EnchancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGEPChar::Look);
		
		EnchancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AGEPChar::Shoot);
	}
}
