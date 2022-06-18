#include "SpiralSplineComponent.h"

void USpiralSplineComponent::ProceedSpline()
{
	Super::ProceedSpline();

	ClearSplinePoints();

	const float MaxTheta = 2.0f * PI * TurnNum;
	for (int32 PointIndex = 0; PointIndex < PointNum; PointIndex++)
	{
		const float Theta = MaxTheta * PointIndex / (PointNum - 1);
		const float R = FMath::Lerp<float>(InnerRadius, OuterRadius, Theta / MaxTheta);
		const FVector Location = (!bInvertSpiral) ? FVector(R * FMath::Sin(Theta), R * FMath::Cos(Theta), 0.0f)
			: FVector(-R * FMath::Sin(Theta), R * FMath::Cos(Theta), 0.0f);
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