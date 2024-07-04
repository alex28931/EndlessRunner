// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSpawnMngr.h"
#include "Logging/StructuredLog.h"

// Sets default values
ALevelSpawnMngr::ALevelSpawnMngr()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelSpawnMngr::BeginPlay()
{
	Super::BeginPlay();
	// Level Pooler Creation
	for (TSubclassOf<ABaseLevel> Level : Levels) 
	{
		for (int i = 0; i < 3; i++)
		{
		ABaseLevel* PoolLevel = GetWorld()->SpawnActor<ABaseLevel>(Level, FVector(0,-2000,0), SpawnRotation);
		LevelPooler.Add(PoolLevel);
		PoolLevel->SetActorHiddenInGame(true);
		PoolLevel->SetActorEnableCollision(false);
		}
	}
	for (TSubclassOf<APowerUp> PowerUp : PowerUps)
	{
		for (int i = 0; i < 30; i++)
		{
			APowerUp* PoolPowerUp = GetWorld()->SpawnActor<APowerUp>(PowerUp, FVector(0, -200, 0), SpawnRotation);
			PowerUpPooler.Add(PoolPowerUp);
			PoolPowerUp->SetActorHiddenInGame(true);
			PoolPowerUp->SetActorEnableCollision(false);
		}
	}
	//Spawn first FourLevel
	SpawnLevel(true);
	SpawnLevel(false);
	SpawnLevel(false);
	SpawnLevel(false);
	
}

// Called every frame
void ALevelSpawnMngr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSpawnMngr::SpawnLevel(bool bIsFirst)
{
	SpawnLocation = FVector(0.0f, 1000.0f, 0.0f);
	SpawnRotation = FRotator(0.0f, 90.0f, 0.0f);
	if (!bIsFirst)
	{
		ABaseLevel* LastLevel = RunTimeLevels.Last();
		SpawnLocation = LastLevel->GetSpawnLocation()->GetComponentTransform().GetTranslation();
	}
	RandomLevelToSpawn = FMath::RandRange(0, LevelPooler.Num() - 1);
	if (LevelPooler[RandomLevelToSpawn]) 
	{
		ABaseLevel* LevelToSpawn = LevelPooler[RandomLevelToSpawn];
		LevelToSpawn->SetActorLocation(SpawnLocation);
		LevelToSpawn->SetActorRotation(SpawnRotation);
		LevelToSpawn->SetActorHiddenInGame(false);
		LevelToSpawn->SetActorEnableCollision(true);
		LevelToSpawn->GetTrigger()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		LevelToSpawn->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &ALevelSpawnMngr::OnOverlapBegin);
		RunTimeLevels.Add(LevelToSpawn);
		LevelPooler.RemoveAt(RandomLevelToSpawn);
			if (RunTimeLevels.Num() > 10)
			{
				ABaseLevel* LevelToDeactivate = RunTimeLevels[0];
				RunTimeLevels.RemoveAt(0);
				LevelPooler.Add(LevelToDeactivate);
				LevelToDeactivate->SetActorHiddenInGame(true);
				LevelToDeactivate->SetActorEnableCollision(false);
				LevelToDeactivate->GetTrigger()->OnComponentBeginOverlap.RemoveDynamic(this, &ALevelSpawnMngr::OnOverlapBegin);
			}
	}
}

void ALevelSpawnMngr::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnLevel(false);
	OverlappedComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

