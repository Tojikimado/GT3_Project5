// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "DrawDebugHelpers.h"
#include "Project_B001_Grp7Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "Camera/CameraComponent.h"

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

int AWeaponBase::Shoot(ATarget* Target)
{
	return 0;
}

void AWeaponBase::Shoot(class AProject_B001_Grp7Character* Player)
{
	
}

ATarget* AWeaponBase::Raycast(AProject_B001_Grp7Character* Player)
{
	FHitResult OutHit;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);

	FVector CamStart = Player->GetCamera()->GetComponentLocation();
	FVector CamForwardVector = Player->GetCamera()->GetForwardVector();

	FVector CamEnd = CamStart + (CamForwardVector * 50000.0f);

	bool CamIsHit = Player->GetWorld()->LineTraceSingleByChannel(OutHit, CamStart, CamEnd, ECC_Visibility, CollisionParams);

	FVector Start = Player->WeaponMesh->GetSocketLocation("BulletStart");

	FVector End = CamIsHit ? OutHit.ImpactPoint : CamEnd;

	//Draw Ray
	if (WeaponType == EnumWeaponType::LASER)
	{
		Player->Laser->SetBeamSourcePoint(0, Start, 0);
		Player->Laser->SetBeamTargetPoint(0, End, 0);
	}
	else {
		DrawDebugLine(Player->GetWorld(), Start, End, FColor::Yellow, false, 0.05, 0, 1);
	}

	bool IsHit = Player->GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

	if (IsHit) {

		if (WeaponType != EnumWeaponType::LASER)
		{
			ADecalActor* DecalActor = Player->GetWorld()->SpawnActor<ADecalActor>(OutHit.ImpactPoint, FRotator());
			DecalActor->SetLifeSpan(2.0f);
			DecalActor->SetDecalMaterial(BulletHoleMaterial);
			DecalActor->GetDecal()->DecalSize = FVector(30.0f, 60.0f, 60.0f);
		}

		if (OutHit.GetActor()->IsA(ATarget::StaticClass())) {
			return Cast<ATarget>(OutHit.GetActor());
		}
	}

	return nullptr;
}


