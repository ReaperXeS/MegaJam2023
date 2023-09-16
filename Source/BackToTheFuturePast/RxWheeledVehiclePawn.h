// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "ClanInterface.h"
#include "RxWheeledVehiclePawn.generated.h"

/**
 * 
 */
UCLASS()
class BACKTOTHEFUTUREPAST_API ARxWheeledVehiclePawn : public AWheeledVehiclePawn, public IClanInterface
{
	GENERATED_BODY()
	
protected:
	// Clan Id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	EClan Clan = EClan::Pink;

public:
	/******************************/
	/*	IClanInterface			  */
	/******************************/
	virtual EClan GetClan() override;
	
};
