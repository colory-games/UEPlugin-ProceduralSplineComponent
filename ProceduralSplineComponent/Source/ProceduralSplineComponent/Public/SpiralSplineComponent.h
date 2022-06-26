/*!
 * ProceduralSplineComponent
 *
 * Copyright (c) 2022 Colory Games
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/

#pragma once

#include "ProceduralSplineComponentBase.h"

#include "SpiralSplineComponent.generated.h"

UCLASS(ClassGroup = (ProceduralSpline), meta = (BlueprintSpawnableComponent))
class PROCEDURALSPLINECOMPONENT_API USpiralSplineComponent : public UProceduralSplineComponentBase
{
	GENERATED_BODY()

public:
	virtual void ProceedSpline() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spiral Spline", meta = (ClampMin = 3))
	int32 PointNum = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spiral Spline", meta = (ClampMin = 0.0f))
	float TurnNum = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spiral Spline", meta = (ClampMin = 0.0f))
	float InnerRadius = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spiral Spline", meta = (ClampMin = 0.0f))
	float OuterRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spiral Spline")
	bool bInvertSpiral = false;
};