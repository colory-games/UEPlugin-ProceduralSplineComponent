#pragma once

#include "ProceduralSplineComponentBase.h"

#include "DiamondSplineComponent.generated.h"

UCLASS(ClassGroup = (ProceduralSpline), meta = (BlueprintSpawnableComponent))
class PROCEDURALSPLINECOMPONENT_API UDiamondSplineComponent : public UProceduralSplineComponentBase
{
	GENERATED_BODY()

public:
	virtual void ProceedSpline() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diamond Spline", meta = (ClampMin = 0.0f))
	float Width = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diamond Spline", meta = (ClampMin = 0.0f, EditCondition = "!bSquare"))
	float Length = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diamond Spline", meta = (InlineEditConditionToggle))
	bool bRoundCorner = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diamond Spline",
		meta = (EditCondition = "bRoundCorner", DisplayName = "Rounded Corner"))
	FSplineRoundedCornerParams RoundedCornerParams;
};