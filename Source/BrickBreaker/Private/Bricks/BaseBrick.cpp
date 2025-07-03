// Fill out your copyright notice in the Description page of Project Settings.


#include "Bricks/BaseBrick.h"

// Sets default values
ABaseBrick::ABaseBrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called when the game starts or when spawned
void ABaseBrick::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseBrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseBrick::OnPlatformHit_Implementation(int32 Damage)
{
	UE_LOG(LogTemp, Log, TEXT("%s got hit for %d"), *GetName(), Damage);
}

