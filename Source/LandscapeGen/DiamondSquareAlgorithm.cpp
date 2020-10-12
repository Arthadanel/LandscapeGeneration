#include "DiamondSquareAlgorithm.h"

void DiamondSquareAlgorithm::squareStep(int side, int step, int x, float deviation, TArray<float>& hm)
{
	int count = 4;

	int leftUpper = x;
	int rightUpper = x + step;
	int leftLower = x + step * side;
	int rightLower = x + step * side + step;
	int center = x + step / 2 + step / 2 * side;

	if (leftUpper<0 || leftUpper>side * side) {
		leftUpper = side * side;
		count--;
	}
	if (rightUpper<0 || rightUpper>side * side) {
		rightUpper = side * side;
		count--;
	}
	if (leftLower<0 || leftLower>side * side) {
		leftLower = side * side;
		count--;
	}
	if (rightLower<0 || rightLower>side * side) {
		rightLower = side * side;
		count--;
	}

	float avg = (hm[leftUpper] + hm[rightUpper] + hm[leftLower] + hm[rightLower]) / count;
	float result = avg <= 0 ? 0 : avg + deviation;
	hm[center] = result <= 0 ? 0 : result;
}

void DiamondSquareAlgorithm::diamondStep(int side, int step, int x, float deviation, TArray<float>& hm)
{
	int count = 4;

	int top = x + step / 2;
	int left = x + step / 2 * side;
	int right = x + step / 2 * side + step;
	int bottom = x + step / 2 + step * side;
	int center = x + (step / 2) + ((step / 2) * side);

	if (top<0 || top>side * side) {
		top = side * side;
		count--;
	}
	if (left<0 || left>side * side || (left % side > top % side)) {
		left = side * side;
		count--;
	}
	if (right<0 || right>side * side || (right % side < top % side)) {
		right = side * side;
		count--;
	}
	if (bottom<0 || bottom>side * side) {
		bottom = side * side;
		count--;
	}

	float avg = (hm[top] + hm[left] + hm[right] + hm[bottom]) / count;
	float result = avg <= 0 ? 0 : avg + deviation;
	hm[center] = result <= 0 ? 0 : result;
}

TArray<float> DiamondSquareAlgorithm::CreateHeightmap(int side, float smoothing, TArray<float> corners, int seed)
{
	FRandomStream rs(seed);

	TArray<float> hm;
	for (int i = 0; i <= side * side; i++)
	{
		hm.Add(0);
	}

	hm[0] = corners[0];
	hm[side - 1] = corners[1];
	hm[(side - 1) * side] = corners[2];
	hm[side * side - 1] = corners[3];

	int step = side - 1;
	int x = 0;

	while (step > 1)
	{
		x = 0;
		while (x < side * side - step - side * (step - 1))
		{
			float deviation = ((rs.FRand() * step * 2) - step) / smoothing;

			squareStep(side, step, x, deviation, hm);
			diamondStep(side, step, x - side * (step / 2), deviation, hm);
			diamondStep(side, step, x - step / 2, deviation, hm);
			diamondStep(side, step, x + step / 2, deviation, hm);
			diamondStep(side, step, x + side * step / 2, deviation, hm);
			x += step;
			if (x % side == side - 1)
				x += 1 + side * (step - 1);
		}
		step /= 2;
	}
	rs.Reset();
	return hm;
}

DiamondSquareAlgorithm::DiamondSquareAlgorithm()
{
}

DiamondSquareAlgorithm::~DiamondSquareAlgorithm()
{
}