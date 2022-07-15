/*!
 * ProceduralSplineComponent
 *
 * Copyright (c) 2022 Colory Games
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "SpringSplineComponent.h"

void USpringSplineComponent::ProceedSpline()
{
	Super::ProceedSpline();

	ClearSplinePoints();

	for (int32 PointIndex = 0; PointIndex < PointNum; PointIndex++)
	{
		const float PointIndexRatio = (float) PointIndex / (PointNum - 1);
		FVector Location = FVector(Radius * FMath::Sin(PointIndexRatio * TurnNum * 2.0 * PI),
			Radius * FMath::Cos(PointIndexRatio * TurnNum * 2.0 * PI), FMath::Lerp<float>(0.0, Height, PointIndexRatio));
		AddSplinePointAtIndex(Location, PointIndex, ESplineCoordinateSpace::Local, false);
		if (PointIndex == 0 || PointIndex == PointNum - 1)
		{
			SetSplinePointType(PointIndex, ESplinePointType::CurveClamped, false);
		}
		else
		{
			SetSplinePointType(PointIndex, ESplinePointType::Curve, false);
		}
	}

	SetClosedLoop(false, false);

	UpdateSpline();
}