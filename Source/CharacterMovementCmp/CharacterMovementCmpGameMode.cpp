// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterMovementCmpGameMode.h"
#include "CharacterMovementCmpCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACharacterMovementCmpGameMode::ACharacterMovementCmpGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
