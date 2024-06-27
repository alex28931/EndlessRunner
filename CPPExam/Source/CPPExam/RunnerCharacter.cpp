// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Engine.h"

// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 90.f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Side View Camera"));
	SideViewCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->JumpZVelocity = 1000.0f;
	GetCharacterMovement()->GroundFriction = 3.0;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	tempPos = GetActorLocation();
	zPosition = tempPos.Z + 300.0f;
}


void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARunnerCharacter::OnOverlapBegin);
	bCanMove = true;
}

// Called every frame
void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	tempPos = GetActorLocation();
	tempPos.X -= 850.0f;
	tempPos.Z = zPosition;
	SideViewCamera->SetWorldLocation(tempPos);
}

// Called to bind functionality to input
void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveRight", this, &ARunnerCharacter::MoveRight);
}

void ARunnerCharacter::MoveRight(float value)
{
	if (bCanMove) 
	{
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), value);
	}
}

void ARunnerCharacter::Death()
{
	GetMesh()->SetCollisionProfileName(FName("Ragdoll"),true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetAnimInstanceClass(nullptr);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bCanMove = false;

	FTimerHandle TimerForRestartLevel;
	GetWorldTimerManager().SetTimer(TimerForRestartLevel, this, &ARunnerCharacter::RestartLevel, 2.0f, false);

}

void ARunnerCharacter::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(GetWorld()->GetName()));
}

void ARunnerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{
		if (OtherActor->ActorHasTag(FName("Spike"))) 
		{
			FVector impulse = GetActorLocation() - OtherActor->GetActorLocation();
			impulse.Z = 0.0f;
			impulse.X = 0.0f;
			impulse.Normalize();
			impulse += GetActorUpVector();
			impulse.Normalize();
			impulse *= 1000.0f;
			LaunchCharacter(impulse,true,true);
			GetCapsuleComponent()->OnComponentBeginOverlap.RemoveDynamic(this, &ARunnerCharacter::OnOverlapBegin);
			FTimerHandle TimerForRestartLevel;
			GetWorldTimerManager().SetTimer(TimerForRestartLevel, this, &ARunnerCharacter::Death, 0.3f, false);
		}
	}
}

