#pragma once

#include "AsyncLoadingScreenTask.h"
#include "AsyncLoadingScreen.h"
#include "GamecodeHelpers.h"

#include "Async/TaskGraphInterfaces.h"
#include "Kismet/GameplayStatics.h"


LoadingScreenTask::LoadingScreenTask(UAsyncLoadingScreen* i_LoadingScreenWidget) :
	LoadingScreenWidget(i_LoadingScreenWidget)
{

}


void LoadingScreenTask::DoWork()
{
	if (IsValid(LoadingScreenWidget))
	{

		while (LoadingScreenWidget->LoadingTime > 0.f)
		{
			// Any logic updates that need to happen with Loading Screen can happen here.
		}

		UAsyncLoadingScreen* localLoadingScreenCopy = LoadingScreenWidget;
		FGraphEventRef removeFromViewportTask = UGamecodeHelpers::RunLambdaOnGameThread(
			[localLoadingScreenCopy]
			{
				localLoadingScreenCopy->RemoveFromViewport();
				UGameplayStatics::OpenLevel(localLoadingScreenCopy, FName(TEXT("MainLevelTestProcGen")));
			}
		);

		FTaskGraphInterface::Get().WaitUntilTaskCompletes(removeFromViewportTask);

	}
}
