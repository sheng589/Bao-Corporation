// Copyright Epic Games, Inc. All Rights Reserved.

#include "BaoCorporationGameMode.h"
#include "BaoCorporationCharacter.h"

ABaoCorporationGameMode::ABaoCorporationGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ABaoCorporationCharacter::StaticClass();	
}
