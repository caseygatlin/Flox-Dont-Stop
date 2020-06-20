#pragma once

#include "Async/AsyncLoadingScreen.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Async/AsyncWork.h"


class LoadingScreenTask : public FNonAbandonableTask
{
public:

	LoadingScreenTask() { }

	/** Initializes references to loading screen and world that it needs during work.
	 * @param       The Widget to use as the loading screen.
	 * @param       A reference to the active world.
	*/
	LoadingScreenTask(UAsyncLoadingScreen* i_LoadingScreenWidget);

	/**Destructor.*/
	~LoadingScreenTask()
	{}

	// Required by engine
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(ClusterTask, STATGROUP_ThreadPoolAsyncTasks);
	}

#pragma region Public Methods

	/**Actual Update Function. Called directly, no explicit call required.*/
	void DoWork();

#pragma endregion

#pragma region Public Variables

	UAsyncLoadingScreen* LoadingScreenWidget;

#pragma endregion

};
