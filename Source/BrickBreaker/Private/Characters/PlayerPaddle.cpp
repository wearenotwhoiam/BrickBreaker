// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerPaddle.h"
#include "Components/BoxComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Input/PlayerPaddleInputComponent.h"
#include "PlayerPaddleGameplayTags.h"
#include "InputActionValue.h"
#include "GameFramework/FloatingPawnMovement.h"  

#include "DebugHelper.h"

APlayerPaddle::APlayerPaddle()
{

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxComp;
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetCollisionObjectType(ECC_Pawn);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Block);


	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(BoxComp);

	BallSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Ball Spawn Point"));
	BallSpawnPoint->SetupAttachment(BoxComp);

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	FloatingMovement->UpdatedComponent = RootComponent;
}

void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();
	Debug::Print("PLAAAAAY");
}


void APlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Valid data asset not assigned as input config"));
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	UPlayerPaddleInputComponent* PaddleInputComp = CastChecked<UPlayerPaddleInputComponent>(PlayerInputComponent);
	
	PaddleInputComp->BindNativeInputAction(InputConfigDataAsset, PlayerPaddleGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
	PaddleInputComp->BindNativeInputAction(InputConfigDataAsset, PlayerPaddleGameplayTags::InputTag_SpawnProjectile, ETriggerEvent::Completed, this, &ThisClass::SpawnProjectile);
	PaddleInputComp->BindNativeInputAction(InputConfigDataAsset, PlayerPaddleGameplayTags::InputTag_LaunchProjectile, ETriggerEvent::Completed, this, &ThisClass::LaunchProjectile);
}


void APlayerPaddle::Tick(float DeltaTime)
{

}

void APlayerPaddle::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (MovementVector.Y != 0.f)
	{
		AddMovementInput(FVector::RightVector, MovementVector.Y);
	}
}

//Spawns the projectiles
//Always from center on top - if you have multiple ammo they add themselves in line from there using the center line as the split point
//Start with X, as you launch they reduce
//Can add more ammo so would need to spawn again

//AddAmmo(AmmoType)
//SpawnProjectile(AmmotType)
//LaunchProjectile() - reduce ammo
//SwitchProjectile() - swap current ammo type

//When the levelbegins - add X starting ammo - Spawn all ammo
//

void APlayerPaddle::SpawnProjectile()
{
	FVector BallSpawnLocation = GetActorLocation() + GetActorUpVector() * 10.f;
	FRotator SpawnRotation = GetActorRotation();

	//GetWorld()->SpawnActor<ABaseBall>(BallClass, BallSpawnLocation, SpawnRotation);
	ABaseBall* Ball = GetWorld()->SpawnActor<ABaseBall>(BallClass, BallSpawnLocation, SpawnRotation);
	if (!Ball) return;
	Ball->SetOwner(this);
	BallAmmo.Add(Ball);
	Debug::Print("Spaaawn");

}
void APlayerPaddle::LaunchProjectile()
{
	if (BallAmmo.Num() <= 0)
	{
		Debug::Print("No Ammo");
		return;
	}
	Debug::Print("Launch");
	
	BallAmmo[0]->LaunchBall(GetActorUpVector(), 500.f);
}
