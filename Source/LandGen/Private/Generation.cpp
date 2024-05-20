// Fill out your copyright notice in the Description page of Project Settings.


#include "Generation.h"
#include "ProceduralMeshComponent.h"
#include "DrawDebugHelpers.h"
//#include "libPNG/libPNG-1.5.2/png.h"
//#include "FreeImage/Source/FreeImage.h"

// Sets default values
AGeneration::AGeneration()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Привязка меша  (!!!уточнить позднее!!!)
	ProceduralMesh = CreateAbstractDefaultSubobject<UProceduralMeshComponent>("ProceduralMeshComponent");
	ProceduralMesh->SetupAttachment(GetRootComponent());

	PngToMatrix();
}

// Called when the game starts or when spawned
void AGeneration::BeginPlay()
{
	Super::BeginPlay();
	// Генерация меша на основе параметров
	GenerationVertices();
	GenerationTriangles();
	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	ProceduralMesh->SetMaterial(0, Material);//Материал
	
}

// Called every frame
void AGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AGeneration::GenerationVertices()// Function generation Vertices
{
	for (int i = 0; i <= XSize; i++)
	{
		for (int j = 0; j <= YSize; j++)
		{
			//here will function Z = Random([Zmin,Zmax]);
			Vertices.Add({ i*Scale, j*Scale, 0 });// coordinate in space {X,Y,Z} (Vector)
			UV0.Add({ i * UVScale, j * UVScale });
			//Debug Sphere
			//DrawDebugSphere(GetWorld(), { i * Scale, j * Scale, 0 }, 10, 12, FColor::Red, false, 60);

		}
	}
	return ;
}

void AGeneration::GenerationTriangles()// Function generation Triangles
{
	for (int i = 0; i < XSize; i++) // Generation Landscape
	{
		for (int j = 0; j < YSize; j++) // Generation Square
		{
			int CurPoint = i * (YSize + 1) + j; //Current point
			int NextPointX = (i + 1) * (YSize + 1) + j; // Next point on axis_X
			// first  triangles
			Triangles.Add(CurPoint);
			Triangles.Add(CurPoint + 1);
			Triangles.Add(NextPointX);
			// second Triangles
			Triangles.Add(CurPoint+1);
			Triangles.Add(NextPointX + 1);
			Triangles.Add(NextPointX);
		}
	}
	return;
}

void AGeneration::PngToMatrix()//test git
{

	return;
}