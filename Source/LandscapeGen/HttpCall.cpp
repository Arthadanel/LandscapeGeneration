#include "HttpCall.h"

AHttpCall::AHttpCall()
{
	Http = &FHttpModule::Get();
}

void AHttpCall::CreateElevationMap(float x, float y, int sideLength, float dotSpacing, float scaling, float smoothing)
{
	length = sideLength;
	delta = dotSpacing;
	scale = scaling;
	Smoothing = smoothing;
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpCall::OnResponseReceived);
	FString url = FString::Printf(TEXT("https://elevation-api.io/api/elevation?points=(%f,%f),(%f,%f),(%f,%f),(%f,%f)"), x, y, x, y + 0.32, x + 0.32, y, x + 0.32, y + 0.32);
	Request->SetURL(url);
	Request->SetVerb("GET");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void AHttpCall::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	TArray<float> Heightmap;

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		for (size_t i = 0; i < 4; i++)
		{
			TSharedPtr<FJsonObject> elevationObject = JsonObject->GetArrayField("elevations")[i]->AsObject();
			float elevation = elevationObject->GetNumberField("elevation");
			Heightmap.Add(elevation);
		}
	}

	FVector location = this->GetActorLocation();
	FRotator rotate = FRotator(0, 0, 0);
	FActorSpawnParameters SpawnInfo;
	ALandscapeMesh* chunk = GetWorld()->SpawnActor<ALandscapeMesh>(ALandscapeMesh::StaticClass(), location, rotate, SpawnInfo);
	chunk->SetActorScale3D(FVector(scale, scale, scale));
	FString key = chunk->GetActorLocation().ToString();
	chunk->CreateTerrain(FMath::Pow(2, length) + 1, delta, SEED, Smoothing, Heightmap);
}

void AHttpCall::BeginPlay()
{
	Super::BeginPlay();
}

void AHttpCall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

