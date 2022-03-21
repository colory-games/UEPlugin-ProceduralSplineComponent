#pragma once

#include "Components/SplineComponent.h"
#include "CoreMinimal.h"

#include "ProceduralSplineComponentBase.generated.h"

UCLASS(ClassGroup = (ProceduralSpline))
class PROCEDUALSPLINECOMPONENT_API UProceduralSplineComponentBase : public USplineComponent
{
	GENERATED_BODY()

public:
	virtual void PostInitProperties() override;
#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif
	virtual void ProceedSpline() {};
};