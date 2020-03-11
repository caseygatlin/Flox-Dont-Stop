// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gamecode/DetachedCamera.h"
#include "Public/GamecodeHelpers.h"
#include "Public/Gamecode/Flox.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
ADetachedCamera::ADetachedCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));



}

// Called when the game starts or when spawned
void ADetachedCamera::BeginPlay()
{
	Super::BeginPlay();
	
    //if (!IsValid(Flox))
    //{
    //    if (!UGamecodeHelpers::GetFirstActorOfClass<AFlox>(Flox))
    //    {
    //        UGamecodeHelpers::DebugPrintScreen(FString("Failed to find Flox player character in the current level."));
    //    }
    //}

}

// Called every frame
void ADetachedCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

