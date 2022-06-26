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

#include "JaggedSplineComponent.generated.h"

UCLASS(ClassGroup = (ProceduralSpline), meta = (BlueprintSpawnableComponent))
class PROCEDURALSPLINECOMPONENT_API UJaggedSplineComponent : public UProceduralSplineComponentBase
{
	GENERATED_BODY()

public:
	virtual void ProceedSpline() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jagged Spline", meta = (ClampMin = 3))
	int32 PointNum = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jagged Spline", meta = (ClampMin = 0.0f))
	float Width = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jagged Spline", meta = (ClampMin = 0.0f))
	float Length = 50.0f;
};