// Fill out your copyright notice in the Description page of Project Settings.


#include "RxTronTrace.h"

#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARxTronTrace::ARxTronTrace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Spline Component
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponent;

	// Instanced Static Mesh Component
	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	InstancedStaticMeshComponent->SetupAttachment(RootComponent);
	InstancedStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InstancedStaticMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InstancedStaticMeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	InstancedStaticMeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
}

void ARxTronTrace::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("ARxTronTrace::OnOverlapBegin"));
	if (IClanInterface* OtherActorClan = Cast<IClanInterface>(OtherActor); OtherActorClan != nullptr && (!bKillOtherClanOnly || OtherActorClan->GetClan() != GetClan()))
	{
		// Destroy the other actor
		OtherActor->Destroy();
	}
}

void ARxTronTrace::DestroyPointOnTrace()
{
	UE_LOG(LogTemp, Warning, TEXT("ARxTronTrace::DestroyPointOnTrace"));
	if (InstancedStaticMeshComponent->GetInstanceCount() > 0)
	{
		// Remove the first instance
		InstancedStaticMeshComponent->RemoveInstance(0);
	}

	if (InstancedStaticMeshComponent->GetInstanceCount() == 0)
	{
		// Destroy the actor
		Destroy();
	} else
	{
		// Next timer to destroy the next point on the trace it runs faster
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ARxTronTrace::DestroyPointOnTrace, DelayDestroyInstance, false);
	}
}

// Called when the game starts or when spawned
void ARxTronTrace::BeginPlay()
{
	Super::BeginPlay();

	InstancedStaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ARxTronTrace::OnOverlapBegin);

	// Create a timer to destroy the trace
	if (LifeSpan > 0.0f)
	{
		// GetWorldTimerManager().SetTimer(TimerHandle, this, &ARxTronTrace::DestroyPointOnTrace, LifeSpan, false);
	}
}

void ARxTronTrace::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (IsValid(InstancedStaticMeshComponent->GetStaticMesh()))
	{
		// Set Material Instance
		InstancedStaticMeshComponent->SetMaterial(0, GetMeshMaterialInstance());
		InstancedStaticMeshComponent->ClearInstances();
		SplineMeshComponents.Empty();
		const auto VectorDiff = InstancedStaticMeshComponent->GetStaticMesh()->GetBoundingBox().Max - InstancedStaticMeshComponent->GetStaticMesh()->GetBoundingBox().Min;
		CalculatedSpacing = VectorDiff.X + MeshOffset;
		const int32 NumberOfInstances = SplineComponent->GetSplineLength() / CalculatedSpacing;

		// Loop through spline points and instance mesh
		for (int32 i = 0; i < NumberOfInstances; i++)
		{
			// Get location and rotation at spline point			
			const auto StartLocation = SplineComponent->GetLocationAtDistanceAlongSpline(i * CalculatedSpacing, ESplineCoordinateSpace::Local);
			const auto StartRotation = SplineComponent->GetRotationAtDistanceAlongSpline(i * CalculatedSpacing, ESplineCoordinateSpace::Local);

			// Add instance to InstancedStaticMeshComponent
			InstancedStaticMeshComponent->AddInstance(FTransform(StartRotation, StartLocation, FVector(1.0f)));

			// Create Spline Mesh Component
			// const auto StartLocation = SplineComponent->GetLocationAtDistanceAlongSpline(i * CalculatedSpacing, ESplineCoordinateSpace::World);
			// const auto StartTangent = SplineComponent->GetTangentAtDistanceAlongSpline(i * CalculatedSpacing, ESplineCoordinateSpace::World);
			// const auto EndLocation = SplineComponent->GetLocationAtDistanceAlongSpline((i + 1) * CalculatedSpacing, ESplineCoordinateSpace::World);
			// const auto EndTangent = SplineComponent->GetTangentAtDistanceAlongSpline((i + 1) * CalculatedSpacing, ESplineCoordinateSpace::World);
			
			// USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
			// SplineMeshComponents.Add(SplineMesh);
			// SplineMesh->SetMobility(EComponentMobility::Movable);
			// SplineMesh->SetStaticMesh(TraceMesh);
			// SplineMesh->SetStartAndEnd(StartLocation, StartTangent, EndLocation, EndTangent);					
		}
	}
}

// Called every frame
void ARxTronTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Accumulate time
	AccumulatedTimeSinceLastSpawn += DeltaTime;
	if (SpawnSceneComponent && SpawnPointFrequency > 0.f && AccumulatedTimeSinceLastSpawn > SpawnPointFrequency)
	{
		AccumulatedTimeSinceLastSpawn = 0.0f;
		// Spawn a point where at the location of the owner
		SplineComponent->AddSplinePoint(SpawnSceneComponent->GetComponentLocation(), ESplineCoordinateSpace::World);

		// Validate if we need to instance a new mesh
		const int32 NumberOfInstances = SplineComponent->GetSplineLength() / CalculatedSpacing;
		
		for (int32 i = InstancedStaticMeshComponent->GetInstanceCount(); i <= NumberOfInstances; i++)
		{
			// Get location and rotation at spline point
			const auto Location = SplineComponent->GetLocationAtDistanceAlongSpline(i * CalculatedSpacing, ESplineCoordinateSpace::Local);
			const auto Rotation = SplineComponent->GetRotationAtDistanceAlongSpline(i * CalculatedSpacing, ESplineCoordinateSpace::Local);

			// Add instance to InstancedStaticMeshComponent
			InstancedStaticMeshComponent->AddInstance(FTransform(Rotation, Location, FVector(1.0f)));
		}
	}

	bool bRemovedPoints = false;
	// Validate if we need to reduce length of spline
	while (MaxSplineLenght > 0.f && SplineComponent->GetSplineLength() > MaxSplineLenght)
	{
		// Reduce the length of the spline
		SplineComponent->RemoveSplinePoint(0, true);
		bRemovedPoints = true;
	}

	if (bRemovedPoints)
	{
		const int32 NumberOfInstances = SplineComponent->GetSplineLength() / CalculatedSpacing;
		while (NumberOfInstances < InstancedStaticMeshComponent->GetInstanceCount())
		{
			// Remove the 1st instance
			InstancedStaticMeshComponent->RemoveInstance(0);
		}
	}
}

EClan ARxTronTrace::GetClan()
{
	return Clan;
}

