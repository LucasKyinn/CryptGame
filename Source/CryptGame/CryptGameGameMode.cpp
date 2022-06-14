// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptGameGameMode.h"
#include "CryptGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACryptGameGameMode::ACryptGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
