#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "LandscapeMesh.generated.h"

UCLASS()
class LANDSCAPEGEN_API ALandscapeMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALandscapeMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateTerrain(int Length, int Delta, int seed, float smoothing, TArray<float>& corners);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UProceduralMeshComponent* mesh;
	UPROPERTY(EditAnywhere)
		UMaterial* material;

};