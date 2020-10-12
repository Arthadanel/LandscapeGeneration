#include "LandscapeMesh.h"
#include "DiamondSquareAlgorithm.h"
#include "UObject/ConstructorHelpers.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Sets default values
ALandscapeMesh::ALandscapeMesh()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	mesh->bUseAsyncCooking = true;
	material = CreateDefaultSubobject<UMaterial>(TEXT("GeneratedMaterial"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/M_LandscapeColor'"));
	if (Material.Object != NULL)
		material = (UMaterial*)Material.Object;
}

void ALandscapeMesh::BeginPlay()
{
	Super::BeginPlay();
}

void ALandscapeMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALandscapeMesh::CreateTerrain(int Length, int Delta, int seed, float smoothing, TArray<float>& corners)
{
	TArray<FVector> vertices;
	TArray<int32> Triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;

	TArray<float> hm = DiamondSquareAlgorithm::CreateHeightmap(Length, smoothing, corners, seed);

	float maxH = MIN_flt;

	//Fill vertices array
	for (int i = 0; i < Length * Length; i++)
	{
		if (hm[i] > maxH) maxH = hm[i];
		vertices.Add(FVector(Delta * (i % Length), Delta * (i / Length), hm[i]));
	}

	//Fill triangles array
	for (int i = 0; i < Length * (Length - 1); i++)
	{
		if (i % Length == 0)
		{
			Triangles.Add(i);
			Triangles.Add(i + Length);
			Triangles.Add(i + 1);
		}
		else if (i % Length == Length - 1)
		{
			Triangles.Add(i);
			Triangles.Add(i + Length - 1);
			Triangles.Add(i + Length);
		}
		else
		{
			Triangles.Add(i);
			Triangles.Add(i + Length - 1);
			Triangles.Add(i + Length);

			Triangles.Add(i);
			Triangles.Add(i + Length);
			Triangles.Add(i + 1);
		}
	}

	TArray<FLinearColor> vertexColors;

	for (int i = 0; i < Length * Length; i++)
	{
		float height = maxH;
		if (hm[i] == 0)
		{
			vertexColors.Add(FLinearColor(0.01, 0.01, 0.1));
		}
		else if ((hm[i] == height * 0.2))
		{
			vertexColors.Add(FLinearColor(0.03, 0.02, 0));
		}
		else if (hm[i] > height * 0.85)
		{
			vertexColors.Add(FLinearColor(0.03, 0.02, 0.01));
		}
		else
		{
			vertexColors.Add(FLinearColor(0, 0.05, 0));
		}
	}
	mesh->CreateMeshSection_LinearColor(1, vertices, Triangles, normals, UV0, vertexColors, tangents, true);
	mesh->SetMaterial(1, material);
}