// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "DrawDebugHelpers.h"
#include "Project_B001_Grp7Character.h"
#include "Particles/ParticleSystemComponent.h"
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

int AWeaponBase::Shoot(ATarget* Target, int Multiplicator)
{
	return Target->Hit(Damage * Multiplicator);
}

void AWeaponBase::Shoot(class AProject_B001_Grp7Character* Player)
{
	ATarget* target = nullptr;
	switch (WeaponType)
	{
	case EnumWeaponType::AUTO:
		if (Player->TimerShootCooldown >= ShootCoolDown) {
			CurrentAmmo -= 1;
			target = Raycast(Player);
		}
		break;
	case EnumWeaponType::SEMIAUTO:
		if (Player->TimerShootCooldown >= ShootCoolDown)
		{
			CurrentAmmo -= 1;
			target = Raycast(Player);
			Player->Shooting = false;
		}
		break;
	case EnumWeaponType::LASER:
		target = Raycast(Player);
		Player->Laser->SetHiddenInGame(false);
		if (Player->TimerShootCooldown >= ShootCoolDown)
		{
			CurrentAmmo -= 5;
			Player->LaserMultiplicator += 1;
		}
		break;
	}

	if (Player->TimerShootCooldown >= ShootCoolDown) {
		Player->TimerShootCooldown = 0;
		Player->Hud->SetAmmo(CurrentAmmo, AllAmmo);

		if (target) {
			auto earningPoints = Shoot(target, Player->LaserMultiplicator);
			Player->Points += earningPoints;
			Player->Money += (earningPoints / 2);
			Player->Hud->SetPointsAndMoney(Player->Points, Player->Money);
		}
	}
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

		if (OutHit.GetActor()->IsA(ATarget::StaticClass())) {
			return Cast<ATarget>(OutHit.GetActor());
		}
	}

	return nullptr;
}


