#include "RegularNgonSplineComponent.h"

void URegularNgonSplineComponent::ProceedSpline()
{
	Super::ProceedSpline();

	ClearSplinePoints();

    InitRoundedCornerParam(RoundedCorner);

    TArray<FVector> NgonVertexLocations;
    for (int VertexIndex = 0; VertexIndex < VertexNum; VertexIndex++)
    {
        const float IntervalAngleRad = 2.0f * PI / VertexNum;
        NgonVertexLocations.Add(
            FVector(Radius * cos(VertexIndex * IntervalAngleRad), Radius * sin(VertexIndex * IntervalAngleRad), 0.0f));
    }

    MakeRoundedCornerSpline(NgonVertexLocations, bRoundedCorner, RoundedCorner);
}