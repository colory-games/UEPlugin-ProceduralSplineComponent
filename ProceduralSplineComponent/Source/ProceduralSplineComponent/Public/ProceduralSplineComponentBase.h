/*!
 * ProceduralSplineComponent
 *
 * Copyright (c) 2022 Colory Games
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/

#pragma once

#include "Components/SplineComponent.h"
#include "CoreMinimal.h"

#include "ProceduralSplineComponentBase.generated.h"

UENUM(BlueprintType)
enum class ESplineRoundMethod : uint8
{
	Circular,
	TangentScale,
	Num UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ESplineRoundedPointPositionType : uint8
{
	Start,
	Between,
	End,
	Num UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FSplineRoundedCornerParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Rounded Corner")
	ESplineRoundMethod Method;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Rounded Corner")
	float Length = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Rounded Corner",
		meta = (EditCondition = "Method == ESplineRoundMethod::Circular"))
	int32 PointNum = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Rounded Corner",
		meta = (EditCondition = "Method == ESplineRoundMethod::TangentScale"))
	float TangentScale = 1.0f;
};

UCLASS(ClassGroup = (ProceduralSpline))
class PROCEDURALSPLINECOMPONENT_API UProceduralSplineComponentBase : public USplineComponent
{
	GENERATED_BODY()

public:
	virtual void PostInitProperties() override;
#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif
	virtual void ProceedSpline(){};

protected:
	void InitRoundedCornerParam(FSplineRoundedCornerParams& RoundedCornerParam);
	TArray<FVector> RoundCornerPoint(const FSplineRoundedCornerParams& RoundedCornerParams, const FVector& PrevPoint,
		const FVector& CornerPoint, const FVector& NextPoint, float InteriorAngleDeg,
		TArray<ESplineRoundedPointPositionType>& OutPointPositions) const;
	void MakeRoundedCornerSpline(
		const TArray<FVector>& VertexLocations, bool bRoundCorner, const FSplineRoundedCornerParams& RoundedCornerParam);
};