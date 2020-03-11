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

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Timeline for Jumping
    UPROPERTY()
        UTimelineComponent* JumpTimeline;
    UPROPERTY()
        UCurveFloat* FloatCurveJump;
    UFUNCTION()
        void JumpTimelineCallback(float i_val);
    UFUNCTION()
        void JumpTimelineFinishedCallback();
    UPROPERTY()
        TEnumAsByte<ETimelineDirection::Type> JumpTimelineDirection;

    void PlayJumpTimeline();


    // Timeline for waiting while in air
    UPROPERTY()
        UTimelineComponent* WaitTimeline;
    UPROPERTY()
        UCurveFloat* FloatCurveWait;
    UFUNCTION()
        void WaitTimelineCallback(float i_val);
    UFUNCTION()
        void WaitTimelineFinishedCallback();
    UPROPERTY()
        TEnumAsByte<ETimelineDirection::Type> WaitTimelineDirection;

    inline void PlayWaitTimeline();


    // Timeline for Dashing
    UPROPERTY()
        UTimelineComponent* DashTimeline;
    UPROPERTY()
        UCurveFloat* FloatCurveDash;
    UFUNCTION()
        void DashTimelineCallback(float i_val);
    UFUNCTION()
        void DashTimelineFinishedCallback();
    UPROPERTY()
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
    void            SetupJumpTimeline();
    void            SetupWaitTimeline();
    void            SetupDashTimeline();
    void            SetupTimelines(UCurveFloat* i_jumpTimeline,
        UCurveFloat* i_waitTimeline,
        UCurveFloat* i_dashTimeline);
    inline void     UpdateTimeline(UTimelineComponent* i_timeLine, float i_dt);

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
    float   m_fOriginGravityScale;
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
