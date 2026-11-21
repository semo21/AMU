using UnrealBuildTool;

public class Defense : ModuleRules
{
    public Defense(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "UMG",
            "HubCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { "InputCore" });
    }
}