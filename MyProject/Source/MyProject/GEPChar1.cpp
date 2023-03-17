// Fill out your copyright notice in the Description page of Project Settings.


#include "GEPChar1.h"

// Sets default values
AGEPChar1::AGEPChar1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGEPChar1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGEPChar1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGEPChar1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

