#pragma once

#include "ProceduralSplineComponentBase.h"

#include "ArcSplineComponent.generated.h"

UCLASS(ClassGroup = (ProceduralSpline), meta = (BlueprintSpawnableComponent))
class PROCEDURALSPLINECOMPONENT_API UArcSplineComponent : public UProceduralSplineComponentBase
{
	GENERATED_BODY()

public:
	virtual void ProceedSpline() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arc Spline", meta = (ClampMin = 3))
	int32 PointNum = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arc Spline", meta = (ClampMin = 0.0f))
	float Radius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arc Spline", meta = (ClampMin = -360.0f, ClampMax = 360.0f))
	float StartAngle = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arc Spline", meta = (ClampMin = -360.0f, ClampMax = 360.0f))
	float EndAngle = 180.0f;
};