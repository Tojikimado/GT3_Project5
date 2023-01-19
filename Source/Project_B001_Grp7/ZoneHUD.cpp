// Fill out your copyright notice in the Description page of Project Settings.


#include "ZoneHUD.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UZoneHUD::SetTimer(float TimeRemainings, float TimeMax)
{
	int timeRemaining = 0;
	if (TimeRemainings > 0) {
		timeRemaining = TimeRemainings;
	}

	if (TimerText) {
		TimerText->SetText(FText::AsNumber(timeRemaining));
	}

	if (TimerImage && TimerMID) {

		TimerMID->SetScalarParameterValue("Percent", TimeRemainings / TimeMax);
	}
}

// Called when the game starts or when spawned
void UZoneHUD::Init()
{
	if (TimerImage && TimerMI) {
		TimerMID = UMaterialInstanceDynamic::Create(TimerMI, this);
		TimerImage->SetBrushFromMaterial(TimerMID);
	}
}