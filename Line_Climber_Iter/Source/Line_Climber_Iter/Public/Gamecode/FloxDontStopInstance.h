// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Async/AsyncLoadingScreenTask.h"

#include "Async/AsyncWork.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FloxDontStopInstance.generated.h"

class UAsyncLoadingScreen;

/**
 * 
 */
UCLASS()
class LINE_CLIMBER_ITER_API UFloxDontStopInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFloxDontStopInstance();

		

	UFUNCTION(BlueprintCallable, Category = "Gamecode|Game Instance|Loading")
		void RunLoadingScreen(TSubclassOf<UUserWidget> i_LoadingScreenClass, const float i_LoadTime);
	
	UAsyncLoadingScreen* LoadingScreenInstance;

	FString LoadLevelPath;

	UWorld* LevelToLoad;

	FAsyncTask<LoadingScreenTask>* AsyncLoadingScreenTask;

};
