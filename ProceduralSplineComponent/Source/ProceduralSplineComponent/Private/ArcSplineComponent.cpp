#include "ArcSplineComponent.h"

void UArcSplineComponent::ProceedSpline()
{
	Super::ProceedSpline();

	ClearSplinePoints();

	for (int32 PointIndex = 0; PointIndex < PointNum; PointIndex++)
	{
		const float AngleRad = FMath::Lerp(StartAngle, EndAngle, (float)PointIndex / (PointNum - 1)) * PI / 180.0f;
		FVector Location = FVector(Radius * FMath::Sin(AngleRad), Radius * FMath::Cos(AngleRad), 0.0f);
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