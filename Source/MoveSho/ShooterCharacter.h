// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ShooterCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class MOVESHO_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();
	virtual void Jump() override;
	virtual void Fire();
	

protected:
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* ShooterCharacterMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* AimAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* AimActionStop;

	/** Randomized gunshot sound cue*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AlllowPrivateAccess = "true"))
		class USoundCue* FireSound;

	/** Flash spawned at gun_barrel*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AlllowPrivateAccess = "true"))
	class UParticleSystem* MuzzleFlash;

	/** Montage For Firing the Weapon*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AlllowPrivateAccess = "true"))
	class UAnimMontage* HipFireMontage;

	/** Particles spawned upon bullet impact*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AlllowPrivateAccess = "true"))
	UParticleSystem* ImpactParticles;


	/** True when aiming*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AlllowPrivateAccess = "true"))
	bool bAiming;

	

	/* Aim component for crosshairs*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crosshairs, meta = (AlllowPrivateAccess = "true"))
	float CrosshairAimFactor;

	/* Shooting component for crosshairs*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crosshairs, meta = (AlllowPrivateAccess = "true"))
	float CrosshairShootingFactor;



	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

	/** Set Aiming true or false with button press */
	void AimingButtonPressed();
	void AimingButtonReleased();

	void CameraInterpZoom(float DeltaTime);

	void CalculateCrosshairSpread(float DeltaTime);
	/** Interp speed for zooming in when aiming */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AlllowPrivateAccess = "true"))
		float ZoomInterpSPeed;

	/** Determines the spread of the crosshiars*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crosshairs, meta = (AlllowPrivateAccess = "true"))
		float CrosshairSpreadMultiplier;

	/* Velocity component for crosshairs*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crosshairs, meta = (AlllowPrivateAccess = "true"))
		float CrosshairVelocityFactor;

	/* In air component for crosshairs*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crosshairs, meta = (AlllowPrivateAccess = "true"))
		float CrosshairInAirFactor;

	float ShootTimeDuration;
	bool bFiringBullet;
	FTimerHandle CrosshairShootTimer;

	void StartCrosshairBulletFire();

	UFUNCTION()
	void FinishCrosshairbulletFire();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	FORCEINLINE bool GetAiming() const { return bAiming; }

	UFUNCTION(BlueprintCallable)
	float GetCrosshairSpreadMultiplier() const;

private:

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AlllowPrivateAccess = "true"))
	float  HipTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AlllowPrivateAccess = "true"))
	float HipLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AlllowPrivateAccess = "true"))
	float AimingTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AlllowPrivateAccess = "true"))
	float AimingLookUpRate;*/
	/** Default camera field of view value*/
	float CameraDefaultFOV;

	float CameraZoomedFOV;

	float CameraCurrentFOV;


};
