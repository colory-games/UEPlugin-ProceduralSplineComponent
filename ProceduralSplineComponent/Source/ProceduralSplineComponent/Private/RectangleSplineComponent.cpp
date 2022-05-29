#include "RectangleSplineComponent.h"

void URectangleSplineComponent::ProceedSpline()
{
	Super::ProceedSpline();

	ClearSplinePoints();

	if (bSquare)
	{
		Length = Width;
	}
	InitRoundedCornerParam(RoundedCornerParam);

	TArray<FVector> SquareVertexLocations;
	SquareVertexLocations.SetNum(4);
	SquareVertexLocations[0] = FVector(Width / 2.0f, Length / 2.0f, 0.0f);
	SquareVertexLocations[1] = FVector(Width / 2.0f, -Length / 2.0f, 0.0f);
	SquareVertexLocations[2] = FVector(-Width / 2.0f, -Length / 2.0f, 0.0f);
	SquareVertexLocations[3] = FVector(-Width / 2.0f, Length / 2.0f, 0.0f);

	MakeRoundedCornerSpline(SquareVertexLocations, bRoundCorner, RoundedCornerParam);
}