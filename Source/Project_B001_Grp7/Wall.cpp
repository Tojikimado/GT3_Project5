// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetCollisionProfileName("Trigger");

	CollisionBox->AttachToComponent(WallMesh, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWall::OverlapBegin);

	PointCostText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PointCostText"));

	PointCostText->AttachToComponent(WallMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
	FString textCost = "Points : ";
	textCost.Append(FString::FromInt(Cost));

	PointCostText->SetText(FText::FromString(textCost));
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AProject_B001_Grp7Character::StaticClass())) {

		if (AProject_B001_Grp7Character* Player = Cast<AProject_B001_Grp7Character>(OtherActor)) {
			if (Player->Points >= Cost && !Player->InZone) {
				K2_DestroyActor();
			}
		}
	}
}


