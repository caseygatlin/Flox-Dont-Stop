// Fill out your copyright notice in the Description page of Project Settings.


#include "FullFunctionCharacter.h"

// Sets default values
AFullFunctionCharacter::AFullFunctionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFullFunctionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFullFunctionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFullFunctionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

