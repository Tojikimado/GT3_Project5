// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponLaser.h"
#include "Project_B001_Grp7Character.h"
#include "Particles/ParticleSystemComponent.h"

int AWeaponLaser::Shoot(ATarget* Target)
{
	return Target->Hit(Damage * LaserMultiplicator);
}

void AWeaponLaser::Shoot(AProject_B001_Grp7Character* Player)
{
	if (Player->AnimInstance == nullptr) return;
	Player->AnimInstance->Montage_Play(Shooting);
	UGameplayStatics::PlaySound2D(Player->GetWorld(), Sound, 1, 1, 1);
	ATarget* target = nullptr;

	target = Raycast(Player);
	Player->Laser->SetHiddenInGame(false);
	if (Player->TimerShootCooldown >= ShootCoolDown)
	{
		CurrentAmmo -= 5;
		LaserMultiplicator += 1;
	}

	if (Player->TimerShootCooldown >= ShootCoolDown) {
		Player->TimerShootCooldown = 0;
		Player->Hud->SetAmmo(CurrentAmmo, AllAmmo);

		if (target) {
			auto earningPoints = Shoot(target);
			Player->Points += earningPoints;
			Player->Money += (earningPoints / 2);
			Player->Hud->SetPointsAndMoney(Player->Points, Player->Money);

			UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			if (GI)
			{
				GI->Score = Player->Points;
			}
		}
	}
}
