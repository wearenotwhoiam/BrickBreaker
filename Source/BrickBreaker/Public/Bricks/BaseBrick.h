// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/OnHitInterface.h"

#include "BaseBrick.generated.h"

UCLASS()
class BRICKBREAKER_API ABaseBrick : public AActor, public IOnHitInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBrick();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnPlatformHit_Implementation(int32 Damage) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh{ NULL };

};
