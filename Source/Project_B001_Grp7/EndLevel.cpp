// Fill out your copyright notice in the Description page of Project Settings.


#include "EndLevel.h"
#include "Project_B001_Grp7Character.h"

void AEndLevel::BeginPlay() {
	Super::BeginPlay();

	UEndMenu* hud = CreateWidget<UEndMenu>(GetWorld(), Hud);
	if (auto player = Cast<AProject_B001_Grp7Character>(GetWorld()->GetFirstPlayerController()->GetPawn())) {
		hud->SetScore(player->Points);
		hud->AddToViewport();
	}
}