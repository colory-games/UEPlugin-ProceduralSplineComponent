#pragma once

#include "ProceduralSplineComponentBase.h"

#include "RegularNgonSplineComponent.generated.h"

UCLASS(ClassGroup = (ProceduralSpline), meta = (BlueprintSpawnableComponent))
class PROCEDURALSPLINECOMPONENT_API URegularNgonSplineComponent : public UProceduralSplineComponentBase
{
	GENERATED_BODY()

public:
	virtual void ProceedSpline() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Regular Ngon Spline", meta = (ClampMin = 3))
	int VertexNum = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Regular Ngon Spline", meta = (ClampMin = 0.0f))
	float Radius = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Regular Ngon Spline", meta = (InlineEditConditionToggle))
	bool bRoundedCorner = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Regular Ngon Spline", meta = (EditCondition = "bRoundedCorner"))
	FSplineRoundedCorner RoundedCorner;
};