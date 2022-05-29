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
struct FSplineRoundedCorner
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESplineRoundMethod Method;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Length = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Method == ESplineRoundMethod::Circular"))
	int32 PointNum = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Method == ESplineRoundMethod::TangentScale"))
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
	void InitRoundedCornerParam(FSplineRoundedCorner& RoundedCornerParam);
	TArray<FVector> RoundCornerPoint(const FSplineRoundedCorner& RoundedCornerParam, const FVector& PrevPoint,
		const FVector& CornerPoint, const FVector& NextPoint, float InteriorAngleDeg,
		TArray<ESplineRoundedPointPositionType>& OutPointPositions) const;
	void MakeRoundedCornerSpline(
		const TArray<FVector>& VertexLocations, bool bRoundCorner, const FSplineRoundedCorner& RoundedCornerParam);
};