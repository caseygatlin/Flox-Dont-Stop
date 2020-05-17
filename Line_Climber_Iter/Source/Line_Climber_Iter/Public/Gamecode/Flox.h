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

#pragma region Public Methods

#pragma region Timelines

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        // Executes every step of the Jump Timeline.
        void JumpTimelineCallback(float i_val);

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        // Executes when the Jump Timeline curve has reached its length.
        void JumpTimelineFinishedCallback();

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        // Starts the Jump Timeline
        void PlayJumpTimeline();

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        // Executes every step of the Wait Timeline.
        void WaitTimelineCallback(float i_val);

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        // Executes when the Wait Timeline curve has reached its length.
        void WaitTimelineFinishedCallback();

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        // Starts the Wait Timeline.
        void PlayWaitTimeline();

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        // Executes every step of the Dash Timeline.
        void DashTimelineCallback(float i_val);

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        // Executes when the Dash Timeline curve has reached its length.
        void DashTimelineFinishedCallback();

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Timelines")
        // Starts the Dash Timeline.
        void PlayDashTimeline();

#pragma endregion

#pragma region Jumping

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Jumping")
        // Starts a player jump.
        void BeginJump();

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Jumping")
        // Ends a player jump.
        void EndJump();

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Jumping")
        bool GetJumped() const { return m_bJumped; }

#pragma endregion

#pragma region Aiming

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Aiming")
        // Hovers the player in the air and allows for aiming the dash reticle.
        void BeginAim();

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Aiming")
        // Starts a dash.
        void EndAim();

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Aiming")
        // Setting variable for UI location
        void RecordUpVal(float i_axisVal);

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Aiming")
        // Places the Dash UI in the correct location.
        void DrawDashUI();

#pragma endregion

#pragma region Walking

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Walking")
        // Takes input and moves the player right or left.
        void Walk(float i_axisVal);

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Walking")
        bool GetIsWalking() const { return m_bIsWalking; }

#pragma endregion

#pragma region Dashing

    UFUNCTION(BlueprintCallable, Category = "Gamecode|Flox|Dashing")
        bool GetBlockingInput() const { return m_bBlockingInput; }

#pragma endregion

#pragma endregion

#pragma region Public Variables

#pragma region Components

    UPROPERTY(EditAnywhere, Category = "Components")
        // The reticle used for aiming the player's dash.
        UStaticMeshComponent* DashUI;

    UPROPERTY(EditAnywhere, Category = "Components")
        // Particles that appear when the player dashes.
        UParticleSystemComponent* ParticleSystem;

#pragma endregion

#pragma region Timelines

    UPROPERTY(EditAnywhere, Category = "Timelines")
        // Timeline for managing gravity while jumping.
        UTimelineComponent* JumpTimeline;

    UPROPERTY(EditAnywhere, Category = "Timelines")
        // Curve used in the Jump Timeline.
        UCurveFloat* FloatCurveJump;

    UPROPERTY(EditAnywhere, Category = "Timelines")
        // The direction at which the Jump Timeline should go.
        TEnumAsByte<ETimelineDirection::Type> JumpTimelineDirection;

    UPROPERTY(EditAnywhere, Category = "Timelines")
        // Timeline for waiting to dash while in the air.
        UTimelineComponent* WaitTimeline;

    UPROPERTY(EditAnywhere, Category = "Timelines")
        // Curve used in the Wait Timeline.
        UCurveFloat* FloatCurveWait;

    UPROPERTY(EditAnywhere, Category = "Timelines")
        // The direction at which the Wait Timeline should go.
        TEnumAsByte<ETimelineDirection::Type> WaitTimelineDirection;

    UPROPERTY(EditAnywhere, Category = "Timelines")
        // Timeline for Dashing.
        UTimelineComponent* DashTimeline;

    UPROPERTY(EditAnywhere, Category = "Timelines")
        // Curve used in the Dash Timeline.
        UCurveFloat* FloatCurveDash;

    UPROPERTY(EditAnywhere, Category = "Timelines")
        // The direction at which the Dash Timeline should go.
        TEnumAsByte<ETimelineDirection::Type> DashTimelineDirection;

#pragma endregion

#pragma region Aiming

    UPROPERTY(EditAnywhere, Category = "Aiming")
        float CastLength;

#pragma endregion

#pragma endregion

private:

#pragma region Private Methods

#pragma region Timelines

    void    SetupJumpTimeline();
    void    SetupWaitTimeline();
    void    SetupDashTimeline();
    void    SetupTimelines();
    void    UpdateTimeline(UTimelineComponent* i_timeLine, float i_dt);

#pragma endregion

#pragma endregion

#pragma region Private Variables

#pragma region Components

    UCharacterMovementComponent* m_charMovementComp;

#pragma endregion

#pragma region Jumping

    UPROPERTY(VisibleAnywhere, Category = "Jumping")
        // If the player is currently jumping.
        bool m_bJumped;

    UPROPERTY(VisibleAnywhere, Category = "Jumping")
        float m_fOriginGravityScale = 4.f;

#pragma endregion

#pragma region Aiming

    UPROPERTY(VisibleAnywhere, Category = "Aiming")
        // If the player is currently aiming.
        bool m_bIsAiming;

    UPROPERTY(VisibleAnywhere, Category = "Aiming")
        // If the player is currently able to aim.
        bool m_bCanAim;

    UPROPERTY(VisibleAnywhere, Category = "Aiming")
        float m_fDashTargetRayCastObjects;

    UPROPERTY(VisibleAnywhere, Category = "Aiming")
        FVector m_vTargetPoint;

#pragma endregion

#pragma region Walking

    UPROPERTY(VisibleAnywhere, Category = "Walking")
        bool m_bIsWalking;

    UPROPERTY(VisibleAnywhere, Category = "Walking")
        bool m_bIsMoveRightZero;

#pragma endregion

#pragma region Dashing

    UPROPERTY(VisibleAnywhere, Category = "Dashing")
        // Whether or not player input is blocked from action.
        bool m_bBlockingInput;

    UPROPERTY(VisibleAnywhere, Category = "Dashing")
        // Whether or not the dash button has just been pressed.
        bool m_bDashPressed;

    UPROPERTY(VisibleAnywhere, Category = "Dashing")
        float m_fDashDampen;

    UPROPERTY(VisibleAnywhere, Category = "Dashing")
        float m_fAxisMoveUpValue;

    UPROPERTY(VisibleAnywhere, Category = "Dashing")
        float m_fAxisMoveRightValue;

    UPROPERTY(VisibleAnywhere, Category = "Dashing")
        FVector m_vDashDirection;

    UPROPERTY(VisibleAnywhere, Category = "Dashing")
        FVector m_vDefaultDashDir;

#pragma endregion

#pragma region Death

    UPROPERTY(VisibleAnywhere, Category = "Death")
        bool m_bPastEdge;

    UPROPERTY(VisibleAnywhere, Category = "Death")
        float m_fEdgeTop;

    UPROPERTY(VisibleAnywhere, Category = "Death")
        float m_fEdgeBottom;

    UPROPERTY(VisibleAnywhere, Category = "Death")
        int m_iEdgeBlockCount;

#pragma endregion

#pragma region Tags

    UPROPERTY(VisibleAnywhere, Category = "Death")
        TArray<FName> m_nPlayerTags;

#pragma endregion

#pragma endregion

};
