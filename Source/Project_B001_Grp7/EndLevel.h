// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "EndMenu.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "EndLevel.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B001_GRP7_API AEndLevel : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UEndMenu> Hud;

public:
	virtual void BeginPlay() override;
};
