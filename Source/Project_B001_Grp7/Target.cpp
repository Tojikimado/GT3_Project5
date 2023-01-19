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
		LifeTime = 5.0f;
		points = 25;
		break;
	case EnumDificulty::MEDIUM:
		LifeTime = 2.5f;
		points = 50;
		break;
	case EnumDificulty::HARD:
		LifeTime = 1.0f;
		points = 100;
		break;
	case EnumDificulty::HELL:
		LifeTime = 0.5f;
		points = 150;
		break;
	}
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timer += DeltaTime;
	if (timer >= LifeTime || Life <= 0) {
		K2_DestroyActor();
	}
}

int ATarget::Hit(int Damage)
{
	Life -= Damage;

	if (Life <= 0) {
		return points;
	}
	return 0;
}

