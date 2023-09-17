// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClanInterface.h"
#include "GameFramework/Actor.h"
#include "RxTronTrace.generated.h"

UCLASS()
class BACKTOTHEFUTUREPAST_API ARxTronTrace : public AActor, public IClanInterface
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ARxTronTrace();

private:
	// Spacing between each mesh (bounding box size + offset)
	float CalculatedSpacing = 0.0f;

	// Life Span Timer Handle
	FTimerHandle TimerHandle;

	// Accumulated time since last spawn point
	float AccumulatedTimeSinceLastSpawn = 0.0f;

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void DestroyPointOnTrace();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	// Spline Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	class USplineComponent* SplineComponent;

	// Instanced Static Mesh Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	class UInstancedStaticMeshComponent* InstancedStaticMeshComponent;

	// Spline Mesh Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	TArray<class USplineMeshComponent*> SplineMeshComponents;

	// Mesh offset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	float MeshOffset = 0.0f;

	// Clan Id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	EClan Clan = EClan::Pink;

	// Life Span of the trace
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	float LifeSpan = 2.0f;

	// Delay for destroying the trace after the initial LifeSpan
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RxTronTrace")
	float DelayDestroyInstance = 0.2f;

	// Spawn Point Frequency (in seconds), if 0 then it will not spawn points at all
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "RxTronTrace")
	float SpawnPointFrequency = 0.0f;

	// Owner relative transform for Spawn Point
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "RxTronTrace")
	FTransform SpawnPointRelativeTransformToOwner;

	// Spawn Scene Component of the Owner
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "RxTronTrace")
	class USceneComponent* SpawnSceneComponent;

	// Maximum Lenght of the Spline in Centimeters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "RxTronTrace")
	float MaxSplineLenght = 1000.0f;

	// Mesh to use for the trace
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "RxTronTrace")
	class UStaticMesh* TraceMesh;

	// Boolean to kill other clan only or everything
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "RxTronTrace")
	bool bKillOtherClanOnly = true;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/******************************/
	/*	IClanInterface			  */
	/******************************/
	virtual EClan GetClan() override;

};
