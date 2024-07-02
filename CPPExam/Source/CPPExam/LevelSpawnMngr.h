// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseLevel.h"
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
	TArray<TSubclassOf<ABaseLevel>> levels;

	TArray<ABaseLevel*> levelPooler;

	TArray<ABaseLevel*> runTimeLevels;
	
	int randomLevelToSpawn;

	FVector spawnLocation = FVector();
	FRotator spawnRotation = FRotator();
	FActorSpawnParameters spawnInfo = FActorSpawnParameters();
};
