#include "ProceduralSplineComponentBase.h"

void UProceduralSplineComponentBase::InitRoundedCornerParam(FSplineRoundedCorner& RoundedCornerParam)
{
	if (RoundedCornerParam.Method == ESplineRoundMethod::Circular)
	{
		RoundedCornerParam.TangentScale = 1.0f;
	}
	else if (RoundedCornerParam.Method == ESplineRoundMethod::TangentScale)
	{
		RoundedCornerParam.PointNum = 2;
	}
}

TArray<FVector> UProceduralSplineComponentBase::RoundCornerPoint(const FSplineRoundedCorner& RoundedCornerParam, const FVector& PrevPoint,
	const FVector& CornerPoint, const FVector& NextPoint, float InteriorAngleDeg,
	TArray<ESplineRoundedPointPositionType>& OutPointPositions) const
{
	const FVector DirectionCornerToPrev = (PrevPoint - CornerPoint).GetSafeNormal();
	const FVector DirectionCornerToNext = (NextPoint - CornerPoint).GetSafeNormal();
	const FVector DirectionCornerToRoundCenter = (DirectionCornerToPrev + DirectionCornerToNext).GetSafeNormal();
	const float InteriorAngleRad = InteriorAngleDeg * PI / 180.0f;
	const float DistanceCornerToRoundCenter = RoundedCornerParam.Length / FMath::Cos(InteriorAngleRad / 2.0f);
	const FVector RoundCenterLocation = CornerPoint + DirectionCornerToRoundCenter * DistanceCornerToRoundCenter;
	const FVector RoundAxis = FVector::CrossProduct(DirectionCornerToNext, DirectionCornerToPrev).GetSafeNormal();
	const FVector VectorRoundCenterToNeighbor =
		-DirectionCornerToRoundCenter * DistanceCornerToRoundCenter + DirectionCornerToPrev * RoundedCornerParam.Length;

	TArray<FVector> ReturnLocations;
	for (int32 PointIndex = 0; PointIndex < RoundedCornerParam.PointNum; PointIndex++)
	{
		const float RoundPointAngleDeg = (180.0f - InteriorAngleDeg) / (RoundedCornerParam.PointNum - 1) * PointIndex;
		ReturnLocations.Add(RoundCenterLocation + VectorRoundCenterToNeighbor.RotateAngleAxis(RoundPointAngleDeg, RoundAxis));
		if (PointIndex == 0)
		{
			OutPointPositions.Add(ESplineRoundedPointPositionType::Start);
		}
		else if (PointIndex == RoundedCornerParam.PointNum - 1)
		{
			OutPointPositions.Add(ESplineRoundedPointPositionType::End);
		}
		else
		{
			OutPointPositions.Add(ESplineRoundedPointPositionType::Between);
		}
	}

	return ReturnLocations;
}

void UProceduralSplineComponentBase::MakeRoundedCornerSpline(
	const TArray<FVector>& VertexLocations, bool bRoundCorner, const FSplineRoundedCorner& RoundedCornerParam)
{
	const int32 VertexNum = VertexLocations.Num();
	TArray<FVector> VertexLocationsRounded;
	TArray<ESplineRoundedPointPositionType> RoundexPointPositionTypes;
	if (bRoundCorner)
	{
		for (int32 VertexIndex = 0; VertexIndex < VertexNum; VertexIndex++)
		{
			const FVector& CornerVertexLocation = VertexLocations[VertexIndex];
			const FVector& PrevVertexLocation =
				(VertexIndex != 0) ? VertexLocations[VertexIndex - 1] : VertexLocations[VertexNum - 1];
			const FVector& NextVertexLocation =
				(VertexIndex != VertexNum - 1) ? VertexLocations[VertexIndex + 1] : VertexLocations[0];
			const float InternalAngleDeg = 180.0f * (VertexNum - 2) / VertexNum;
			TArray<ESplineRoundedPointPositionType> RoundPointPositionTypes;
			VertexLocationsRounded.Append(RoundCornerPoint(RoundedCornerParam, PrevVertexLocation, CornerVertexLocation, NextVertexLocation,
				InternalAngleDeg, RoundPointPositionTypes));
			RoundexPointPositionTypes.Append(RoundPointPositionTypes);
		}
	}
	const TArray<FVector>& SplinePointLocations = (!bRoundCorner) ? VertexLocations : VertexLocationsRounded;

	for (int32 PointIndex = 0; PointIndex < SplinePointLocations.Num(); PointIndex++)
	{
		AddSplinePointAtIndex(SplinePointLocations[PointIndex], PointIndex, ESplineCoordinateSpace::Local, false);
		if (!bRoundCorner)
		{
			SetSplinePointType(PointIndex, ESplinePointType::Linear, false);
		}
		else
		{
			SetSplinePointType(PointIndex, ESplinePointType::Curve, false);
		}
	}

	SetClosedLoop(true, false);

	UpdateSpline();

	if (bRoundCorner)
	{
		for (int32 PointIndex = 0; PointIndex < SplinePointLocations.Num(); PointIndex++)
		{
			const int32 PrevPointIndex = (PointIndex != 0) ? PointIndex - 1 : SplinePointLocations.Num() - 1;
			const int32 NextPointIndex = (PointIndex != SplinePointLocations.Num() - 1) ? PointIndex + 1 : 0;
			if (RoundexPointPositionTypes[PointIndex] == ESplineRoundedPointPositionType::Start)
			{
				const FVector TangentDirection =
					(SplinePointLocations[PointIndex] - SplinePointLocations[PrevPointIndex]).GetSafeNormal();
				const float NextTangentSize = GetTangentAtSplinePoint(NextPointIndex, ESplineCoordinateSpace::Local).Size();
				const FVector Tangent = TangentDirection * NextTangentSize * RoundedCornerParam.TangentScale;
				SetTangentAtSplinePoint(PointIndex, Tangent, ESplineCoordinateSpace::Local, false);
			}
			else if (RoundexPointPositionTypes[PointIndex] == ESplineRoundedPointPositionType::End)
			{
				const FVector TangentDirection =
					(SplinePointLocations[NextPointIndex] - SplinePointLocations[PointIndex]).GetSafeNormal();
				const float PrevTangentSize = GetTangentAtSplinePoint(PrevPointIndex, ESplineCoordinateSpace::Local).Size();
				const FVector Tangent = (RoundedCornerParam.PointNum != 2) ? TangentDirection * PrevTangentSize * RoundedCornerParam.TangentScale
																   : TangentDirection * PrevTangentSize;
				SetTangentAtSplinePoint(PointIndex, Tangent, ESplineCoordinateSpace::Local, false);
			}
		}
		UpdateSpline();
	}
}

void UProceduralSplineComponentBase::PostInitProperties()
{
	Super::PostInitProperties();

	bSplineHasBeenEdited = true;
	ProceedSpline();
}

#if WITH_EDITOR

void UProceduralSplineComponentBase::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property != nullptr)
	{
		ProceedSpline();
	}
}

#endif