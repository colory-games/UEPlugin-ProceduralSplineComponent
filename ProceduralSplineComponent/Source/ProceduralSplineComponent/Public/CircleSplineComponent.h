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

#include "CircleSplineComponent.generated.h"

UCLASS(ClassGroup = (ProceduralSpline), meta = (BlueprintSpawnableComponent))
class PROCEDURALSPLINECOMPONENT_API UCircleSplineComponent : public UProceduralSplineComponentBase
{
	GENERATED_BODY()

public:
	virtual void ProceedSpline() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Circle Spline", meta = (ClampMin = 3))
	int32 PointNum = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Circle Spline", meta = (ClampMin = 0.0f))
	float Radius = 500.0f;
};