// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_B001_Grp7GameMode.h"
#include "Project_B001_Grp7Character.h"
#include "UObject/ConstructorHelpers.h"

AProject_B001_Grp7GameMode::AProject_B001_Grp7GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
