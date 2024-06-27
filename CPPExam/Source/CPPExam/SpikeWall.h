// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spike.h"
#include "SpikeWall.generated.h"

/**
 * 
 */
UCLASS()
class CPPEXAM_API ASpikeWall : public ASpike
{
	GENERATED_BODY()

public:

	ASpikeWall();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	
};
