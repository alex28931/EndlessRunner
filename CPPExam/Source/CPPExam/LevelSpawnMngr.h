// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseLevel.h"
#include "PowerUp.h"
#include "GameFramework/Actor.h"
#include "LevelSpawnMngr.generated.h"

UCLASS()
class CPPEXAM_API ALevelSpawnMngr : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelSpawnMngr();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnLevel(bool bIsFirst);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<TSubclassOf<ABaseLevel>> Levels;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<APowerUp>> PowerUps;

	TArray<ABaseLevel*> LevelPooler;

	TArray<APowerUp*> PowerUpPooler;

	TArray<ABaseLevel*> RunTimeLevels;

	TArray<APowerUp*> RunTimePowerUp;
	
	int32 RandomLevelToSpawn;

	FVector SpawnLocation = FVector();
	FRotator SpawnRotation = FRotator();
	FActorSpawnParameters SpawnInfo = FActorSpawnParameters();
};
