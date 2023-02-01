// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B001_GRP7_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* ResumeButton;



	class AProject_B001_Grp7Character* Player;

public :
	UFUNCTION()
		void init(AProject_B001_Grp7Character* player);

	UFUNCTION()
		void UnPauseGame();
};
