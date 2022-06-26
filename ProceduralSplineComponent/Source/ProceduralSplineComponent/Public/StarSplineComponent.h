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

#include "StarSplineComponent.generated.h"

UCLASS(ClassGroup = (ProceduralSpline), meta = (BlueprintSpawnableComponent))
class PROCEDURALSPLINECOMPONENT_API UStarSplineComponent : public UProceduralSplineComponentBase
{
	GENERATED_BODY()

public:
	virtual void ProceedSpline() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star Spline", DisplayName = "N gram", meta = (ClampMin = 3))
	int32 Ngram = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star Spline", meta = (ClampMin = 0.0f))
	float OuterRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star Spline", meta = (ClampMin = 0.0f))
	float InnerRadius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star Spline", meta = (InlineEditConditionToggle))
	bool bRoundCorner = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Star Spline",
		meta = (EditCondition = "bRoundCorner", DisplayName = "Rounded Corner"))
	FSplineRoundedCornerParams RoundedCornerParams;
};