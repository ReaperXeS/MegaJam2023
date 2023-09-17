// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClanInterface.h"
#include "GameFramework/Actor.h"
#include "RxActor.generated.h"

UCLASS()
class BACKTOTHEFUTUREPAST_API ARxActor : public AActor, public IClanInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARxActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// Clan Id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	EClan Clan = EClan::Pink;

	// Tail Length increase size in centimeters when the player eats an energy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	int32 TailLengthIncreaseSize = 100;

	// RxTrace Actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	TSubclassOf<class ARxTronTrace> RxTronTraceActor;
public:
	/******************************/
	/*	IClanInterface			  */
	/******************************/
	virtual EClan GetClan() override;

	UFUNCTION(BlueprintCallable, Category = "ClanInterface")
	UMaterialInstance* GetMaterialInstance();

};
