#include "GEPChar.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

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

void AGEPChar::BeginPlay()
{
	Super::BeginPlay();
}

void AGEPChar::Move(const FInputActionValue& Value)
{
	FVector2d MovementVector = Value.Get<FVector2d>();

	if(Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AGEPChar::Look(const FInputActionValue& Value)
{
	FVector2d LookAxisVector = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGEPChar::Shoot()
{
}

void AGEPChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGEPChar::Move);
		
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGEPChar::Look);
		
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AGEPChar::Shoot);
	}

}
