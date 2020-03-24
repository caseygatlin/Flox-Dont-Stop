// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gamecode/Flox.h"

#include "Components/InputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NavArea_Obstacle.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMesh.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>


// Sets default values
AFlox::AFlox()
{

    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;


    // Timeline initialization
    static ConstructorHelpers::FObjectFinder<UCurveFloat> JumpCurve(TEXT("/Game/Curves/C_JumpCurve"));
    check(JumpCurve.Succeeded());
    FloatCurveJump = JumpCurve.Object;

    static ConstructorHelpers::FObjectFinder<UCurveFloat> WaitCurve(TEXT("/Game/Curves/C_WaitCurve"));
    check(WaitCurve.Succeeded());
    FloatCurveWait = WaitCurve.Object;

    static ConstructorHelpers::FObjectFinder<UCurveFloat> DashCurve(TEXT("/Game/Curves/C_DashCurve"));
    check(DashCurve.Succeeded());
    FloatCurveDash = DashCurve.Object;

    UCapsuleComponent* capsuleComponent = GetCapsuleComponent();
    capsuleComponent->SetCapsuleHalfHeight(96.f);
    capsuleComponent->SetCapsuleRadius(42.f);

    // Skeletal mesh component initialization
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> BirdMesh (TEXT(
        "SkeletalMesh'/Game/Character/BirdCharacter_Customizable.BirdCharacter_Customizable'"));

    static ConstructorHelpers::FObjectFinder<UClass> ClothingSimulationClass (TEXT(
        "Class'/Script/ClothingSystemRuntime.ClothingSimulationFactoryNv'"));

    USkeletalMeshComponent* playerMeshComponent = GetMesh();
    playerMeshComponent->SetSkeletalMesh(BirdMesh.Object);
    playerMeshComponent->SetRelativeScale3D(FVector(20.f, 20.f, 20.f));
    playerMeshComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
    playerMeshComponent->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);
    playerMeshComponent->ClothingSimulationFactory = ClothingSimulationClass.Object;
    playerMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -95.f));


    // Dash UI component initialization
    static ConstructorHelpers::FObjectFinder<UStaticMesh> DashUIMesh (TEXT(
        "StaticMesh'/Game/Models/Dash_UI.Dash_UI'"));

    DashUI = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DashUI"));
    DashUI->SetStaticMesh(DashUIMesh.Object);
    DashUI->SetVisibility(false);
    DashUI->SetGenerateOverlapEvents(false);
    DashUI->SetCollisionProfileName("NoCollision");


    // Dash Particles component initialization
    static ConstructorHelpers::FObjectFinder<UParticleSystem> DashParticleSystem (TEXT(
        "ParticleSystem'/Game/ParticleEffects/CharacterDash.CharacterDash'"));

    ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DashParticles"));
    ParticleSystem->SetTemplate(DashParticleSystem.Object);
    ParticleSystem->bAutoActivate = false;
    ParticleSystem->SetRelativeLocation(FVector(0.f, 0.f, -80.f));
    ParticleSystem->SetupAttachment(GetRootComponent());


    // Character Movement component initialization
    m_charMovementComp = GetCharacterMovement();
    m_charMovementComp->GravityScale = 2.f;
    m_charMovementComp->GroundFriction = 3.f;
    m_charMovementComp->JumpZVelocity = 700.f;
    m_charMovementComp->AirControl = 0.8f;
    m_charMovementComp->RotationRate = FRotator(0.f, 1080.f, 0.f);
    m_charMovementComp->bOrientRotationToMovement = true;
    m_charMovementComp->GetNavAgentPropertiesRef().AgentRadius = 42.f;
    m_charMovementComp->GetNavAgentPropertiesRef().AgentHeight = 192.f;
    m_charMovementComp->SetPlaneConstraintNormal(FVector(1.f, 0.f, 0.f));
    m_charMovementComp->bConstrainToPlane = true;


    // Add player tag
    m_nPlayerTags.Add("Player");
    Tags = m_nPlayerTags;

    bUseControllerRotationYaw = false;
    AutoPossessPlayer = EAutoReceiveInput::Type::Player0;
}


// Called when the game starts or when spawned
void AFlox::BeginPlay()
{

    Super::BeginPlay();

    SetupTimelines(FloatCurveJump, FloatCurveWait, FloatCurveDash);
    m_bPastEdge = false;
    m_iEdgeBlockCount = 0;

#ifdef  UE_BUILD_DEBUG
    if (m_nPlayerTags.Num() == 0)
    {

        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Flox needs player tag."));

    }
#endif // UE_BUILD_DEBUG

}


// Called every frame
void AFlox::Tick(float DeltaTime)
{

    Super::Tick(DeltaTime);

    UpdateTimeline(JumpTimeline, DeltaTime);
    UpdateTimeline(WaitTimeline, DeltaTime);
    UpdateTimeline(DashTimeline, DeltaTime);

    DrawDashUI();

}


