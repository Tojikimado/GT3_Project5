#include "Components/TextRenderComponent.h"
#include "Wall.h"

// Sets default values
AWall::AWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetCollisionProfileName("Trigger");

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWall::OverlapBegin);

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	WallMesh->AttachToComponent(CollisionBox, FAttachmentTransformRules::KeepRelativeTransform);

	PointCostText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PointCostText"));

	PointCostText->AttachToComponent(CollisionBox, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();

	FString textCost = "Points : ";
	textCost.Append(FString::FromInt(Cost));

	PointCostText->SetText(FText::FromString(textCost));
}

void AWall::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->IsA(AProject_B001_Grp7Character::StaticClass())) {

		if (AProject_B001_Grp7Character* Player = Cast<AProject_B001_Grp7Character>(OtherActor)) {
			if (Player->Points >= Cost) {
				K2_DestroyActor();
			}
		}
	}
}