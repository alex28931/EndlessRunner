// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeWall.h"

ASpikeWall::ASpikeWall()
{
	PrimaryActorTick.bCanEverTick = true;
	Speed = 450.0f;
}

void ASpikeWall::BeginPlay()
{
	Super::BeginPlay();
	this->GetRootComponent()->ComponentVelocity = FVector(0, 25, 0);
	FTimerHandle TimerToSetVelocity;
	GetWorldTimerManager().SetTimer(TimerToSetVelocity, this, &ASpikeWall::IncrementSpeed, 30.0f, true);
}

void ASpikeWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + FVector(0, Speed * DeltaTime, 0), true);
}

void ASpikeWall::IncrementSpeed()
{
	Speed += 10;
}
