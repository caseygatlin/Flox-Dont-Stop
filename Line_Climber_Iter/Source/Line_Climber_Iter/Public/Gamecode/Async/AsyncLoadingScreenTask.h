#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"


class LoadingScreenTask : public FNonAbandonableTask
{
public:

	/** Initializes references to the systems it needs to access during work.
	 * @param       Reference to the Rendering core system.
	 * @param       Reference to the Cluster Pools subsystem.
	*/
	LoadingScreenTask()
	{}

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



#pragma endregion

};
