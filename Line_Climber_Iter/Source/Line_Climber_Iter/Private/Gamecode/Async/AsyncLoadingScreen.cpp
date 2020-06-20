
#include "AsyncLoadingScreen.h"

UAsyncLoadingScreen::UAsyncLoadingScreen(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UAsyncLoadingScreen::NativeConstruct()
{

	Super::NativeConstruct();

}

void UAsyncLoadingScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	LoadingTime -= InDeltaTime;
}