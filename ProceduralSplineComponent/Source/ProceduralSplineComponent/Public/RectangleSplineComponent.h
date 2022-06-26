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

#include "RectangleSplineComponent.generated.h"

UCLASS(ClassGroup = (ProceduralSpline), meta = (BlueprintSpawnableComponent))
class PROCEDURALSPLINECOMPONENT_API URectangleSplineComponent : public UProceduralSplineComponentBase
{
	GENERATED_BODY()

public:
	virtual void ProceedSpline() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Square Spline", meta = (ClampMin = 0.0f))
	bool bSquare = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Square Spline", meta = (ClampMin = 0.0f))
	float Width = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Square Spline", meta = (ClampMin = 0.0f, EditCondition = "!bSquare"))
	float Length = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Square Spline", meta = (InlineEditConditionToggle))
	bool bRoundCorner = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Square Spline",
		meta = (EditCondition = "bRoundCorner", DisplayName = "Rounded Corner"))
	FSplineRoundedCornerParams RoundedCornerParams;
};