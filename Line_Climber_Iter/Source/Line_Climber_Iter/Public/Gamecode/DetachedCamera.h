// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DetachedCamera.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AFlox;

UCLASS()
class LINE_CLIMBER_ITER_API ADetachedCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADetachedCamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR

    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

    // Called after an actor has been moved in the editor
    virtual void PostEditMove(bool bFinished);

#endif // WITH_EDITOR


#pragma region Public Methods

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Detached Camera|Tracking")
        void TrackPlayer(float i_VerticalOffset, float i_DistanceFromPlayer);

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Detached Camera|Tracking")
        void AttachToPlayer(float i_VerticalOffset, float i_DistanceFromPlayer);

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Detached Camera|Scrolling")
        void ScrollUp(float i_DistanceFromPlayer);

#pragma endregion


#pragma region Public Variables

#pragma region Components

    UPROPERTY(EditAnywhere, Category = "Components")
        USpringArmComponent* SpringArm;

    UPROPERTY(EditAnywhere, Category = "Components")
        UCameraComponent* Camera;

#pragma endregion

#pragma region Player

    UPROPERTY(EditAnywhere, Category = "Player")
        AFlox* Flox;

#pragma endregion

#pragma region Movement

    UPROPERTY(EditAnywhere, Category = "Movement Settings")
        float VerticalOffset = 0.f;

    UPROPERTY(EditAnywhere, Category = "Movement Settings")
        float DistanceFromPlayer = 1000.f;

    UPROPERTY(EditAnywhere, Category = "Movement Settings")
        float ScrollSpeed = 1.f;

#pragma endregion

#pragma endregion

};
