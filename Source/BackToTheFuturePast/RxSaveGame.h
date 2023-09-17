// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RxSaveGame.generated.h"


USTRUCT(BlueprintType)
struct FRxSaveGameData
{
	GENERATED_BODY()

	// Player Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	FString PlayerName;

	// Player Score
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	int32 PlayerScore;

	// Score Date
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	FDateTime ScoreDate;
};
/**
 * 
 */
UCLASS()
class BACKTOTHEFUTUREPAST_API URxSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	// Top 10 High Scores
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RxTronTrace")
	TArray<FRxSaveGameData> HighScores;
};
