// Fill out your copyright notice in the Description page of Project Settings.


#include "Generation.h"
#include "ProceduralMeshComponent.h"


// Sets default values
AGeneration::AGeneration()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Привязка меша  (!!!уточнить позднее!!!)
	ProceduralMesh = CreateAbstractDefaultSubobject<UProceduralMeshComponent>("ProceduralMeshComponent");
	ProceduralMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AGeneration::BeginPlay()
{
	Super::BeginPlay();
	// Генерация меша на основе параметров
	//CreateMapVertices(&Vertices);
	//CreateArrTriangles(&Triangles);
	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	ProceduralMesh->SetMaterial(0, Material);//Материал
}

// Called every frame
void AGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

