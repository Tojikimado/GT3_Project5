// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Project_B001_Grp7Character.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "PickupWeapon.generated.h"

UCLASS()
class PROJECT_B001_GRP7_API APickupWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AWeaponBase> Weapon;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		float floatSpeed = 20.0f;
	UPROPERTY(EditAnywhere)
		float rotateSpeed = 20.0f;

	UPROPERTY(EditAnywhere)
		UTextRenderComponent* PointCostText;

	void Float(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		int Cost;
};
