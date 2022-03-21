#include "ProceduralSplineComponentBase.h"

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




