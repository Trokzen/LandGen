// Fill out your copyright notice in the Description page of Project Settings.


#include "Generation.h"
#include "ProceduralMeshComponent.h"

//#include "FreeImage/Source/FreeImage.h"
#include <FreeImage/FreeImage-3.18.0/Source/FreeImage.h>

#include "DrawDebugHelpers.h"


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
	GenerationVertices();
	GenerationTriangles();
	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	ProceduralMesh->SetMaterial(0, Material);//Material
	PngToMatrix();//"height.png",5,10
	
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

void AGeneration::PngToMatrix()//Convert Png to HeightMap
{
	// Initializing the FreeImage library
	FreeImage_Initialise(true);
	// Download image
	FIBITMAP* image = FreeImage_Load(FIF_PNG, "monochrome_image.png", PNG_DEFAULT);

	if (image) {
		// get size image
		int width = FreeImage_GetWidth(image);
		int height = FreeImage_GetHeight(image);

		// Get value of pixel
		int x = 50;
		int y = 50;   

		RGBQUAD pixel;
		FreeImage_GetPixelColor(image, x, y, &pixel);

		// The pixel value is the brightness component (R, G, B are the same for monochrome)
		unsigned char pixel_value = pixel.rgbRed;

		FString ValueAsString = FString::Printf(TEXT("Value: %d"), pixel_value);
		//FString ValueString = FString()
		
		GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Yellow, ValueAsString);

		// Freeing memory after use
		FreeImage_Unload(image);
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Failed to load image"));
	}

	// Completing the FreeImage Library
	FreeImage_DeInitialise();

	return;
	//UE_LOG(LogTemp, Log, TEXT("Number to log: %d"), pixel_value);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is GEngine"));
	//UE_LOG(LogTemp, Warning, TEXT("This is  UE_LOG"), VariableX, VariableY);

}