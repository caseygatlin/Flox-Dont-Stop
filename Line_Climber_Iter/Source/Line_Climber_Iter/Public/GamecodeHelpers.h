// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GamecodeHelpers.generated.h"

/**
 * 
 */
UCLASS()
class LINE_CLIMBER_ITER_API UGamecodeHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

    //UFUNCTION(BlueprintCallable, Category = "Libraries|Gamecode Helpers")
    //    static bool GetFirstActorOfClass(* o_FoundActor);

    UFUNCTION(BlueprintCallable, Category = "Libraries|Gamecode Helpers")
        static void DebugPrintLog(FString i_StringToPrint);

    UFUNCTION(BlueprintCallable, Category = "Libraries|Gamecode Helpers")
        static void DebugPrintScreen(FString i_StringToPrint, float i_TimeToDisplay = 5.f, FColor i_TextColor = FColor::Blue, int32 i_Key = -1);


};
