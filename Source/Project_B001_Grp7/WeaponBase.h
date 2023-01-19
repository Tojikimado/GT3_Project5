// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UENUM(BlueprintType)
enum class EnumWeaponType : uint8 {
	AUTO       UMETA(DisplayName = "AUTO"),
	SEMIAUTO       UMETA(DisplayName = "SEMIAUTO"),
	LASER       UMETA(DisplayName = "LASER"),
	CAC        UMETA(DisplayName = "CAC"),
};

UCLASS()
class PROJECT_B001_GRP7_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMesh* WeaponMesh;

	UPROPERTY(EditAnywhere)
		int Damage;

	UPROPERTY(EditAnywhere)
		int CurrentAmmo;

	UPROPERTY(EditAnywhere)
		int AllAmmo;

	UPROPERTY(EditAnywhere)
		int AmmoPerLoader;

	UPROPERTY(EditAnywhere)
		int MaxLoader;

	UPROPERTY(EditAnywhere)
		int ShootCoolDown;

	UPROPERTY(EditAnywhere)
		UAnimBlueprint* AnimationWeapon;

	UPROPERTY(EditAnywhere)
		FVector3d OffSetPosition;

	UPROPERTY(EditAnywhere)
		FRotator OffSetRotation;

	UPROPERTY(EditAnywhere)
		FVector3d OffSetScale;

	void Shoot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EnumWeaponType WeaponType;

	
};
