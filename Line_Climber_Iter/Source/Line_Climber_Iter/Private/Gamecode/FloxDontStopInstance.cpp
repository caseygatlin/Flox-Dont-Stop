// Fill out your copyright notice in the Description page of Project Settings.


#include "FloxDontStopInstance.h"
#include "Async/AsyncLoadingScreen.h"
#include "Async/AsyncLoadingScreenTask.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"


UFloxDontStopInstance::UFloxDontStopInstance()
{

	AsyncLoadingScreenTask = nullptr;

}

void UFloxDontStopInstance::RunLoadingScreen(TSubclassOf<UUserWidget> i_LoadingScreenClass, const float i_LoadTime)
{

	if (!IsValid(LoadingScreenInstance))
	{

		LoadingScreenInstance = CreateWidget<UAsyncLoadingScreen>(GetWorld(), i_LoadingScreenClass);

	}

	LoadingScreenInstance->AddToViewport();

	if (AsyncLoadingScreenTask == nullptr)
	{

		AsyncLoadingScreenTask = new FAsyncTask<LoadingScreenTask>(LoadingScreenInstance);

	}

	FString packageName = "/Game/MainLevel/MainLevelTestProcGen";
	LoadPackageAsync(packageName);
	if (IsValid(GetWorld()))
	{

		TArray<UObject*> allWorlds;
		GetObjectsOfClass(UWorld::StaticClass(), allWorlds);
		for (UObject* aWorld : allWorlds)
		{

			UWorld* theWorld = Cast<UWorld>(aWorld);
			if (theWorld->GetMapName() == FString("MainLevelTestProcGen"))
			{

				LevelToLoad = theWorld;

			}
		}

		AsyncLoadingScreenTask->StartBackgroundTask();

	}
}