// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "WeaponBase.h"
#include "PlayerHUD.h"
#include "Animation/AnimInstance.h"
#include "PauseMenu.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Target.h"
#include "EndMenu.h"
#include "Project_B001_Grp7Character.generated.h"


UCLASS(config = Game)
class AProject_B001_Grp7Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

public:
	AProject_B001_Grp7Character();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void ShowWeaponStat();

	void SwitchWeapon(float Scroll);

	void SetWeapon();



protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay() override;

	int ActualWeapon = 0;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AWeaponBase> MainWeapon;

	UPROPERTY(BlueprintReadWrite)
		bool Reloading;

	UPROPERTY(EditAnywhere)
		class TSubclassOf<class UEndMenu> HudEnd;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartShooting();

	void EndShooting();

	void StartReloading();

	bool CheckAmmo();

	void Pause();

	UFUNCTION(BlueprintCallable)
		void FinishReloading();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	bool isPaused = false;

	int Points = 0;

	int Money = 0;

	float TimerShootCooldown;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AWeaponBase>> MainWeaponArray;

	UPROPERTY(BlueprintReadWrite)
		bool Shooting = false;

	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UPlayerHud> HudClass;

	UPROPERTY()
		class UPlayerHud* Hud;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UPauseMenu> HudClassPause;

	UPROPERTY()
		class UPauseMenu* HudPause;	

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Laser;

	UAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* JumpAM;

	void PlayJumpAM();

	UCameraComponent* GetCamera();
};

