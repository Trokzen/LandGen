// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerationOnTypeLandscape.h"
//Library
#include "Landscape.h"
#include "LandscapeComponent.h"
#include "LandscapeInfo.h"
#include "LandscapeDataAccess.h"

#include "Engine/World.h"
// Sets default values
AGenerationOnTypeLandscape::AGenerationOnTypeLandscape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGenerationOnTypeLandscape::BeginPlay()
{
    Super::BeginPlay();
    GenerateLandscape();
}

// Called every frame
void AGenerationOnTypeLandscape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGenerationOnTypeLandscape::GenerateLandscape()
{
    // Параметры ландшафта
    int32 Width = 63;  // Ширина в вертексах - 1
    int32 Height = 63;  // Высота в вертексах - 1
    float Scale = 100.0f;
    FVector Location(0.0f, 0.0f, 0.0f);
    FRotator Rotation(0.0f, 0.0f, 0.0f);
    FVector Scale3D(100.0f, 100.0f, 100.0f);

    // Создаем данные высот
    TArray<uint16> HeightData;
    HeightData.SetNum((Width + 1) * (Height + 1));

    for (int32 y = 0; y <= Height; y++)
    {
        for (int32 x = 0; x <= Width; x++)
        {
            float HeightValue = 0;// PerlinNoise::Noise(x * 0.1f, y * 0.1f)* Scale;
            HeightData[x + y * (Width + 1)] = FMath::Clamp(HeightValue, 0.0f, 255.0f) * 256.0f;
        }
    }

    // Параметры ландшафта
    int32 SectionSize = 63; // Размер секции (в вершинах)
    int32 NumSections = 1;  // Количество секций на компонент
    int32 ComponentsPerProxy = 1; // Количество компонентов на прокси
    int32 NumQuads = SectionSize * NumSections; // Общее количество квадратов на компонент

    // Создаем новый ландшафт
    ALandscape* Landscape = GetWorld()->SpawnActor<ALandscape>(Location, Rotation);
    Landscape->SetActorRelativeScale3D(Scale3D);

    // Создаем компоненты ландшафта
    TArray<ULandscapeComponent*> LandscapeComponents;
    for (int32 ComponentY = 0; ComponentY < ComponentsPerProxy; ComponentY++)
    {
        for (int32 ComponentX = 0; ComponentX < ComponentsPerProxy; ComponentX++)
        {
            // Создаем и инициализируем компонент
            ULandscapeComponent* LandscapeComponent = NewObject<ULandscapeComponent>(Landscape);
            LandscapeComponent->SetSectionBase(FIntPoint(ComponentX * NumQuads, ComponentY * NumQuads));
            LandscapeComponent->SetRelativeLocation(FVector(ComponentX * NumQuads, ComponentY * NumQuads, 0));
            LandscapeComponent->SetupAttachment(Landscape->GetRootComponent());

            // Заполняем данные высот
            TArray<uint16> ComponentHeightData;
            ComponentHeightData.SetNum((SectionSize + 1) * (SectionSize + 1));
            for (int32 y = 0; y <= SectionSize; y++)
            {
                for (int32 x = 0; x <= SectionSize; x++)
                {
                    int32 LandscapeX = ComponentX * SectionSize + x;
                    int32 LandscapeY = ComponentY * SectionSize + y;
                    ComponentHeightData[x + y * (SectionSize + 1)] = HeightData[LandscapeX + LandscapeY * (Width + 1)];
                }
            }

            // Инициализируем компонент данными высот
            LandscapeComponent->Init(SectionSize, ComponentHeightData);
            LandscapeComponents.Add(LandscapeComponent);
        }
    }

    Landscape->PostEditChange();
}
