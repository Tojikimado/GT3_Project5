// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "EndMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B001_GRP7_API UEndMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* TextScore;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void PlayLevel();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* PlayButton;

public:
	void SetScore(int Score);
};
