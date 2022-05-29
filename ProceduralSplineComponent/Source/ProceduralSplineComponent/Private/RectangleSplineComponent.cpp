#include "RectangleSplineComponent.h"

void URectangleSplineComponent::ProceedSpline()
{
	Super::ProceedSpline();

	ClearSplinePoints();

    if (bSquare) {
        Length = Width;
    }
    InitRoundedCornerParam(RoundedCornerParam);

    const TArray<FVector> SquareVertexLocations
    {
        FVector(Width / 2.0f, Length / 2.0f, 0.0f),
        FVector(Width / 2.0f, -Length / 2.0f, 0.0f),
        FVector(-Width / 2.0f, -Length / 2.0f, 0.0f),
        FVector(-Width / 2.0f, Length / 2.0f, 0.0f)
    };

	MakeRoundedCornerSpline(SquareVertexLocations, bRoundedCorner, RoundedCornerParam);
}