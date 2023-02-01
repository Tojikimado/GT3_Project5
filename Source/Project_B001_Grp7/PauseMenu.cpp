// Fill out your copyright notice in the Description page of Project Settings.

#include "PauseMenu.h"
#include "Project_B001_Grp7Character.h"

void UPauseMenu::NativeConstruct()
{
	if (ResumeButton) {
		ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::UnPauseGame);
	}
}

void UPauseMenu::UnPauseGame()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetPause(false);
	Player->HudPause->RemoveFromParent();
	Player->isPaused = false;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
}

void UPauseMenu::init(AProject_B001_Grp7Character* player)
{
	Player = player;
}