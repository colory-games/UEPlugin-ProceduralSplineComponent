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

#include "SpringSplineComponent.generated.h"

UCLASS(ClassGroup = (ProceduralSpline), meta = (BlueprintSpawnableComponent))
class PROCEDURALSPLINECOMPONENT_API USpringSplineComponent : public UProceduralSplineComponentBase
{
	GENERATED_BODY()

public:
	virtual void ProceedSpline() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spring Spline", meta = (ClampMin = 0.0f))
	float TurnNum = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spring Spline", meta = (ClampMin = 3))
	int32 PointNum = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spring Spline", meta = (ClampMin = 0.0f))
	float Radius = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spring Spline", meta = (ClampMin = 0.0f))
	float Height = 500.0f;
};