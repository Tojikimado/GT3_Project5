// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	if (PlayButton) {
		PlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayLevel);
	}

	if (QuitButton) {
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitLevel);
	}
}

void UMainMenuWidget::PlayLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void UMainMenuWidget::QuitLevel()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
