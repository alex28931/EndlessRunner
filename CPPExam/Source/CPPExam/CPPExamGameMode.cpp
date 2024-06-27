// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPPExamGameMode.h"
#include "CPPExamCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACPPExamGameMode::ACPPExamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
