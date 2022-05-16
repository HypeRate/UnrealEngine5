// Copyright Epic Games, Inc. All Rights Reserved.

#include "HypeRateUE5GameMode.h"
#include "HypeRateUE5Character.h"
#include "UObject/ConstructorHelpers.h"

AHypeRateUE5GameMode::AHypeRateUE5GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
