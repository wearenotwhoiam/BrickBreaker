// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BasePaddle.h"
#include "../Balls/BaseBall.h"
#include "PlayerPaddle.generated.h"

class UBoxComponent;
class UDataAsset_InputConfig;
class UFloatingPawnMovement;
struct FInputActionValue;

UCLASS()
class BRICKBREAKER_API APlayerPaddle : public ABasePaddle
{
	GENERATED_BODY()

public:
	APlayerPaddle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UFloatingPawnMovement* FloatingMovement;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

#pragma region Components

	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh{ NULL };

	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComp{ NULL };
#pragma endregion

#pragma region Input
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset{ NULL };

	void Move (const FInputActionValue& InputActionValue);
#pragma endregion
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Balls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* BallSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Balls", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABaseBall> BallClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Balls", meta = (AllowPrivateAccess = "true"))

		
	TArray<ABaseBall*> BallAmmo;

	void SpawnProjectile();
	void LaunchProjectile();
};
