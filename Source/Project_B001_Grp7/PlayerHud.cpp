// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"

void UPlayerHud::SetAmmo(int CurrentAmmo, int AllAmmo)
{
	CurrentAmmoText->SetText(FText::AsNumber(CurrentAmmo));
	AllAmmoText->SetText(FText::AsNumber(AllAmmo));
}

void UPlayerHud::SetPointsAndMoney(int Points, int Money)
{
	PointsText->SetText(FText::AsNumber(Points));
	MoneyText->SetText(FText::AsNumber(Money));
}
