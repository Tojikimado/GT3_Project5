// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_B001_Grp7Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DrawDebugHelpers.h"
#include "Target.h"

//////////////////////////////////////////////////////////////////////////
// AProject_B001_Grp7Character

AProject_B001_Grp7Character::AProject_B001_Grp7Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);

	this->SetActorTickEnabled(true);
}

void AProject_B001_Grp7Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	SetWeapon();
}

void AProject_B001_Grp7Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	WeaponMesh->SetWorldLocation(GetMesh()->GetSocketLocation(MainWeapon->GetDefaultObject<AWeaponBase>()->SocketName));
	WeaponMesh->SetWorldRotation(GetMesh()->GetSocketRotation(MainWeapon->GetDefaultObject<AWeaponBase>()->SocketName));

	if (Shooting && TimerShootCooldown >= MainWeapon->GetDefaultObject<AWeaponBase>()->ShootCoolDown) {
		Shoot();
	}

	if (TimerShootCooldown < MainWeapon->GetDefaultObject<AWeaponBase>()->ShootCoolDown) {
		TimerShootCooldown += DeltaTime;
	}
}

void AProject_B001_Grp7Character::StartShooting()
{
	Shooting = true;
}

void AProject_B001_Grp7Character::EndShooting()
{
	Shooting = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProject_B001_Grp7Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProject_B001_Grp7Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProject_B001_Grp7Character::Look);

		PlayerInputComponent->BindKey(EKeys::P, IE_Pressed, this, &AProject_B001_Grp7Character::ShowWeaponStat);

		PlayerInputComponent->BindAxis("Wheel", this, &AProject_B001_Grp7Character::SwitchWeapon);

		PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AProject_B001_Grp7Character::StartShooting);
		PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AProject_B001_Grp7Character::EndShooting);
	}

}

void AProject_B001_Grp7Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AProject_B001_Grp7Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AProject_B001_Grp7Character::ShowWeaponStat()
{
	if (MainWeapon->GetDefaultObject()->IsA(AWeaponBase::StaticClass())) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("----------------------------------------------------------------------------------"));

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("CurrentAmmo : %lld"), MainWeapon->GetDefaultObject<AWeaponBase>()->CurrentAmmo));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("CurrentAmmo : %lld"), MainWeapon->GetDefaultObject<AWeaponBase>()->AllAmmo));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("CurrentAmmo : %lld"), MainWeapon->GetDefaultObject<AWeaponBase>()->Damage));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Main Weapon : "));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("----------------------------------------------------------------------------------"));
	}


	for (auto& weapon : MainWeaponArray)
	{
		if (MainWeapon->GetDefaultObject()->IsA(AWeaponBase::StaticClass())) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("----------------------------------------------------------------------------------"));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("CurrentAmmo : %lld"), weapon->GetDefaultObject<AWeaponBase>()->CurrentAmmo));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("CurrentAmmo : %lld"), weapon->GetDefaultObject<AWeaponBase>()->AllAmmo));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("CurrentAmmo : %lld"), weapon->GetDefaultObject<AWeaponBase>()->Damage));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("----------------------------------------------------------------------------------"));
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("All Weapons : "));
}

void AProject_B001_Grp7Character::SwitchWeapon(float Scroll)
{
	if (Scroll > 0) {
		if (MainWeaponArray.IsValidIndex(ActualWeapon - 1)) {
			ActualWeapon -= 1;
			SetWeapon();
		}
	}
	else if (Scroll < 0) {
		if (MainWeaponArray.IsValidIndex(ActualWeapon + 1)) {
			ActualWeapon += 1;
			SetWeapon();
		}
	}
}

void AProject_B001_Grp7Character::SetWeapon()
{
	MainWeapon = MainWeaponArray[ActualWeapon];
	WeaponMesh->SetStaticMesh(MainWeapon->GetDefaultObject<AWeaponBase>()->WeaponMesh);
	WeaponMesh->SetWorldScale3D(MainWeapon->GetDefaultObject<AWeaponBase>()->OffSetScale);

	this->GetMesh()->SetAnimInstanceClass(MainWeapon->GetDefaultObject<AWeaponBase>()->AnimationWeapon->GetAnimBlueprintGeneratedClass());
}

void AProject_B001_Grp7Character::Shoot() 
{
	TimerShootCooldown = 0;
	switch (MainWeapon->GetDefaultObject<AWeaponBase>()->WeaponType)
	{
	case EnumWeaponType::AUTO:
		Raycast();
		break;
	case EnumWeaponType::SEMIAUTO:
		Raycast();
		Shooting = false;
		break;
	case EnumWeaponType::LASER:
		Raycast();
		break;
	}
}

void AProject_B001_Grp7Character::Raycast()
{
	FHitResult OutHit;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	FVector Start = WeaponMesh->GetComponentLocation();
	FVector ForwardVector = WeaponMesh->GetForwardVector();

	Start = Start + (ForwardVector);

	FVector End = Start + (ForwardVector * 5000.0f);

	//Draw Ray
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	bool IsHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

	if (IsHit) {

		if (OutHit.GetActor()->IsA(ATarget::StaticClass())) {

			Points += MainWeapon->GetDefaultObject<AWeaponBase>()->Shoot(Cast<ATarget>(OutHit.GetActor()));

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Points : %lld"), Points));
		}
	}
}
