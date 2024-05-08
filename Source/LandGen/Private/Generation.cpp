// Fill out your copyright notice in the Description page of Project Settings.

//Based librarys
#include "Generation.h"
#include "ProceduralMeshComponent.h"
//Debug librarys
#include "DrawDebugHelpers.h"
//Test Librarys
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image-master/stb_image.h>


// Sets default values
AGeneration::AGeneration()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Connection with main component
	ProceduralMesh = CreateAbstractDefaultSubobject<UProceduralMeshComponent>("ProceduralMeshComponent");
	ProceduralMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AGeneration::BeginPlay()
{
	Super::BeginPlay();
	// Generation Mesh
    PngToMatrix();
	GenerationVertices();
	GenerationTriangles();
	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	ProceduralMesh->SetMaterial(0, Material);//Material
}

// Called every frame
void AGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AGeneration::GenerationVertices()// Function generation Vertices
{
    //Normal
    int indexArrayZ = 0;
	for (int i = 0; i >= -XSize; i--)
	{
		for (int j = 0; j <= YSize; j++)
		{
			Vertices.Add({ i*Scale, j*Scale, (float)arrayHeightMap[indexArrayZ] * Scale});// coordinate in space {X,Y,Z} (Vector)
			UV0.Add({ i * UVScale, j * UVScale });
            indexArrayZ++;
		}
	}
    stbi_image_free(arrayHeightMap);
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
            int NextPointY = i * (YSize + 1) + (j + 1); // Next point on axis_Y
            int NextPointXY = (i + 1) * (YSize + 1) + (j + 1); // Next point on axis_XY
			// first  triangles
			Triangles.Add(CurPoint);
			Triangles.Add(NextPointX);
			Triangles.Add(NextPointXY);
			// second Triangles
			Triangles.Add(CurPoint);
			Triangles.Add(NextPointXY);
			Triangles.Add(NextPointY);
		}
	}
	return;
}

void AGeneration::PngToMatrix()//Convert Png to HeightMap
{
    int channels;
    arrayHeightMap = stbi_load(TCHAR_TO_UTF8(*pathFilePng), &XSize, &YSize, &channels, 1);
    XSize--;
    YSize--;
    if (arrayHeightMap)
    {
        UE_LOG(LogTemp, Log, TEXT("Loaded image"));
        UE_LOG(LogTemp, Error, TEXT("Channels: %d"), channels);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Failed to load image")); 
    }
	return;
}


///For Debug...
    //UE_LOG(LogTemp, Log, TEXT("Number to log: %d"), pixel_value);
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is GEngine"));
    //UE_LOG(LogTemp, Warning, TEXT("This is  UE_LOG"), VariableX, VariableY);


    //Debug Sphere
    //DrawDebugSphere(GetWorld(), { i * Scale, j * Scale, 0 }, 10, 12, FColor::Red, false, 60);