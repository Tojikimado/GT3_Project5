// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSemi.h"
#include "Project_B001_Grp7Character.h"

int AWeaponSemi::Shoot(ATarget* Target)
{
	return Target->Hit(Damage);
}

void AWeaponSemi::Shoot(AProject_B001_Grp7Character* Player)
{
	ATarget* target = nullptr;

	if (Player->TimerShootCooldown >= ShootCoolDown)
	{
		CurrentAmmo -= 1;
		target = Raycast(Player);
		Player->Shooting = false;
	}

	if (Player->TimerShootCooldown >= ShootCoolDown) {
		Player->TimerShootCooldown = 0;
		Player->Hud->SetAmmo(CurrentAmmo, AllAmmo);

		if (target) {
			auto earningPoints = Shoot(target);
			Player->Points += earningPoints;
			Player->Money += (earningPoints / 2);
			Player->Hud->SetPointsAndMoney(Player->Points, Player->Money);
		}
	}
}
