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

UINTERFACE(MinimalAPI)
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
	virtual EClan GetClan() = 0;
	virtual TObjectPtr<UMaterialInstance> GetMeshMaterialInstance();
};
