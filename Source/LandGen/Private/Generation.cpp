// Fill out your copyright notice in the Description page of Project Settings.


#include "Generation.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AGeneration::AGeneration()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AGeneration::BeginPlay()
{
	Super::BeginPlay();
	//UProceduralMeshComponent ProceduralMesh;
	//ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}

// Called every frame
void AGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

