// Fill out your copyright notice in the Description page of Project Settings.


#include "Playfields/StaticPlayfield.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AStaticPlayfield::AStaticPlayfield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(BoxComp);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.f;

	StaticCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("StaticCamera"));
	StaticCamera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void AStaticPlayfield::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStaticPlayfield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

