// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GlobalStructs.h"
#include "HandAnimInstance.generated.h"


/**
 * 
 */
UCLASS()
class VRSTART_API UHandAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grip Status")
	EGripState GripStatus = EGripState::Open;
	
	
};
