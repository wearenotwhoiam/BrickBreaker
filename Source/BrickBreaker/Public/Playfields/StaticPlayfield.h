// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticPlayfield.generated.h"

class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class BRICKBREAKER_API AStaticPlayfield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStaticPlayfield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SetupPlayfield();
	void SetupWalls();
	UFUNCTION(BlueprintCallable)
	void UpdatePlayfield();


#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* StaticCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

#pragma region PlayfieldComponents
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FloorMeshComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* FloorBaseMesh{ NULL };
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* WallBaseMesh{ NULL };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWallComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWallComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TopWallComp;
#pragma endregion

#pragma endregion

#pragma region Dimensions
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayfieldDimensions", meta = (AllowPrivateAccess = "true"))
float FloorWidth{ 50.0f };
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayfieldDimensions", meta = (AllowPrivateAccess = "true"))
float FloorHeight{ 100.0f };
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayfieldDimensions", meta = (AllowPrivateAccess = "true"))
float BaseWallHeight{ 50.f };
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayfieldDimensions", meta = (AllowPrivateAccess = "true"))
float BaseWallThickness{ 10.f };
#pragma endregion

};
