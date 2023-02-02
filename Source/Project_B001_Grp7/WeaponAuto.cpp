// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_B001_Grp7Character.h"
#include "WeaponAuto.h"


int AWeaponAuto::Shoot(ATarget* Target)
{
	return Target->Hit(Damage);
}

void AWeaponAuto::Shoot(AProject_B001_Grp7Character* Player)
{
	if (Player->AnimInstance == nullptr) return;
	Player->AnimInstance->Montage_Play(Shooting);
	UGameplayStatics::PlaySound2D(Player->GetWorld(), Sound, 100, 1, 1);
	
	ATarget* target = nullptr;

	if (Player->TimerShootCooldown >= ShootCoolDown)
	{
		CurrentAmmo -= 1;
		Player->GetWorld()->SpawnActor<AWeaponParticle>(WeaponParticle, Player->WeaponMesh->GetSocketLocation("BulletStart"), FRotator(0, 0, 0));
		target = Raycast(Player);
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
