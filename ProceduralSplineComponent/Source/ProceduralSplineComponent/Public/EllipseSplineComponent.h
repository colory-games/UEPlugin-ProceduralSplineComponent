#pragma once

#include "ProceduralSplineComponentBase.h"

#include "EllipseSplineComponent.generated.h"

UCLASS(ClassGroup = (ProceduralSpline), meta = (BlueprintSpawnableComponent))
class PROCEDURALSPLINECOMPONENT_API UEllipseSplineComponent : public UProceduralSplineComponentBase
{
	GENERATED_BODY()

public:
	virtual void ProceedSpline() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ellipse Spline", meta = (ClampMin = 2))
	int32 PointNum = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ellipse Spline", meta = (ClampMin = 0.0f))
	float Width = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ellipse Spline", meta = (ClampMin = 0.0f))
	float Length = 500.0f;
};