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
	for (TSubclassOf<ABaseLevel> level : Levels) 
	{
		for (int i = 0; i < 3; i++)
		{
		ABaseLevel* poolLevel = GetWorld()->SpawnActor<ABaseLevel>(level, FVector(0,-200,0), spawnRotation);
		levelPooler.Add(poolLevel);
		poolLevel->SetActorHiddenInGame(true);
		poolLevel->SetActorEnableCollision(false);
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
	spawnLocation = FVector(0.0f, 1000.0f, 0.0f);
	spawnRotation = FRotator(0.0f, 90.0f, 0.0f);
	if (!bIsFirst)
	{
		ABaseLevel* lastLevel = runTimeLevels.Last();
		spawnLocation = lastLevel->GetSpawnLocation()->GetComponentTransform().GetTranslation();
	}
	randomLevelToSpawn = FMath::RandRange(0, levelPooler.Num() - 1);
	if (levelPooler[randomLevelToSpawn]) 
	{
		ABaseLevel* levelToSpawn = levelPooler[randomLevelToSpawn];
		levelToSpawn->SetActorLocation(spawnLocation);
		levelToSpawn->SetActorRotation(spawnRotation);
		levelToSpawn->SetActorHiddenInGame(false);
		levelToSpawn->SetActorEnableCollision(true);
		levelToSpawn->GetTrigger()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		levelToSpawn->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &ALevelSpawnMngr::OnOverlapBegin);
		runTimeLevels.Add(levelToSpawn);
		levelPooler.RemoveAt(randomLevelToSpawn);
			if (runTimeLevels.Num() > 10)
			{
				ABaseLevel* levelToDeactivate = runTimeLevels[0];
				runTimeLevels.RemoveAt(0);
				levelPooler.Add(levelToDeactivate);
				levelToDeactivate->SetActorHiddenInGame(true);
				levelToDeactivate->SetActorEnableCollision(false);
				levelToDeactivate->GetTrigger()->OnComponentBeginOverlap.RemoveDynamic(this, &ALevelSpawnMngr::OnOverlapBegin);
			}
	}
}

void ALevelSpawnMngr::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnLevel(false);
	OverlappedComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

