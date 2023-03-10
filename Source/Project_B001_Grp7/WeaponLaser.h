// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponLaser.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B001_GRP7_API AWeaponLaser : public AWeaponBase
{
	GENERATED_BODY()
	
public :
	virtual int Shoot(ATarget* Target) override;

	virtual void Shoot(class AProject_B001_Grp7Character* Player) override;

	int LaserMultiplicator = 1;

	UPROPERTY(EditAnywhere)
		UParticleSystem* Laser;
};
