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

	Laser = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser"));

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

	if (HudClass) {
		APlayerController* PC = GetController<APlayerController>();
		check(PC);
		Hud = CreateWidget<UPlayerHud>(PC, HudClass);
		check(Hud);
		Hud->SetPointsAndMoney(Points, Money);
		Hud->AddToPlayerScreen();
	}

	for (TSubclassOf<AWeaponBase> weapon : MainWeaponArray)
	{
		weapon->GetDefaultObject<AWeaponBase>()->AllAmmo = weapon->GetDefaultObject<AWeaponBase>()->AmmoPerLoader * weapon->GetDefaultObject<AWeaponBase>()->MaxLoader;
		weapon->GetDefaultObject<AWeaponBase>()->CurrentAmmo = weapon->GetDefaultObject<AWeaponBase>()->AmmoPerLoader;
	}

	SetWeapon();
}

void AProject_B001_Grp7Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	WeaponMesh->SetWorldLocation(GetMesh()->GetSocketLocation(MainWeapon->GetDefaultObject<AWeaponBase>()->SocketName));
	WeaponMesh->SetWorldRotation(GetMesh()->GetSocketRotation(MainWeapon->GetDefaultObject<AWeaponBase>()->SocketName));

	Laser->SetHiddenInGame(true);
	if (Shooting && MainWeapon->GetDefaultObject<AWeaponBase>()->CurrentAmmo > 0 && !Reloading) {
		MainWeapon->GetDefaultObject<AWeaponBase>()->Shoot(this);
		if (!CheckAmmo()) {
			Defeat();
		}
	}

	if (Shooting && MainWeapon->GetDefaultObject<AWeaponBase>()->CurrentAmmo <= 0) {
		StartReloading();
	}

	if (TimerShootCooldown < MainWeapon->GetDefaultObject<AWeaponBase>()->ShootCoolDown && !Reloading) {
		TimerShootCooldown += DeltaTime;
	}
}

void AProject_B001_Grp7Character::StartShooting()
{
	if (Reloading) return;
	MainWeapon->GetDefaultObject<AWeaponBase>()->StartShooting(this);
	Shooting = true;
}

void AProject_B001_Grp7Character::EndShooting()
{
	MainWeapon->GetDefaultObject<AWeaponBase>()->EndShooting();
	Shooting = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProject_B001_Grp7Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AProject_B001_Grp7Character::PlayJumpAM);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProject_B001_Grp7Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProject_B001_Grp7Character::Look);

		PlayerInputComponent->BindKey(EKeys::P, IE_Pressed, this, &AProject_B001_Grp7Character::ShowWeaponStat);

		PlayerInputComponent->BindKey(EKeys::R, IE_Pressed, this, &AProject_B001_Grp7Character::StartReloading);

		PlayerInputComponent->BindKey(EKeys::N, IE_Pressed, this, &AProject_B001_Grp7Character::Pause).bExecuteWhenPaused = true;

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
	Reloading = false;
	MainWeapon = MainWeaponArray[ActualWeapon];
	Hud->SetAmmo(MainWeapon->GetDefaultObject<AWeaponBase>()->CurrentAmmo, MainWeapon->GetDefaultObject<AWeaponBase>()->AllAmmo);
	WeaponMesh->SetStaticMesh(MainWeapon->GetDefaultObject<AWeaponBase>()->WeaponMesh);
	WeaponMesh->SetWorldScale3D(MainWeapon->GetDefaultObject<AWeaponBase>()->OffSetScale);
	this->GetMesh()->SetAnimInstanceClass(MainWeapon->GetDefaultObject<AWeaponBase>()->AnimationWeapon->GetAnimBlueprintGeneratedClass());
	AnimInstance = GetMesh()->GetAnimInstance();
}

void AProject_B001_Grp7Character::StartReloading()
{
	if (Reloading) return;
	if (MainWeapon->GetDefaultObject<AWeaponBase>()->AmmoPerLoader == MainWeapon->GetDefaultObject<AWeaponBase>()->CurrentAmmo || MainWeapon->GetDefaultObject<AWeaponBase>()->AllAmmo == 0) return;
	Reloading = true;
	MainWeapon->GetDefaultObject<AWeaponBase>()->EndShooting();
	AnimInstance->Montage_Play(MainWeapon->GetDefaultObject<AWeaponBase>()->Reloading);
}

void AProject_B001_Grp7Character::Pause()
{
	APlayerController* PC = GetController<APlayerController>();
	check(PC);
	if (isPaused) {
		HudPause->UnPauseGame();
		isPaused = false;
	}
	else {
		HudPause = CreateWidget<UPauseMenu>(PC, HudClassPause);
		check(HudPause);
		HudPause->init(this);
		HudPause->AddToPlayerScreen();
		PC->SetPause(true);
		isPaused = true;
		PC->bShowMouseCursor = true;
	}
}

void AProject_B001_Grp7Character::FinishReloading()
{
	if (MainWeapon->GetDefaultObject<AWeaponBase>()->AllAmmo >= (MainWeapon->GetDefaultObject<AWeaponBase>()->AmmoPerLoader - MainWeapon->GetDefaultObject<AWeaponBase>()->CurrentAmmo)) {
		MainWeapon->GetDefaultObject<AWeaponBase>()->AllAmmo = MainWeapon->GetDefaultObject<AWeaponBase>()->AllAmmo - (MainWeapon->GetDefaultObject<AWeaponBase>()->AmmoPerLoader - MainWeapon->GetDefaultObject<AWeaponBase>()->CurrentAmmo);
		MainWeapon->GetDefaultObject<AWeaponBase>()->CurrentAmmo = MainWeapon->GetDefaultObject<AWeaponBase>()->AmmoPerLoader;
	}
	else {
		MainWeapon->GetDefaultObject<AWeaponBase>()->CurrentAmmo = MainWeapon->GetDefaultObject<AWeaponBase>()->AllAmmo;
		MainWeapon->GetDefaultObject<AWeaponBase>()->AllAmmo = 0;
	}

	Hud->SetAmmo(MainWeapon->GetDefaultObject<AWeaponBase>()->CurrentAmmo, MainWeapon->GetDefaultObject<AWeaponBase>()->AllAmmo);

	MainWeapon->GetDefaultObject<AWeaponBase>()->StartShooting(this);
	Reloading = false;;
}

UCameraComponent* AProject_B001_Grp7Character::GetCamera()
{
	return FollowCamera;
}

void AProject_B001_Grp7Character::Defeat()
{
	UEndMenu* ui = CreateWidget<UEndMenu>(GetWorld(), HudEnd);
	ui->SetScore(Points);
	ui->AddToViewport();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
}

void AProject_B001_Grp7Character::PlayJumpAM()
{
	AnimInstance->Montage_Play(JumpAM);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Jump"));
}

bool AProject_B001_Grp7Character::CheckAmmo()
{
	bool ammo = false;

	for (TSubclassOf<AWeaponBase> weapon : MainWeaponArray)
	{
		if (!weapon->GetDefaultObject<AWeaponBase>()->CurrentAmmo == 0 || !weapon->GetDefaultObject<AWeaponBase>()->AllAmmo == 0) {
			ammo = true;
		}
	}

	return ammo;
}