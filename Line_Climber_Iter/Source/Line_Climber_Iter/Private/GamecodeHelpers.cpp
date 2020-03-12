// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/GamecodeHelpers.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

void UGamecodeHelpers::DebugPrintLog(FString i_StringToPrint)
{

#ifdef UE_BUILD_DEBUG

    UE_LOG(LogTemp, Warning, TEXT("%s"), *i_StringToPrint);

#endif // UE_BUILD_DEBUG

}

void UGamecodeHelpers::DebugPrintScreen(FString i_StringToPrint, float i_TimeToDisplay, FColor i_TextColor, int32 i_Key)
{

#ifdef UE_BUILD_DEBUG

    GEngine->AddOnScreenDebugMessage(i_Key, i_TimeToDisplay, i_TextColor, i_StringToPrint);

#endif // UE_BUILD_DEBUG

}
