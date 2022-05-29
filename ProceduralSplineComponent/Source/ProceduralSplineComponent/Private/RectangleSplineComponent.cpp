#include "RectangleSplineComponent.h"

void URectangleSplineComponent::ProceedSpline()
{
	Super::ProceedSpline();

	ClearSplinePoints();

	if (bSquare)
	{
		Length = Width;
	}
	InitRoundedCornerParam(RoundedCornerParams);

	TArray<FVector> SquareVertexLocations;
	SquareVertexLocations.Add(FVector(Width / 2.0f, Length / 2.0f, 0.0f));
	SquareVertexLocations.Add(FVector(Width / 2.0f, -Length / 2.0f, 0.0f));
	SquareVertexLocations.Add(FVector(-Width / 2.0f, -Length / 2.0f, 0.0f));
	SquareVertexLocations.Add(FVector(-Width / 2.0f, Length / 2.0f, 0.0f));

	MakeRoundedCornerSpline(SquareVertexLocations, bRoundCorner, RoundedCornerParams);
}