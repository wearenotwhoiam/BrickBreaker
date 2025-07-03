// Fill out your copyright notice in the Description page of Project Settings.


#include "Playfields/StaticPlayfield.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStaticPlayfield::AStaticPlayfield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetupPlayfield();
}

void AStaticPlayfield::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UpdatePlayfield();
}
// Called when the game starts or when spawned
void AStaticPlayfield::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(this, 0.0f);
	}
}

// Called every frame
void AStaticPlayfield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStaticPlayfield::SetupPlayfield()
{
	////Floor&Wall Meshes
	FloorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	RootComponent = FloorMeshComp;
	LeftWallComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftWallMesh"));
	LeftWallComp->SetupAttachment(RootComponent);
	RightWallComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWallMesh"));
	RightWallComp->SetupAttachment(RootComponent);
	TopWallComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopWallComp"));
	TopWallComp->SetupAttachment(RootComponent);

	//Setup Camera
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->bUsePawnControlRotation = true;

	//StaticCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("StaticCamera"));
	//StaticCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//StaticCamera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		FloorMeshComp->SetStaticMesh(CubeMesh.Object);
		LeftWallComp->SetStaticMesh(CubeMesh.Object);
		RightWallComp->SetStaticMesh(CubeMesh.Object);
		TopWallComp->SetStaticMesh(CubeMesh.Object);
	}

	if (FloorBaseMesh)
		FloorMeshComp->SetStaticMesh(FloorBaseMesh);
	if (WallBaseMesh)
	{
		LeftWallComp->SetStaticMesh(WallBaseMesh);
		RightWallComp->SetStaticMesh(WallBaseMesh);
		TopWallComp->SetStaticMesh(WallBaseMesh);
	}
	////Wall Collision
	LeftWallComp->SetCollisionProfileName(TEXT("BlockAll"));
	RightWallComp->SetCollisionProfileName(TEXT("BlockAll"));
	TopWallComp->SetCollisionProfileName(TEXT("BlockAll"));

}

void AStaticPlayfield::SetupWalls()
{
#if 1
	if (!FloorMeshComp || !FloorMeshComp->GetStaticMesh()) return;

	const FVector FloorSize = FloorMeshComp->GetStaticMesh()->GetBounds().GetBox().GetSize();
	const FVector WorldFloorScale = FloorMeshComp->GetComponentScale();
	const FVector WorldFloorExtent = FloorSize * WorldFloorScale * 0.5f;
	const float ZOffset = BaseWallHeight / 2;

	const FVector WallMeshSize = LeftWallComp->GetStaticMesh()->GetBounds().GetBox().GetSize();

	const FVector TopScale = FVector(FloorWidth / WallMeshSize.X, BaseWallThickness / WallMeshSize.Y, BaseWallHeight / WallMeshSize.Z);
	const FVector WallScale = FVector(BaseWallThickness / WallMeshSize.X, FloorHeight / WallMeshSize.Y, BaseWallHeight / WallMeshSize.Z);
	TopWallComp->SetWorldScale3D(TopScale);
	LeftWallComp->SetWorldScale3D(WallScale);
	RightWallComp->SetWorldScale3D(WallScale);

	const FVector FloorCenter = FloorMeshComp->GetComponentLocation();
	const FRotator FloorRot = FloorMeshComp->GetComponentRotation();

	// Calculate relative positions in local space, then transform to world space
	const FVector TopWallLocalPos = FVector(0.f, WorldFloorExtent.Y + BaseWallThickness * 0.5f, ZOffset);
	const FVector LeftWallLocalPos = FVector(WorldFloorExtent.X + BaseWallThickness * 0.5f, 0.f, ZOffset);
	const FVector RightWallLocalPos = FVector(-WorldFloorExtent.X - BaseWallThickness * 0.5f, 0.f, ZOffset);

	// Transform local positions to world space using floor's rotation
	const FVector TopWallWorldPos = FloorCenter + FloorRot.RotateVector(TopWallLocalPos);
	const FVector LeftWallWorldPos = FloorCenter + FloorRot.RotateVector(LeftWallLocalPos);
	const FVector RightWallWorldPos = FloorCenter + FloorRot.RotateVector(RightWallLocalPos);

	TopWallComp->SetWorldLocation(TopWallWorldPos);
	LeftWallComp->SetWorldLocation(LeftWallWorldPos);
	RightWallComp->SetWorldLocation(RightWallWorldPos);

	TopWallComp->SetWorldRotation(FloorRot);
	LeftWallComp->SetWorldRotation(FloorRot);
	RightWallComp->SetWorldRotation(FloorRot);
#endif	
}

void AStaticPlayfield::UpdatePlayfield()
{
	if (!FloorMeshComp || !FloorMeshComp->GetStaticMesh()) return;

	const FVector FloorBaseSize = FloorMeshComp->GetStaticMesh()->GetBounds().GetBox().GetSize();

	FVector NewScale = FVector(FloorWidth / FloorBaseSize.X, FloorHeight / FloorBaseSize.Y, 0.05f);
	FloorMeshComp->SetWorldScale3D(NewScale);

	SetupWalls();
}
