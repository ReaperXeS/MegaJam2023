#include "RxActor.h"

#include "RxTronTrace.h"

ARxActor::ARxActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ARxActor::BeginPlay()
{
	Super::BeginPlay();
}

EClan ARxActor::GetClan()
{
	return Clan;
}

UMaterialInstance* ARxActor::GetMaterialInstance()
{
	return IClanInterface::GetMeshMaterialInstance();
}

