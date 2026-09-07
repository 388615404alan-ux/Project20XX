using UnrealBuildTool;
using System.Collections.Generic;

public class Project20XXEditorTarget : TargetRules
{
    public Project20XXEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V7;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
        ExtraModuleNames.Add("Project20XX");
    }
}
