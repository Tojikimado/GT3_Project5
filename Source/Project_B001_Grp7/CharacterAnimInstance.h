// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories=AnimInstance, BlueprintType)
class CharacterAnimInstance: public UAnimInstance
{
	GENERATED_BODY()
public:
	CharacterAnimInstance();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		float Speed;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
