/*!
 * ProceduralSplineComponent
 *
 * Copyright (c) 2022 Colory Games
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "CircleSplineComponent.h"

void UCircleSplineComponent::ProceedSpline()
{
	Super::ProceedSpline();

	ClearSplinePoints();

	for (int32 PointIndex = 0; PointIndex < PointNum; PointIndex++)
	{
		FVector Location = FVector(Radius * FMath::Sin((float) PointIndex / PointNum * 2.0 * PI),
			Radius * FMath::Cos((float) PointIndex / PointNum * 2.0 * PI), 0.0f);
		AddSplinePointAtIndex(Location, PointIndex, ESplineCoordinateSpace::Local, false);
		SetSplinePointType(PointIndex, ESplinePointType::Curve, false);
	}

	SetClosedLoop(true, false);

	UpdateSpline();
}