// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSpawnMngr.h"
#include "Logging/StructuredLog.h"

// Sets default values
ALevelSpawnMngr::ALevelSpawnMngr()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelSpawnMngr::BeginPlay()
{
	Super::BeginPlay();
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
	RandomLevelToSpawn = FMath::RandRange(0, Levels.Num() - 1);
	if (Levels[RandomLevelToSpawn]) 
	{
		ABaseLevel* LevelToSpawn = GetWorld()->SpawnActor<ABaseLevel>(Levels[RandomLevelToSpawn], SpawnLocation, SpawnRotation);
		LevelToSpawn->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &ALevelSpawnMngr::OnOverlapBegin);
		RunTimeLevels.Add(LevelToSpawn);
			if (RunTimeLevels.Num() > 10)
			{
				ABaseLevel* LevelToDestroy = RunTimeLevels[0];
				RunTimeLevels.RemoveAt(0);
				LevelToDestroy->Destroy();
			}
	}
}

void ALevelSpawnMngr::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnLevel(false);
	OverlappedComp->DestroyComponent();
}

