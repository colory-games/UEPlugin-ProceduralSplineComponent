#include "ProceduralSplineComponentBase.h"

void UProceduralSplineComponentBase::InitRoundedCornerParam(FSplineRoundedCorner& RoundParam)
{
	if (RoundParam.Method == ESplineRoundMethod::Circular)
	{
		RoundParam.TangentScale = 1.0f;
	}
	else if (RoundParam.Method == ESplineRoundMethod::TangentScale)
	{
		RoundParam.PointNum = 2;
	}
}

TArray<FVector> UProceduralSplineComponentBase::RoundCornerPoint(const FSplineRoundedCorner& RoundParam, const FVector& PrevPoint, const FVector& CornerPoint,
	const FVector& NextPoint, float InteriorAngleDeg, TArray<ESplineRoundedPointPositionType>& OutPointPositions) const
{
	const FVector DirectionCornerToPrev = (PrevPoint - CornerPoint).GetSafeNormal();
	const FVector DirectionCornerToNext = (NextPoint - CornerPoint).GetSafeNormal();
	const FVector DirectionCornerToRoundCenter = (DirectionCornerToPrev + DirectionCornerToNext).GetSafeNormal();
	const float InteriorAngleRad = InteriorAngleDeg * PI / 180.0f;
	const float DistanceCornerToRoundCenter = RoundParam.Length / cos(InteriorAngleRad / 2.0f);
	const FVector RoundCenterLocation = CornerPoint + DirectionCornerToRoundCenter * DistanceCornerToRoundCenter;
	const FVector RoundAxis = FVector::CrossProduct(DirectionCornerToNext, DirectionCornerToPrev).GetSafeNormal();
	const FVector VectorRoundCenterToNeighbor =
		-DirectionCornerToRoundCenter * DistanceCornerToRoundCenter + DirectionCornerToPrev * RoundParam.Length;

	TArray<FVector> ReturnLocations;
	for (int PointIndex = 0; PointIndex < RoundParam.PointNum; PointIndex++)
	{
		const float RoundPointAngleDeg = (180.0f - InteriorAngleDeg) / (RoundParam.PointNum - 1) * PointIndex;
		ReturnLocations.Add(RoundCenterLocation + VectorRoundCenterToNeighbor.RotateAngleAxis(RoundPointAngleDeg, RoundAxis));
		if (PointIndex == 0)
		{
			OutPointPositions.Add(ESplineRoundedPointPositionType::Start);
		}
		else if (PointIndex == RoundParam.PointNum - 1)
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
	const TArray<FVector>& VertexLocations, bool bRoundedCorner, const FSplineRoundedCorner& RoundParam)
{
	const int VertexNum = VertexLocations.Num();
	TArray<FVector> VertexLocationsRounded;
	TArray<ESplineRoundedPointPositionType> RoundexPointPositionTypes;
	if (bRoundedCorner)
	{
		for (int VertexIndex = 0; VertexIndex < VertexNum; VertexIndex++)
		{
			const FVector& CornerVertexLocation = VertexLocations[VertexIndex];
			const FVector& PrevVertexLocation =
				(VertexIndex != 0) ? VertexLocations[VertexIndex - 1] : VertexLocations[VertexNum - 1];
			const FVector& NextVertexLocation =
				(VertexIndex != VertexNum - 1) ? VertexLocations[VertexIndex + 1] : VertexLocations[0];
			const float InternalAngleDeg = 180.0f * (VertexNum - 2) / VertexNum;
			TArray<ESplineRoundedPointPositionType> RoundPointPositionTypes;
			VertexLocationsRounded.Append(RoundCornerPoint(RoundParam, PrevVertexLocation, CornerVertexLocation, NextVertexLocation,
				InternalAngleDeg, RoundPointPositionTypes));
			RoundexPointPositionTypes.Append(RoundPointPositionTypes);
		}
	}
	const TArray<FVector>& SplinePointLocations = (!bRoundedCorner) ? VertexLocations : VertexLocationsRounded;

	for (int32 PointIndex = 0; PointIndex < SplinePointLocations.Num(); PointIndex++)
	{
		AddSplinePointAtIndex(SplinePointLocations[PointIndex], PointIndex, ESplineCoordinateSpace::Local, false);
		if (!bRoundedCorner)
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

	if (bRoundedCorner)
	{
		for (int32 PointIndex = 0; PointIndex < SplinePointLocations.Num(); PointIndex++)
		{
			const int PrevPointIndex = (PointIndex != 0) ? PointIndex - 1 : SplinePointLocations.Num() - 1;
			const int NextPointIndex = (PointIndex != SplinePointLocations.Num() - 1) ? PointIndex + 1 : 0;
			if (RoundexPointPositionTypes[PointIndex] == ESplineRoundedPointPositionType::Start)
			{
				const FVector TangentDirection =
					(SplinePointLocations[PointIndex] - SplinePointLocations[PrevPointIndex]).GetSafeNormal();
				const float NextTangentSize = GetTangentAtSplinePoint(NextPointIndex, ESplineCoordinateSpace::Local).Size();
				const FVector Tangent = TangentDirection * NextTangentSize * RoundParam.TangentScale;
				SetTangentAtSplinePoint(PointIndex, Tangent, ESplineCoordinateSpace::Local, false);
			}
			else if (RoundexPointPositionTypes[PointIndex] == ESplineRoundedPointPositionType::End)
			{
				const FVector TangentDirection = (SplinePointLocations[NextPointIndex] - SplinePointLocations[PointIndex]).GetSafeNormal();
				const float PrevTangentSize = GetTangentAtSplinePoint(PrevPointIndex, ESplineCoordinateSpace::Local).Size();
				const FVector Tangent = (RoundParam.PointNum != 2) ? TangentDirection * PrevTangentSize * RoundParam.TangentScale
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