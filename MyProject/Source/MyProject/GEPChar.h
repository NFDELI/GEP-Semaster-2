// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "GEPChar.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AWeapon_Base;

UCLASS(Abstract)
class MYPROJECT_API AGEPChar : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> _Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> _WeaponAttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TexCreate_InputAttachmentRead, meta=(AllowPrivateAccess="true"))
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TexCreate_InputAttachmentRead, meta=(AllowPrivateAccess="true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TexCreate_InputAttachmentRead, meta=(AllowPrivateAccess="true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TexCreate_InputAttachmentRead, meta=(AllowPrivateAccess="true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TexCreate_InputAttachmentRead, meta=(AllowPrivateAccess="true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TexCreate_InputAttachmentRead, meta=(AllowPrivateAccess="true"))
	UInputAction* ReloadAction;
public:
	// Sets default values for this character's properties
	AGEPChar();

	UFUNCTION(BlueprintNativeEvent)
	void Init();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> _DefaultWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> _FireableRef;

	virtual void BeginPlay() override;
	
	void Move (const FInputActionValue& Value);

	void Look (const FInputActionValue& Value);

	void Shoot();

	void Reload();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
