// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Flox.generated.h"

class UCharacterMovementComponent;

UCLASS()
class LINE_CLIMBER_ITER_API AFlox : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AFlox();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Timeline for Jumping
    UPROPERTY(EditAnywhere, Category = "Timelines")
        UTimelineComponent* JumpTimeline;
    UPROPERTY(EditAnywhere, Category = "Timelines")
        UCurveFloat* FloatCurveJump;
    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        void JumpTimelineCallback(float i_val);
    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        void JumpTimelineFinishedCallback();
    UPROPERTY(EditAnywhere, Category = "Timelines")
        TEnumAsByte<ETimelineDirection::Type> JumpTimelineDirection;

    void PlayJumpTimeline();


    // Timeline for waiting while in air
    UPROPERTY(EditAnywhere, Category = "Timelines")
        UTimelineComponent* WaitTimeline;
    UPROPERTY(EditAnywhere, Category = "Timelines")
        UCurveFloat* FloatCurveWait;
    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        void WaitTimelineCallback(float i_val);
    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        void WaitTimelineFinishedCallback();
    UPROPERTY(EditAnywhere, Category = "Timelines")
        TEnumAsByte<ETimelineDirection::Type> WaitTimelineDirection;

    void PlayWaitTimeline();


    // Timeline for Dashing
    UPROPERTY(EditAnywhere, Category = "Timelines")
        UTimelineComponent* DashTimeline;
    UPROPERTY(EditAnywhere, Category = "Timelines")
        UCurveFloat* FloatCurveDash;
    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        void DashTimelineCallback(float i_val);
    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        void DashTimelineFinishedCallback();
    UPROPERTY(EditAnywhere, Category = "Timelines")
        TEnumAsByte<ETimelineDirection::Type> DashTimelineDirection;

    void PlayDashTimeline();



    UPROPERTY(EditAnywhere, Category = "Dash UI")
        UStaticMeshComponent* DashUI;

    UPROPERTY(EditAnywhere, Category = "Particle System")
        UParticleSystemComponent* ParticleSystem;

    // Jumping
    void BeginJump();
    void EndJump();

    // Aiming
    void BeginAim();
    void EndAim();

    // Walking
    void Walk(float i_axisVal);

    // Setting variable for UI location
    void RecordUpVal(float i_axisVal);

    // Dash UI
    void DrawDashUI();

private:
    void    SetupJumpTimeline();
    void    SetupWaitTimeline();
    void    SetupDashTimeline();
    void    SetupTimelines(UCurveFloat* i_jumpTimeline, UCurveFloat* i_waitTimeline, UCurveFloat* i_dashTimeline);
    void    UpdateTimeline(UTimelineComponent* i_timeLine, float i_dt);

    bool    m_bPastEdge;
    bool    m_bIsAiming;
    bool    m_bCanAim;
    bool    m_bBlockingInput;
    bool    m_bDashPressed;
    bool    m_bIsWalking;
    bool    m_bJumped;
    bool    m_bIsMoveRightZero;
    float   m_fPlayerAcceleration;
    float   m_fEdgeTop;
    float   m_fEdgeBottom;
    float   m_fPositionToHold;
    float   m_fOriginGravityScale = 4.f;
    float   m_fCastLength;
    float   m_fDashTargetRayCastObjects;
    float   m_fDashDampen;
    float   m_fAxisMoveUpValue;
    float   m_fAxisMoveRightValue;
    int     m_iMaxLength;
    int     m_iEdgeBlockCount;

    TArray<FVector>     m_vLocations;
    FVector             m_vDashDirection;
    FVector             m_vDefaultDashDir;
    FVector             m_vTargetPoint;
    TArray<FName>       m_nPlayerTags;

    UCharacterMovementComponent* m_charMovementComp;

};
