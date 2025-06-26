// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerPaddle.h"
#include "Components/BoxComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Input/PlayerPaddleInputComponent.h"
#include "PlayerPaddleGameplayTags.h"
#include "InputActionValue.h"

#include "DebugHelper.h"

APlayerPaddle::APlayerPaddle()
{

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(BoxComp);
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
	
	PaddleInputComp->BindNativeInputAction(InputConfigDataAsset, PlayerPaddleGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
}


void APlayerPaddle::Tick(float DeltaTime)
{

}

void APlayerPaddle::Input_Move(const FInputActionValue& InputActionValue)
{

	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	Debug::Print(MovementVector.ToString());

	if (MovementVector.Y != 0.f)
	{
		Debug::Print("PMoooove");

		FVector DeltaLocation = FVector::ZeroVector;

		DeltaLocation.Y = 2 * MovementVector.Y;
		AddActorLocalOffset(DeltaLocation);
	}
}
