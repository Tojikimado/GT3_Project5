// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainMenuWidget.h"
#include "Sound/SoundBase.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B001_GRP7_API AMainMenuHUD : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UMainMenuWidget> Hud;

	UPROPERTY(EditAnywhere)
		USoundBase* Sound;
};
