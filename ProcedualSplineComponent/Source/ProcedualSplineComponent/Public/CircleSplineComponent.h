#pragma once

#include "ProceduralSplineComponentBase.h"

#include "CircleSplineComponent.generated.h"

UCLASS(ClassGroup = (ProceduralSpline), meta = (BlueprintSpawnableComponent))
class PROCEDUALSPLINECOMPONENT_API UCircleSplineComponent : public UProceduralSplineComponentBase
{
	GENERATED_BODY()

public:
	virtual void ProceedSpline() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 3))
	int PointNum = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.0f))
	float Radius = 500.0f;
};