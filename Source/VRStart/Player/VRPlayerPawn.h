// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VRPlayerPawn.generated.h"

class IHeadMountedDisplay;
class UCameraComponent;
class USceneComponent;

UCLASS()
class VRSTART_API AVRPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	IHeadMountedDisplay* HMD;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultPlayerSceneRoot;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* VROrigin;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
};
