// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Target.h"
#include "ZoneHUD.h"
#include "Project_B001_Grp7Character.h"
#include "SpawningZone.generated.h"

UCLASS()
class PROJECT_B001_GRP7_API ASpawningZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawningZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FActorSpawnParameters SpawnInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
		float SpawnCooldown;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ATarget> TargetToSpawn;

	UPROPERTY(EditAnywhere)
		float Timer;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool started = false;

	float timerSpawn;

	float timerTimer;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UZoneHUD> HudClass;

	UPROPERTY()
		class UZoneHUD* Hud;
};
