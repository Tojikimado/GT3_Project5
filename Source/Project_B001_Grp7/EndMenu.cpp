// Fill out your copyright notice in the Description page of Project Settings.


#include "EndMenu.h"
#include "Components/TextBlock.h"

void UEndMenu::NativeConstruct()
{
	if (PlayButton) {
		PlayButton->OnClicked.AddDynamic(this, &UEndMenu::PlayLevel);
	}
}

void UEndMenu::SetScore(int Score)
{
	if (TextScore) {
		TextScore->SetText(FText::AsNumber(Score));
	}
}

void UEndMenu::PlayLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "L_MainMenu");
}