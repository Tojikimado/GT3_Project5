// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuHUD.h"

void AMainMenuHUD::BeginPlay() {
	Super::BeginPlay();
	CreateWidget<UMainMenuWidget>(GetWorld(), Hud)->AddToViewport();

	UGameplayStatics::PlaySound2D(GetWorld(), Sound, 1, 1, 1);
}