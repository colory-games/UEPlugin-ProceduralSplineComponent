/*!
 * ProceduralSplineComponent
 *
 * Copyright (c) 2022 Colory Games
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/

#include "RegularNgonSplineComponent.h"

void URegularNgonSplineComponent::ProceedSpline()
{
	Super::ProceedSpline();

	ClearSplinePoints();

	InitRoundedCornerParam(RoundedCornerParams);

	TArray<FVector> NgonVertexLocations;
	for (int32 VertexIndex = 0; VertexIndex < VertexNum; VertexIndex++)
	{
		const float IntervalAngleRad = 2.0f * PI / VertexNum;
		NgonVertexLocations.Add(FVector(
			Radius * FMath::Cos(VertexIndex * IntervalAngleRad), Radius * FMath::Sin(VertexIndex * IntervalAngleRad), 0.0f));
	}

	MakeRoundedCornerSpline(NgonVertexLocations, bRoundCorner, RoundedCornerParams);
}