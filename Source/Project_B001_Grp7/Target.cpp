// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

// Sets default values
ATarget::ATarget()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target Mesh"));
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	switch (Dificulty) {
	case EnumDificulty::EASY:
		Life = 5.0f;
		break;
	case EnumDificulty::MEDIUM:
		Life = 2.5f;
		break;
	case EnumDificulty::HARD:
		Life = 1.0f;
		break;
	case EnumDificulty::HELL:
		Life = 0.5f;
		break;
	}
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timer += DeltaTime;
	if (timer >= Life) {
		K2_DestroyActor();
	}
}

