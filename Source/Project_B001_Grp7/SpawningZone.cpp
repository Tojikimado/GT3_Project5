// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningZone.h"
// Sets default values
ASpawningZone::ASpawningZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetCollisionProfileName("Trigger");

	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASpawningZone::OverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ASpawningZone::OverlapEnd);

	HudClass = nullptr;
	Hud = nullptr;

	this->SetActorTickEnabled(true);
}

// Called when the game starts or when spawned
void ASpawningZone::BeginPlay()
{
	Super::BeginPlay();
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

void ASpawningZone::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AProject_B001_Grp7Character::StaticClass()) && started != true) {
		started = true;
		timerTimer = Timer;

		if (Cast<AProject_B001_Grp7Character>(OtherActor)->IsLocallyControlled() && HudClass) {
			APlayerController* PC = Cast<AProject_B001_Grp7Character>(OtherActor)->GetController<APlayerController>();
			check(PC);
			Hud = CreateWidget<UZoneHUD>(PC, HudClass);
			check(Hud);
			Hud->Init();
			Hud->AddToPlayerScreen();
		}
	}
}

void ASpawningZone::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called every frame
void ASpawningZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (started) {
		

		timerSpawn += DeltaTime;

		if (timerSpawn > SpawnCooldown && SpawnCooldown > 0.0f) {
			timerSpawn = 0.0f;
			CollisionBox->GetLocalBounds().BoxExtent;

			float X = FMath::RandRange(-((float)(CollisionBox->GetLocalBounds().BoxExtent.X) / 2), (float)(CollisionBox->GetLocalBounds().BoxExtent.X) / 2) + GetActorLocation().X;
			float Y = FMath::RandRange(-((float)(CollisionBox->GetLocalBounds().BoxExtent.Y) / 2), (float)(CollisionBox->GetLocalBounds().BoxExtent.Y) / 2) + GetActorLocation().Y;

			GetWorld()->SpawnActor<ATarget>(TargetToSpawn, FVector(X, Y, CollisionBox->GetLocalBounds().BoxExtent.Z), FRotator(0, 0, 0), SpawnInfo);
		}

		timerTimer -= DeltaTime;

		Hud->SetTimer(timerTimer, Timer);

		if (timerTimer <= 0.0f) {
			started = false;
			Hud->RemoveFromParent();
		}

	}



}
