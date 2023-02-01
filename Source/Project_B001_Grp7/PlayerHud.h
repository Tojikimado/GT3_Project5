// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B001_GRP7_API UPlayerHud : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* PointsText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* MoneyText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* CurrentAmmoText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* AllAmmoText;

public:

	void SetAmmo(int CurrentAmmo, int AllAmmo);

	void SetPointsAndMoney(int Points, int Money);
};
