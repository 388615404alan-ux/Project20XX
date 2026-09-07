param(
    [string]$EngineRoot = 'D:\UE_5.8',
    [string]$MirrorRoot = 'D:\Project20XXBuild'
)

$ErrorActionPreference = 'Stop'

$workspaceRoot = Split-Path -Parent $PSScriptRoot
$sourceProject = Join-Path $workspaceRoot 'Game\Project20XX'
$sourceUproject = Join-Path $sourceProject 'Project20XX.uproject'
$buildScript = Join-Path $EngineRoot 'Engine\Build\BatchFiles\Build.bat'
$resolvedMirror = [System.IO.Path]::GetFullPath($MirrorRoot)
$mirrorDriveRoot = [System.IO.Path]::GetPathRoot($resolvedMirror)

if (-not (Test-Path -LiteralPath $sourceUproject)) {
    throw "Project file not found: $sourceUproject"
}

if (-not (Test-Path -LiteralPath $buildScript)) {
    throw "Unreal build script not found: $buildScript"
}

if ($resolvedMirror -eq $mirrorDriveRoot -or $resolvedMirror.Length -lt 10) {
    throw "Unsafe mirror path: $resolvedMirror"
}

New-Item -ItemType Directory -Force -Path $resolvedMirror | Out-Null

foreach ($folderName in @('Config', 'Source')) {
    $destination = Join-Path $resolvedMirror $folderName
    if (Test-Path -LiteralPath $destination) {
        $checkedDestination = [System.IO.Path]::GetFullPath($destination)
        if (-not $checkedDestination.StartsWith($resolvedMirror, [System.StringComparison]::OrdinalIgnoreCase)) {
            throw "Refusing to replace path outside mirror root: $checkedDestination"
        }
        Remove-Item -LiteralPath $checkedDestination -Recurse -Force
    }
    Copy-Item -LiteralPath (Join-Path $sourceProject $folderName) -Destination $destination -Recurse
}

Copy-Item -LiteralPath $sourceUproject -Destination (Join-Path $resolvedMirror 'Project20XX.uproject') -Force

& $buildScript Project20XXEditor Win64 Development (Join-Path $resolvedMirror 'Project20XX.uproject') -WaitMutex -NoHotReloadFromIDE
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

$mirrorBinaries = Join-Path $resolvedMirror 'Binaries'
if (Test-Path -LiteralPath $mirrorBinaries) {
    Copy-Item -LiteralPath $mirrorBinaries -Destination $sourceProject -Recurse -Force
}

Write-Host 'Project20XXEditor build succeeded.'
