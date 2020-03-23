// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gamecode/DetachedCamera.h"
#include "Public/GamecodeHelpers.h"
#include "Public/Gamecode/Flox.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"


// Sets default values
ADetachedCamera::ADetachedCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    SpringArm->TargetArmLength = DistanceFromPlayer;

    Camera->SetupAttachment(SpringArm);
    SetRootComponent(SpringArm);

    RootComponent->SetWorldRotation(FRotator(0.f, 180.f, 0.f));


}

// Called when the game starts or when spawned
void ADetachedCamera::BeginPlay()
{
	Super::BeginPlay();
	
    if (!IsValid(Flox))
    {
        if (!UGamecodeHelpers::GetFirstActorOfClass<AFlox>(this, Flox))
        {
            UGamecodeHelpers::DebugPrintScreen(FString("Detached Camera failed to find Flox player character in the current level."));
            return;
        }
    }

    AttachToPlayer(VerticalOffset, DistanceFromPlayer);

    APlayerController* playerController = GetWorld()->GetFirstPlayerController();
    playerController->SetViewTarget(this);
}

// Called every frame
void ADetachedCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (IsValid(Flox))
    {
        FVector floxLocation = Flox->GetActorLocation();
        FVector cameraLocation = SpringArm->GetComponentLocation();
        FVector floxVelocity = Flox->GetVelocity();

        bool isFloxHigher = floxLocation.Z >= cameraLocation.Z;
        bool isFloxRising = floxVelocity.Z > 0.1f;

        if (isFloxHigher && isFloxRising)
        {
            TrackPlayer(VerticalOffset, DistanceFromPlayer);
        }
        else
        {
            ScrollUp(DistanceFromPlayer);
        }
    }
}


#if WITH_EDITOR

void ADetachedCamera::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    AttachToPlayer(VerticalOffset, DistanceFromPlayer);
}

void ADetachedCamera::PostEditMove(bool bFinished)
{
    Super::PostEditMove(bFinished);

    AttachToPlayer(VerticalOffset, DistanceFromPlayer);
}

#endif // WITH_EDITOR


void ADetachedCamera::TrackPlayer(float i_VerticalOffset, float i_DistanceFromPlayer)
{
    if (IsValid(Flox))
    {
        SpringArm->TargetArmLength = i_DistanceFromPlayer;
        FVector floxLocation = Flox->GetActorLocation();
        FVector cameraLocation = SpringArm->GetComponentLocation();
        FVector cameraTrackingLocation = FVector(cameraLocation.X, cameraLocation.Y, floxLocation.Z + i_VerticalOffset);

        RootComponent->SetWorldLocation(cameraTrackingLocation);
    }
}

void ADetachedCamera::AttachToPlayer(float i_VerticalOffset, float i_DistanceFromPlayer)
{
    if (IsValid(Flox))
    {
        SpringArm->TargetArmLength = i_DistanceFromPlayer;
        FVector floxLocation = Flox->GetActorLocation();
        RootComponent->SetWorldLocation(floxLocation + FVector::UpVector * i_VerticalOffset);
    }
}

void ADetachedCamera::ScrollUp(float i_DistanceFromPlayer)
{
    SpringArm->TargetArmLength = i_DistanceFromPlayer;
    RootComponent->AddWorldOffset(FVector(0.f, 0.f, ScrollSpeed));
}

