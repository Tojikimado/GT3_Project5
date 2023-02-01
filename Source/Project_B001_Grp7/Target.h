// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

UENUM(BlueprintType)
enum class EnumDificulty : uint8 {
	EASY       UMETA(DisplayName = "EASY"),
	MEDIUM       UMETA(DisplayName = "MEDIUM"),
	HARD       UMETA(DisplayName = "HARD"),
	HELL        UMETA(DisplayName = "HELL"),
};

UCLASS()
class PROJECT_B001_GRP7_API ATarget : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EnumDificulty Dificulty;

	float Life = 250;
	float LifeTime;
	float timer;
	float points;

public:
	int Hit(int Damage);
};
