// Fill out your copyright notice in the Description page of Project Settings.

#include "Hand.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AHand::AHand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultHandSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultHandSceneRoot"));
	RootComponent = DefaultHandSceneRoot;
	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Motion Controller Component"));
	MotionController->SetupAttachment(GetRootComponent());
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(MotionController);
	

}

// Called when the game starts or when spawned
void AHand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AHand::InvertSkeletalMesh()
{
	SkeletalMesh->SetWorldRotation(FRotator(0, 0, 180));
	SkeletalMesh->SetWorldScale3D(FVector(1, 1, -1));
	MotionController->Hand = EControllerHand::Left;
}



