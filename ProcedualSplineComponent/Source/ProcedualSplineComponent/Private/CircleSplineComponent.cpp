#include "CircleSplineComponent.h"

void UCircleSplineComponent::ProceedSpline()
{
	Super::ProceedSpline();

	ClearSplinePoints();
	for (int i_point = 0; i_point < PointNum; i_point++)
	{
		FVector Location = FVector(Radius * FMath::Sin((float) i_point / PointNum * 2.0 * PI),
			Radius * FMath::Cos((float) i_point / PointNum * 2.0 * PI), 0.0f);
		AddSplinePointAtIndex(Location, i_point, ESplineCoordinateSpace::Local, false);
		SetSplinePointType(i_point, ESplinePointType::CurveClamped, false);
	}
	SetClosedLoop(true, false);
	UpdateSpline();
}