#pragma once

#include "CoreMinimal.h"
#include "Math/RandomStream.h"

class LANDSCAPEGEN_API DiamondSquareAlgorithm
{
private:
	static void diamondStep(int side, int step, int x, float deviation, TArray<float>& hm);
	static void squareStep(int side, int step, int x, float deviation, TArray<float>& hm);
public:
	DiamondSquareAlgorithm();
	~DiamondSquareAlgorithm();
	static TArray<float> CreateHeightmap(int side, float smoothing, TArray<float> corners, int seed);
};