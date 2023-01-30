// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B001_GRP7_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* PlayButton;

	UFUNCTION()
		void PlayLevel();

	UPROPERTY(EditAnywhere)
		FName LevelName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* QuitButton;

	UFUNCTION()
		void QuitLevel();
};
