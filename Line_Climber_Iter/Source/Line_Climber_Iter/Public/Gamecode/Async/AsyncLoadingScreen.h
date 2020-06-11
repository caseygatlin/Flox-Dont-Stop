#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"

#include "AsyncLoadingScreen.generated.h"

/**
 * 
 */
UCLASS()
class LINE_CLIMBER_ITER_API UAsyncLoadingScreen : public UUserWidget
{
	GENERATED_BODY()

public:

	UAsyncLoadingScreen(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* LoadingText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* SplashImage;
	
};
