// Some copyright should be here...

using UnrealBuildTool;

public class ProceduralSplineComponent : ModuleRules
{
	public ProceduralSplineComponent(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]{
			"Core",
			"CoreUObject",
			"Engine",
		});

		PrivateDependencyModuleNames.AddRange(new string[]{});
	}
}
