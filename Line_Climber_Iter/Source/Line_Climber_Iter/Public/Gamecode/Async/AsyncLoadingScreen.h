#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"

#include "AsyncLoadingScreen.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class LINE_CLIMBER_ITER_API UAsyncLoadingScreen : public UUserWidget
{
	GENERATED_BODY()

public:

	UAsyncLoadingScreen(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Timer")
		float LoadingTime = 5.f;

};