// Called to bind functionality to input
void AFlox::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFlox::BeginJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFlox::EndJump);
    PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AFlox::BeginAim);
    PlayerInputComponent->BindAction("Aim", IE_Released, this, &AFlox::EndAim);

    PlayerInputComponent->BindAxis("MoveRight", this, &AFlox::Walk);

}


// Start the jump behavior
void AFlox::BeginJump()
{

    // Continue if not blocking input or aiming
    if (!m_bBlockingInput && !m_bIsAiming)
    {

        // Jump
        Jump();


        // Exit if player can't jump
        if (CanJump())
        {

            // If player can jump, set jumped to true
            m_bJumped = true;


            // Adjust Jump gravity with timeline
            PlayJumpTimeline();

        }
    }
}


// Position and place UI
void AFlox::DrawDashUI()
{

    if (m_charMovementComp->IsWalking())
    {

        m_bJumped = false;
        m_bCanAim = true;

    }

    if (!m_bBlockingInput)
    {
        if (m_fAxisMoveRightValue == 0 && m_fAxisMoveUpValue == 0)
        {

            m_vDashDirection = m_vDefaultDashDir;

        }

        else
        {

            FVector dashDirection = { 0.f, m_fAxisMoveRightValue * -1.f, m_fAxisMoveUpValue };
            dashDirection.Normalize();

            m_vDashDirection = dashDirection;
        }

        if (m_bIsAiming)
        {

            FVector targetPoint = m_vDashDirection * m_fCastLength;
            targetPoint += GetActorLocation();

            m_vTargetPoint = targetPoint;

            FHitResult traceHit;
            FCollisionQueryParams collisionParams;

            if (ActorLineTraceSingle(traceHit, GetActorLocation(), m_vTargetPoint, ECollisionChannel::ECC_WorldDynamic, collisionParams))
            {
                m_vTargetPoint = traceHit.Location;
            }

            DashUI->SetWorldLocation(m_vTargetPoint);

        }
    }

}


// Setup the timeline for the jump gravity
void AFlox::SetupJumpTimeline()
{
    FOnTimelineFloat        onTimelineCallback;
    FOnTimelineEventStatic  onTimelineFinishedCallback;

    JumpTimeline = NewObject<UTimelineComponent>(this, FName("Jump Timeline"));
    JumpTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript;

    this->BlueprintCreatedComponents.Add(JumpTimeline);

    JumpTimeline->SetNetAddressable();
    JumpTimeline->SetPropertySetObject(this);
    JumpTimeline->SetDirectionPropertyName(FName("JumpTimelineDirection"));
    JumpTimeline->SetLooping(false);
    JumpTimeline->SetTimelineLength(.25f);
    JumpTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
    JumpTimeline->SetPlaybackPosition(0.0f, false);

    onTimelineCallback.BindUFunction(this, FName{ TEXT("JumpTimelineCallback") });
    onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("JumpTimelineFinishedCallback") });

    JumpTimeline->AddInterpFloat(FloatCurveJump, onTimelineCallback);
    JumpTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);
    JumpTimeline->RegisterComponent();
}


// Setup the timeline for waiting for 1.5 seconds
void AFlox::SetupWaitTimeline()
{

    FOnTimelineFloat        onTimelineCallback;
    FOnTimelineEventStatic  onTimelineFinishedCallback;

    WaitTimeline = NewObject<UTimelineComponent>(this, FName("Wait Timeline"));
    WaitTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript;

    this->BlueprintCreatedComponents.Add(WaitTimeline);

    WaitTimeline->SetNetAddressable();
    WaitTimeline->SetPropertySetObject(this);
    WaitTimeline->SetDirectionPropertyName(FName("WaitTimelineDirection"));
    WaitTimeline->SetLooping(false);
    WaitTimeline->SetTimelineLength(1.5f);
    WaitTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
    WaitTimeline->SetPlaybackPosition(0.0f, false);

    onTimelineCallback.BindUFunction(this, FName{ TEXT("WaitTimelineCallback") });
    onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("WaitTimelineFinishedCallback") });

    WaitTimeline->AddInterpFloat(FloatCurveJump, onTimelineCallback);
    WaitTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);
    WaitTimeline->RegisterComponent();

}


// Setup the timeline for dash velocity
void AFlox::SetupDashTimeline()
{
    FOnTimelineFloat        onTimelineCallback;
    FOnTimelineEventStatic  onTimelineFinishedCallback;

    DashTimeline = NewObject<UTimelineComponent>(this, FName("Dash Timeline"));
    DashTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript;

    this->BlueprintCreatedComponents.Add(DashTimeline);

    DashTimeline->SetNetAddressable();
    DashTimeline->SetPropertySetObject(this);
    DashTimeline->SetDirectionPropertyName(FName("DashTimelineDirection"));
    DashTimeline->SetLooping(false);
    DashTimeline->SetTimelineLength(.35f);
    DashTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
    DashTimeline->SetPlaybackPosition(0.0f, false);

    onTimelineCallback.BindUFunction(this, FName{ TEXT("DashTimelineCallback") });
    onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("DashTimelineFinishedCallback") });

    DashTimeline->AddInterpFloat(FloatCurveJump, onTimelineCallback);
    DashTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);
    DashTimeline->RegisterComponent();
}


