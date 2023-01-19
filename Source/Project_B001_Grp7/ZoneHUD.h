// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ZoneHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B001_GRP7_API UZoneHUD : public UUserWidget
{
	GENERATED_BODY()
	
public :
	void SetTimer(float TimeRemainings, float TimeMax);

	UPROPERTY(EditAnywhere)
		class UTextBlock* TimerText;
};
