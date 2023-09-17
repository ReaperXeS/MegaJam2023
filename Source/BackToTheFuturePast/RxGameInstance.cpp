// Fill out your copyright notice in the Description page of Project Settings.


#include "RxGameInstance.h"

#include "RxSaveGame.h"
#include "Kismet/GameplayStatics.h"

void URxGameInstance::Init()
{
	Super::Init();

	// Create Player Score Data	
	CurrentPlayerScore.PlayerName = "Player"; // TODO: Should be the player name?
    CurrentPlayerScore.PlayerScore = 0;

	// Validate Save Game Exists
	if (UGameplayStatics::DoesSaveGameExist(SaveGameSlotName, 0))
	{
		// Yes, Load Save Game and apply to World
		LoadedSaveGame = Cast<URxSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameSlotName, 0));
		if (LoadedSaveGame)
		{
			// Nothing to do for now
		}
	}

	// Create Save Game if it doesn't exist
	if (LoadedSaveGame == nullptr)
	{		
		LoadedSaveGame = Cast<URxSaveGame>(UGameplayStatics::CreateSaveGameObject(URxSaveGame::StaticClass()));
	}
}

FRxSaveGameData URxGameInstance::GetCurrentPlayerScore()
{
	return CurrentPlayerScore;
}

void URxGameInstance::AddPlayerScore(const int32 IncrementScore)
{
	CurrentPlayerScore.PlayerScore += IncrementScore;
	CurrentPlayerScore.ScoreDate = FDateTime::Now();
}

void URxGameInstance::UpdatePlayerName(FString NewPlayerName)
{
	CurrentPlayerScore.PlayerName = NewPlayerName;
}

void URxGameInstance::SavePlayerScore()
{
	// Validate High Scores and Save if necessary
	if (LoadedSaveGame->HighScores.Num() == 0)
	{
		LoadedSaveGame->HighScores.Add(CurrentPlayerScore);
	}
	else
	{
		// Find the index of the first score that is less than the current player score
		for (int32 i = 0; i < LoadedSaveGame->HighScores.Num(); i++)
		{
			if (LoadedSaveGame->HighScores[i].PlayerScore < CurrentPlayerScore.PlayerScore)
			{
				// Insert the current player score at the index
				LoadedSaveGame->HighScores.Insert(CurrentPlayerScore, i);
				break;
			}
		}
		// Keeper only top 10
		if (LoadedSaveGame->HighScores.Num() > 10)
		{
			LoadedSaveGame->HighScores.RemoveAt(10);
		}
	}
	
	UGameplayStatics::SaveGameToSlot(LoadedSaveGame, SaveGameSlotName, 0);
}
