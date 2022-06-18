#include "JaggedSplineComponent.h"

void UJaggedSplineComponent::ProceedSpline()
{
	Super::ProceedSpline();

	ClearSplinePoints();

	const float IntervalWidth = Width / PointNum;
	for (int32 PointIndex = 0; PointIndex < PointNum; PointIndex++)
	{
		float LocationYSign = (PointIndex % 2 == 0) ? 1.0f : -1.0f;
		const FVector Location = FVector(IntervalWidth * PointIndex, LocationYSign * Length / 2.0f, 0.0f);
		AddSplinePointAtIndex(Location, PointIndex, ESplineCoordinateSpace::Local, false);
		SetSplinePointType(PointIndex, ESplinePointType::Linear, false);
	}

	SetClosedLoop(false, false);

	UpdateSpline();
}