// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Hello World"));
}

void AWeaponBase::Shoot()
{
	switch (WeaponType)
	{
	case EnumWeaponType::AUTO:
		break;
	case EnumWeaponType::SEMIAUTO:
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("PAN"));
		break;
	case EnumWeaponType::LASER:
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ZZZZZZZZZZZZZZZZZZZZZZZ"));
		break;
	case EnumWeaponType::CAC:
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SLASH"));
		break;
	}
}