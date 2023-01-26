// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponParticle.generated.h"

UCLASS()
class PROJECT_B001_GRP7_API AWeaponParticle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponParticle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int Timer = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
