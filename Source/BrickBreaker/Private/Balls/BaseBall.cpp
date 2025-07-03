// Fill out your copyright notice in the Description page of Project Settings.


#include "Balls/BaseBall.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/Gameplaystatics.h"
#include "DebugHelper.h"

// Sets default values
ABaseBall::ABaseBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	CollisionComp->InitSphereRadius(5.75f);                          
	CollisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	CollisionComp->SetNotifyRigidBodyCollision(true);               
	RootComponent = CollisionComp;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BallMesh->SetupAttachment(CollisionComp);
	BallMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.9f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	ProjectileMovement->bConstrainToPlane = true;
	ProjectileMovement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::X);

	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ABaseBall::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}


// Called every frame
void ABaseBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBall::LaunchBall(const FVector& Direction, float Speed)
{
	if (!ProjectileMovement) return;

	ProjectileMovement->Velocity = Direction.GetSafeNormal() * Speed;
	ProjectileMovement->Activate(true);
}

void ABaseBall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner{ GetOwner() };
	if (!MyOwner) return;
	auto MyOwnerInstigator{ MyOwner->GetInstigatorController() };
	auto DamageType = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageType);
	}
}
