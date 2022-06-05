#include "EllipseSplineComponent.h"

void UEllipseSplineComponent::ProceedSpline()
{
	Super::ProceedSpline();

	ClearSplinePoints();

	for (int32 PointIndex = 0; PointIndex < PointNum; PointIndex++)
	{
		FVector Location = FVector(Width / 2.0f * FMath::Sin((float) PointIndex / PointNum * 2.0 * PI),
			Length / 2.0f * FMath::Cos((float) PointIndex / PointNum * 2.0 * PI), 0.0f);
		AddSplinePointAtIndex(Location, PointIndex, ESplineCoordinateSpace::Local, false);
		SetSplinePointType(PointIndex, ESplinePointType::Curve, false);
	}

	SetClosedLoop(true, false);

	UpdateSpline();
}