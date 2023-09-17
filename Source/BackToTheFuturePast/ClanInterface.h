#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ClanInterface.generated.h"

UENUM(BlueprintType)
enum class EClan : uint8
{
	Pink,
	Blue,
	Green,
	Gold
};

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UClanInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BACKTOTHEFUTUREPAST_API IClanInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "ClanInterface")
	virtual EClan GetClanEnum();
	
	virtual  EClan GetClan() = 0;
	UFUNCTION(BlueprintCallable, Category = "ClanInterface")
	virtual UMaterialInstance* GetMeshMaterialInstance();
};
