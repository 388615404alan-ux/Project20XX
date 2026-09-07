using UnrealBuildTool;
using System.Collections.Generic;

public class Project20XXTarget : TargetRules
{
    public Project20XXTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V7;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
        ExtraModuleNames.Add("Project20XX");
    }
}
