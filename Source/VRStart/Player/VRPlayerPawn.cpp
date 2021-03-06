// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPlayerPawn.h"
#include "HeadMountedDisplay.h"
#include "Engine/Engine.h"
#include "IXRTrackingSystem.h"

#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"

#include "Hand.h"

#include "ConstructorHelpers.h"

#include "Weapons/Gun.h"


// Sets default values
AVRPlayerPawn::AVRPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultPlayerSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultPlayerSceneRoot"));
	RootComponent = DefaultPlayerSceneRoot;
	VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	VROrigin->SetupAttachment(GetRootComponent());
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VROrigin);
	DebugText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DebugText"));
	DebugText->SetupAttachment(Camera);

}

// Called when the game starts or when spawned
void AVRPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	HMD = GEngine->XRSystem->GetHMDDevice();

	//Change for the distinct systems the origin tracking
	GEngine->XRSystem->SetTrackingOrigin(EHMDTrackingOrigin::Floor);
	if (ControllerBlueprint) {
		RightController = GetWorld()->SpawnActor<AHand>(ControllerBlueprint, GetTransform());
		RightController->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
		LeftController = GetWorld()->SpawnActor<AHand>(ControllerBlueprint, GetTransform());
		LeftController->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
		LeftController->InvertSkeletalMesh();
	}
	
}

// Called every frame
void AVRPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FQuat Orientation;
	//FVector Position;
	//FXRSensorProperties Properties;
	//GEngine->XRSystem->GetTrackingSensorProperties(3, Orientation, Position, Properties);

	//FString::Printf(TEXT("Testing: %s"), *Camera->GetForwardVector().ToString())
	//SetDebugText(FText::FromString(Position.ToString()));
}

// Called to bind functionality to input
void AVRPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MotionControllerThumbLeft_Y", this, &AVRPlayerPawn::MoveForward);
	InputComponent->BindAxis("MotionControllerThumbLeft_X", this, &AVRPlayerPawn::MoveRight);
	InputComponent->BindAction("TriggerLeft", IE_Pressed, this, &AVRPlayerPawn::TriggerLeftPressed);
	InputComponent->BindAction("TriggerRight", IE_Pressed, this, &AVRPlayerPawn::TriggerRightPressed);
	InputComponent->BindAction("TriggerLeft", IE_Released, this, &AVRPlayerPawn::TriggerLeftReleased);
	InputComponent->BindAction("TriggerRight", IE_Released, this, &AVRPlayerPawn::TriggerRightReleased);

	InputComponent->BindAction("GripRight", IE_Pressed, this, &AVRPlayerPawn::GripButtonRightPressed);
	InputComponent->BindAction("GripLeft", IE_Pressed, this, &AVRPlayerPawn::GripButtonLeftPressed);


}

void AVRPlayerPawn::SetDebugText(FText Text)
{
	DebugText->SetText(Text);
}

void AVRPlayerPawn::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		FVector Direction = Camera->GetForwardVector() * Value * 5;
		Direction.Z = 0;
		SetActorLocation(GetActorLocation() + Direction);
	}
}

void AVRPlayerPawn::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		FVector Direction = Camera->GetForwardVector() * Value * 5;
		SetActorLocation(GetActorLocation() + FVector(-Direction.Y, Direction.X, 0));
	}
}

void AVRPlayerPawn::TriggerLeftPressed()
{
	if (LeftController->GetAttachedActor()) {
		AGun* AttachedGun = Cast<AGun>(LeftController->GetAttachedActor());
		if (AttachedGun) AttachedGun->Fire();
	}
	else {
		LeftController->GrabActor();
	}
}

void AVRPlayerPawn::TriggerRightPressed()
{
	if (RightController->GetAttachedActor()) {
		AGun* AttachedGun = Cast<AGun>(RightController->GetAttachedActor());
		if (AttachedGun) AttachedGun->Fire();
	}
	else {
		RightController->GrabActor();
	}
}

void AVRPlayerPawn::TriggerLeftReleased()
{
	if(LeftController->IsGrabbing())	LeftController->ReleaseActor();
}

void AVRPlayerPawn::TriggerRightReleased()
{
	if(RightController->IsGrabbing())	RightController->ReleaseActor();
}

void AVRPlayerPawn::GripButtonRightPressed()
{
	if (RightController->GetAttachedActor() && RightController->GetAttachedActor()->IsA(AGun::StaticClass()) && !RightController->IsGrabbing()) RightController->ReleaseActor();
	else RightController->GrabActor(TEXT("RightHandGripPoint"));
}

void AVRPlayerPawn::GripButtonLeftPressed()
{
	if (LeftController->GetAttachedActor() && LeftController->GetAttachedActor()->IsA(AGun::StaticClass()) && !LeftController->IsGrabbing()) LeftController->ReleaseActor();
	else LeftController->GrabActor(TEXT("LeftHandGripPoint"));
}