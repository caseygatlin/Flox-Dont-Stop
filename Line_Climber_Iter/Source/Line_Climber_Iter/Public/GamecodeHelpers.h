// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GamecodeHelpers.generated.h"

/**
 * 
 */
UCLASS()
class LINE_CLIMBER_ITER_API UGamecodeHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:



    UFUNCTION(BlueprintCallable, Category = "Libraries|Gamecode Helpers")
        static void DebugPrintLog(FString i_StringToPrint);

    UFUNCTION(BlueprintCallable, Category = "Libraries|Gamecode Helpers")
        static void DebugPrintScreen(FString i_StringToPrint, float i_TimeToDisplay = 5.f, FColor i_TextColor = FColor::Blue, int32 i_Key = -1);

    template<typename SubclassOfActor>
    UFUNCTION(BlueprintCallable, Category = "Libraries|Gamecode Helpers")
        static FORCEINLINE bool GetFirstActorOfClass(UObject* i_OwningInstance, SubclassOfActor* o_FoundActor)
    {
        TArray<AActor*> allInputActors;
        for (TActorIterator<AActor> It(i_OwningInstance->GetWorld(), AActor::StaticClass()); It; ++It)
        {
            SubclassOfActor* Actor = Cast<SubclassOfActor>(*It);
            if (Actor && !Actor->IsPendingKill())
            {
                allInputActors.Add(Actor);
            }
        }

        if (allInputActors.Num() <= 0)
        {
            return false;
        }

        o_FoundActor = Cast<SubclassOfActor>(allInputActors[0]);

        return true;
    }

};
