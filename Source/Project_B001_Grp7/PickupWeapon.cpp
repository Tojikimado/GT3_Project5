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

	PointCostText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PointCostText"));

	PointCostText->AttachToComponent(WeaponMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APickupWeapon::BeginPlay()
{
	Super::BeginPlay();

	FString textCost = "Money : ";
	textCost.Append(FString::FromInt(Cost));

	PointCostText->SetText(FText::FromString(textCost));
}

// Called every frame
void APickupWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PointCostText->SetWorldRotation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation() + FRotator(0.0f, 180.0f, 0.0f));
	Float(DeltaTime);
}

void APickupWeapon::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->IsA(AProject_B001_Grp7Character::StaticClass())) {
		if (AProject_B001_Grp7Character* Player = Cast<AProject_B001_Grp7Character>(OtherActor)) {
			if (Player->Money >= Cost) {
				Player->MainWeaponArray.Add(Weapon);
				Player->Money -= Cost;
				Player->Hud->SetPointsAndMoney(Player->Points, Player->Money);
				K2_DestroyActor();
			}
		}

	}
}

void APickupWeapon::Float(float DeltaTime)
{
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * floatSpeed;       //Scale our height by a factor of 20
	float DeltaRotation = DeltaTime * rotateSpeed;    //Rotate by 20 degrees per second
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
}
