// Fill out your copyright notice in the Description page of Project Settings.


#include "Start_GameMode.h"
#include "FloxDontStopInstance.h"
#include "Async/AsyncLoadingScreen.h"
#include "Engine/StreamableManager.h"


AStart_GameMode::AStart_GameMode()
{

}

void AStart_GameMode::RunLoadingScreen()
{
	UFloxDontStopInstance* gameInstance = GetGameInstance<UFloxDontStopInstance>();
	
	if (IsValid(gameInstance))
	{

		UAsyncLoadingScreen* loadingScreenDefault = LoadingScreenClass->GetDefaultObject<UAsyncLoadingScreen>();
		gameInstance->RunLoadingScreen(LoadingScreenClass, loadingScreenDefault->LoadingTime);


	}
}