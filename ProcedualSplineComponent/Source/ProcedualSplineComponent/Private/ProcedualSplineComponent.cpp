#include "ProcedualSplineComponent.h"

#define LOCTEXT_NAMESPACE "FProcedualSplineComponent"

void FProcedualSplineComponentModule::StartupModule()
{
}

void FProcedualSplineComponentModule::ShutdownModule()
{
}

bool FProcedualSplineComponentModule::SupportsDynamicReloading()
{
	return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FProcedualSplineComponentModule, ProcedualSplineComponent);
