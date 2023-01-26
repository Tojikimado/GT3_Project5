// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponParticle.h"

// Sets default values
AWeaponParticle::AWeaponParticle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponParticle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;

	if (Timer > 2.0f) {
		K2_DestroyActor();
	}
}

