#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Map.h"
#include <Http.h>
#include "LandscapeMesh.h"
#include "HttpCall.generated.h"

UCLASS()
class LANDSCAPEGEN_API AHttpCall : public AActor
{
	GENERATED_BODY()

public:
	AHttpCall();

	UFUNCTION(BlueprintCallable, Category = "My Functions")
		void CreateElevationMap(float x, float y, int sideLength, float dotSpacing, float scaling, float smoothing);

	FHttpModule* Http;

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
		int SEED = 521434;
	UPROPERTY(EditAnywhere)
		int length = 11;
	UPROPERTY(EditAnywhere)
		int delta = 1;
	UPROPERTY(EditAnywhere)
		float scale = 1;
	UPROPERTY(EditAnywhere)
		float Smoothing = 8;

};
