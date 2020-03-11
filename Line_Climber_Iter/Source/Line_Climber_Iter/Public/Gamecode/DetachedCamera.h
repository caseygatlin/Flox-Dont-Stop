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

#pragma endregion

};
