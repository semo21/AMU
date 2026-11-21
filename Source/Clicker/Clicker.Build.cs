using UnrealBuildTool;

public class Clicker : ModuleRules
{
    public Clicker(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "UMG",
            "GameplayTags", 
            "HubCore" 
        });

        PrivateDependencyModuleNames.AddRange(new string[] { 
            "InputCore", 
            "Niagara", 
            "StructUtils" 
        });
    }
}