// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"
#include "Components/TextBlock.h"

void UPlayerHud::SetAmmo(int CurrentAmmo, int AllAmmo)
{
	CurrentAmmoText->SetText(FText::AsNumber(CurrentAmmo));
	AllAmmoText->SetText(FText::AsNumber(AllAmmo));
}

void UPlayerHud::SetPoints(int Points)
{
	PointsText->SetText(FText::AsNumber(Points));
}