// Set up timelines for use in player movement
void AFlox::SetupTimelines(UCurveFloat* i_jumpTimeline, UCurveFloat* i_waitTimeline, UCurveFloat* i_dashTimeline)
{

    if (i_jumpTimeline != NULL)
    {

        SetupJumpTimeline();

    }

    if (i_waitTimeline != NULL)
    {

        SetupWaitTimeline();

    }

    if (i_dashTimeline != NULL)
    {

        SetupDashTimeline();

    }
}

// Set gravity scale of character to the value in the timeline
void AFlox::JumpTimelineCallback(float i_val)
{

    m_charMovementComp->GravityScale = i_val;

}


void AFlox::JumpTimelineFinishedCallback() {}


// Play timeline for jump gravity
void AFlox::PlayJumpTimeline()
{
    if (JumpTimeline != NULL)
    {
        JumpTimeline->PlayFromStart();
    }
}


void AFlox::WaitTimelineCallback(float i_val) {}


// Bring gravity back to normal
void AFlox::WaitTimelineFinishedCallback()
{

    PlayJumpTimeline();

}


// Wait for 1.5 seconds
void AFlox::PlayWaitTimeline()
{

    if (WaitTimeline != NULL)
    {

        WaitTimeline->PlayFromStart();

    }
}


// Move character in the dash formation
void AFlox::DashTimelineCallback(float i_val)
{

    m_charMovementComp->Velocity = m_vDashDirection * i_val;

}


// Stop dashing and start falling
void AFlox::DashTimelineFinishedCallback()
{

    m_charMovementComp->GravityScale = m_fOriginGravityScale;
    m_charMovementComp->SetMovementMode(EMovementMode::MOVE_Falling);
    m_bIsAiming = false;
    m_bBlockingInput = false;
    ParticleSystem->SetActive(false);

}


// Start velocity change for dash
void AFlox::PlayDashTimeline()
{

    if (DashTimeline != NULL)
    {

        DashTimeline->Play();

    }
}


// End the jump behavior
void AFlox::EndJump()
{

    // Bring player back  to the ground
    if (!m_bBlockingInput && !m_bIsAiming)
    {

        m_charMovementComp->GravityScale = m_fOriginGravityScale;

        StopJumping();
        JumpTimeline->Stop();

    }
}


// Float and place reticle
void AFlox::BeginAim()
{

    m_bDashPressed = true;

    if (m_bCanAim)
    {

        // Set isAiming and aiming reticle
        DashUI->SetVisibility(true);
        m_bIsAiming = true;


        // Stop character in mid air
        JumpTimeline->Stop();
        m_charMovementComp->GravityScale = 0.0f;
        m_charMovementComp->Velocity = FVector::ZeroVector;

        // Float in mid air for 1.5 seconds
        PlayWaitTimeline();

    }
}


// Stop floating, dash 
void AFlox::EndAim()
{

    if (m_bDashPressed)
    {

        m_bDashPressed = false;

    }

    DashUI->SetVisibility(false);
    ParticleSystem->SetActive(true, true);

    if (m_bIsAiming && !m_bBlockingInput)
    {

        JumpTimeline->Stop();
        m_charMovementComp->GravityScale = 0.0f;
        m_bCanAim = false;
        m_bBlockingInput = true;
        m_charMovementComp->SetMovementMode(EMovementMode::MOVE_Falling);
        PlayDashTimeline();

    }
}

// Move character
void AFlox::Walk(float i_axisVal)
{

    m_fAxisMoveRightValue = i_axisVal;

    if (i_axisVal == 0)
    {

        m_bIsWalking = false;

    }

    if (!m_bIsAiming)
    {

        if (i_axisVal > 0)
        {

            m_vDefaultDashDir = FVector::LeftVector;

        }

        else if (i_axisVal < 0)
        {

            m_vDefaultDashDir = FVector::RightVector;

        }

        AddMovementInput(FVector::LeftVector, i_axisVal);
        m_bIsWalking = true;

    }
}


// Set MoveUpVal for positioning UI
void AFlox::RecordUpVal(float i_axisVal)
{

    m_fAxisMoveUpValue = i_axisVal;

}


// Update the given timeline
void AFlox::UpdateTimeline(UTimelineComponent* i_timeLine, float i_dt)
{
    if (i_timeLine)
    {

        i_timeLine->TickComponent(i_dt, ELevelTick::LEVELTICK_TimeOnly, NULL);

    }
}