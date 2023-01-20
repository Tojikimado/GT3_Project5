// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupWeapon.h"

// Sets default values
APickupWeapon::APickupWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetCollisionProfileName("Trigger");

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APickupWeapon::OverlapBegin);

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	WeaponMesh->AttachToComponent(CollisionBox, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APickupWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupWeapon::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Main Weapon : "));
	if (OtherActor->IsA(AProject_B001_Grp7Character::StaticClass())) {
		if (AProject_B001_Grp7Character* Player = Cast<AProject_B001_Grp7Character>(OtherActor)) {
			if (Player->Money >= Cost) {
				Player->MainWeaponArray.Add(Weapon);
				Player->Money -= Cost;
				K2_DestroyActor();
			}
		}

	}
}

