// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B001_GRP7_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	int Score = 0;
};
