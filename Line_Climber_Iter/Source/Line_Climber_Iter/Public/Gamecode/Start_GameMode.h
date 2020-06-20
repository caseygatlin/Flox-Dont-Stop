// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Async/AsyncLoadingScreenTask.h"
#include "Blueprint/UserWidget.h"

#include "Async/AsyncWork.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Start_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class LINE_CLIMBER_ITER_API AStart_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AStart_GameMode();

	UFUNCTION(BlueprintCallable, Category = "Gamecode|Game Modes|Start")
		void RunLoadingScreen();

	UPROPERTY(EditAnywhere, Category = "Loading Screen")
		TSubclassOf<UUserWidget> LoadingScreenClass;

};
