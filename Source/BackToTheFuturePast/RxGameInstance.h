// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RxSaveGame.h"
#include "Engine/GameInstance.h"
#include "RxGameInstance.generated.h"

class URxSaveGame;
/**
 * 
 */
UCLASS()
class BACKTOTHEFUTUREPAST_API URxGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	virtual void Init() override;
	
	// Game Scores
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RxGameInstance")
	FRxSaveGameData CurrentPlayerScore;

	// Loaded Save Game, kept in memory for the duration of the game instance
	UPROPERTY(BlueprintReadOnly, Category = "RxGameInstance")
	URxSaveGame* LoadedSaveGame;

	// Const for Save Game Slot Name
	const FString SaveGameSlotName = "SaveGame";

	// Current Player Clan
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RxGameInstance")
	EClan CurrentPlayerClan;
	
public:
	// Getter for Current Player Score
	UFUNCTION(BlueprintCallable, Category = "RxGameInstance")
	FRxSaveGameData GetCurrentPlayerScore();

	// Update Current Player Score
	UFUNCTION(BlueprintCallable, Category = "RxGameInstance")
	void AddPlayerScore(int32 IncrementScore);

	// Update Player Name
	UFUNCTION(BlueprintCallable, Category = "RxGameInstance")
	void UpdatePlayerName(FString NewPlayerName);

	// Update Player Clan
	UFUNCTION(BlueprintCallable, Category = "RxGameInstance")
	void UpdatePlayerClan(EClan NewPlayerClan);

	// Save Player Score to High Scores
	UFUNCTION(BlueprintCallable, Category = "RxGameInstance")
	void SavePlayerScore();
	
};
