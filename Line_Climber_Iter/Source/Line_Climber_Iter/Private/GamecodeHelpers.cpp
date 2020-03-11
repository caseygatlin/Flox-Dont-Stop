// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/GamecodeHelpers.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

//template<class T>
//bool UGamecodeHelpers::GetFirstActorOfClass(T* o_FoundActor)
//{
//    TArray<T*> allInputActors;
//    for (TActorIterator<T> It(GetWorld(), T::StaticClass()); It; ++It)
//    {
//        T* Actor = Cast<T>(*It);
//        if (Actor && !Actor->IsPendingKill())
//        {
//            allInputActors.Add(Actor);
//        }
//    }
//
//    if (allInputActors.Num() <= 0)
//    {
//        return false;
//    }
//
//    o_FoundActor = allInputActors[0];
//
//    return true;
//}

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
