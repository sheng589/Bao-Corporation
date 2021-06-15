// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaoCorporationGameMode.h"
#include "BaoCorporationCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABaoCorporationGameMode::ABaoCorporationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
