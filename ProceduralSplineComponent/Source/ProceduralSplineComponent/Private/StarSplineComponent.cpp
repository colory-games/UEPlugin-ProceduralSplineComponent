/*!
 * ProceduralSplineComponent
 *
 * Copyright (c) 2022 Colory Games
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/

#include "StarSplineComponent.h"

void UStarSplineComponent::ProceedSpline()
{
	Super::ProceedSpline();

	ClearSplinePoints();

	InitRoundedCornerParam(RoundedCornerParams);

	TArray<FVector> StarVertexLocations;
	const int PointNum = Ngram * 2;
	for (int32 PointIndex = 0; PointIndex < PointNum; PointIndex++)
	{
		const float Radius = (PointIndex % 2 == 0) ? OuterRadius : InnerRadius;
		FVector Location = FVector(Radius * FMath::Cos((float) PointIndex / PointNum * 2.0 * PI),
			-Radius * FMath::Sin((float) PointIndex / PointNum * 2.0 * PI), 0.0f);
		StarVertexLocations.Add(Location);
	}

	MakeRoundedCornerSpline(StarVertexLocations, bRoundCorner, RoundedCornerParams);

	SetClosedLoop(true, false);

	UpdateSpline();
}