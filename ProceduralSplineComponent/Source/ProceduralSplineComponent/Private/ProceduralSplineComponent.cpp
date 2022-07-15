/*!
 * ProceduralSplineComponent
 *
 * Copyright (c) 2022 Colory Games
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "ProceduralSplineComponent.h"

#define LOCTEXT_NAMESPACE "FProceduralSplineComponent"

void FProceduralSplineComponentModule::StartupModule()
{
}

void FProceduralSplineComponentModule::ShutdownModule()
{
}

bool FProceduralSplineComponentModule::SupportsDynamicReloading()
{
	return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FProceduralSplineComponentModule, ProceduralSplineComponent);
