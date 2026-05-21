<#
.SYNOPSIS
    Stages every merged AGENTS.md (dotnet-new + VSIX) under
    dev\Templates\.review-temp for human review on a PR.

.DESCRIPTION
    Reuses Source\Validate-VSIXBuilds.ps1 to build the 7 VSIX twin csprojs;
    that fires the _GenerateMergedReadme target and writes the merged
    AGENTS.md next to each .vstemplate. Then packs
    Dotnet\WinAppSdk.CSharp.DotnetNewTemplates.csproj, which fires the
    inline ExpandProjectTemplatePackItems task and writes merged AGENTS.md
    files into obj\<config>\net8.0\merged-readmes\<short-id>\AGENTS.md.

    Both sets are copied into a single review tree:
        dev\Templates\.review-temp\out-of-box-instructions\
            dotnet-new\<friendly>\AGENTS.md       (e.g. blank-app)
            VSIX\Csharp\<TemplateName>\AGENTS.md  (e.g. ClassLibrary)

    This output is for PR review only. It is intended to be deleted from
    the branch before the PR merges -- the merged files themselves are
    generated at build/pack time and never need to live in tree.

    Re-running the script wipes and refreshes .review-temp\.

.PARAMETER Configuration
    MSBuild configuration to use for the dotnet pack. The dot-sourced
    Validate-VSIXBuilds.ps1 always builds Release; passing anything else
    here only affects the dotnet pack output path. Default: Release.
#>
[CmdletBinding()]
param(
    [string]$Configuration = "Release"
)

$ErrorActionPreference = "Stop"

$TemplatesDir = $PSScriptRoot
$RepoRoot     = (Resolve-Path (Join-Path $TemplatesDir "..\..")).Path
$ReviewRoot   = Join-Path $TemplatesDir ".review-temp\out-of-box-instructions"
$VsixDest     = Join-Path $ReviewRoot "VSIX\Csharp"
$DotnetDest   = Join-Path $ReviewRoot "dotnet-new"

# --- 1. Clean previous output so reviewers see exactly what this run produced. ---
if (Test-Path $ReviewRoot) {
    Remove-Item -LiteralPath $ReviewRoot -Recurse -Force
}
New-Item -ItemType Directory -Path $VsixDest, $DotnetDest -Force | Out-Null

# --- 2. VSIX: dot-source the validation script so it builds the 7 twin csprojs
# in our scope. That sets $msbuild, $projects, $agents, $overallPass for us. ---
$validateScript = Join-Path $TemplatesDir "Source\Validate-VSIXBuilds.ps1"
Push-Location $RepoRoot
try {
    . $validateScript
}
finally {
    Pop-Location
}
if (-not $overallPass) {
    throw "VSIX validation failed before staging artifacts: $firstFailure"
}

# --- 3. Stage VSIX merged AGENTS.md files. ---
# All 7 VSIX twin csprojs set <TemplateReadme>, so each one produces a merged
# file next to its .vstemplate. PackagedApp is a ProjectGroup umbrella whose
# .vstemplate does not <ProjectItem> AGENTS.md, so its merged file is generated
# but never shipped in the .vsix; we include it for review completeness.
$vsixNames = @(
    "ClassLibrary",
    "MvvmApp",
    "NavigationApp",
    "PackagedApp",
    "SingleProjectPackagedApp",
    "TabViewApp",
    "UnitTestApp"
)
foreach ($name in $vsixNames) {
    $src = Join-Path $RepoRoot "dev\Templates\Source\ProjectTemplates\Desktop\CSharp\$name\AGENTS.md"
    if (-not (Test-Path $src)) {
        Write-Warning "VSIX merged AGENTS.md not generated for $name; skipping."
        continue
    }
    $dstDir = Join-Path $VsixDest $name
    New-Item -ItemType Directory -Path $dstDir -Force | Out-Null
    Copy-Item -LiteralPath $src -Destination (Join-Path $dstDir "AGENTS.md") -Force
    Write-Host "Staged VSIX\Csharp\$name\AGENTS.md"
}

# --- 4. dotnet-new: pack the templates csproj to fire ExpandProjectTemplatePackItems. ---
$dotnetProj = Join-Path $RepoRoot "dev\Templates\Dotnet\WinAppSdk.CSharp.DotnetNewTemplates.csproj"
Write-Host ""
Write-Host "Packing $dotnetProj ..."
& $msbuild $dotnetProj /t:Pack /p:Configuration=$Configuration /v:minimal /nologo
if ($LASTEXITCODE -ne 0) {
    throw "dotnet templates Pack failed (exit $LASTEXITCODE)."
}

# --- 5. Build a short-id -> friendly folder name map from templates.props. ---
# The merge task writes merged AGENTS.md into merged-readmes\<ItemSpec>\ where
# ItemSpec is the short id (e.g. winui.blankapp). The user-facing review folder
# uses the friendly DotnetConfigDir leaf name (e.g. blank-app) instead.
$propsPath = Join-Path $TemplatesDir "templates.props"
[xml]$propsXml = Get-Content -LiteralPath $propsPath -Raw
$shortToFriendly = @{}
foreach ($pt in $propsXml.SelectNodes("//ProjectTemplate[@Include]")) {
    $configNode = $pt.SelectSingleNode("DotnetConfigDir")
    if (-not $configNode) { continue }
    $configDir = $configNode.InnerText.Trim()
    if ([string]::IsNullOrWhiteSpace($configDir)) { continue }
    $shortToFriendly[$pt.GetAttribute("Include")] = (Split-Path $configDir -Leaf)
}

# --- 6. Stage dotnet-new merged AGENTS.md files. ---
$mergedRoot = Join-Path $RepoRoot "dev\Templates\Dotnet\obj\$Configuration\net8.0\merged-readmes"
if (-not (Test-Path $mergedRoot)) {
    throw "merged-readmes directory missing at $mergedRoot after Pack."
}
foreach ($itemDir in Get-ChildItem -LiteralPath $mergedRoot -Directory) {
    $src = Join-Path $itemDir.FullName "AGENTS.md"
    if (-not (Test-Path $src)) { continue }

    $shortId  = $itemDir.Name
    $friendly = $shortToFriendly[$shortId]
    if (-not $friendly) {
        Write-Warning "No DotnetConfigDir mapping for short id '$shortId'; using id as folder name."
        $friendly = $shortId
    }

    $dstDir = Join-Path $DotnetDest $friendly
    New-Item -ItemType Directory -Path $dstDir -Force | Out-Null
    Copy-Item -LiteralPath $src -Destination (Join-Path $dstDir "AGENTS.md") -Force
    Write-Host "Staged dotnet-new\$friendly\AGENTS.md"
}

Write-Host ""
Write-Host "Review artifacts staged under:"
Write-Host "    $ReviewRoot"
