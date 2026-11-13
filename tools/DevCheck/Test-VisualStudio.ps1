# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.
Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

$root = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path
$ast = [System.Management.Automation.Language.Parser]::ParseFile(
    "$root\tools\DevCheck\DevCheck.ps1", [ref]$null, [ref]$null)
$names = @('Get-VisualStudioInstallPath', 'Test-VisualStudioInstall',
    'Test-VisualStudioComponent', 'Test-VisualStudioComponents')
foreach ($node in $ast.FindAll({
    param($node)
    $node -is [System.Management.Automation.Language.FunctionDefinitionAst]
}, $true)) {
    if ($node.Name -in $names) {
        . ([scriptblock]::Create($node.Extent.Text))
    }
}

function Get-ProjectRoot { return $root }
function Get-VSWhere { return 'vswhere.exe' }
function Run-Process {
    param([string]$exe, [string]$arguments, [int]$throwIfExitCodeIsFailure = 0)
    if ($arguments -match '-format json') { return $script:instanceJson }
    if ($arguments -notmatch [regex]::Escape("[$global:vsversion,$global:vsversion]")) {
        throw 'Component query was not scoped to the selected version'
    }
    $component = [regex]::Match($arguments, '-requires (\S+)').Groups[1].Value
    if ($script:overrides.ContainsKey($component)) { return $script:overrides[$component] }
    return "$global:vspath`r`n"
}
function Assert([bool]$condition, [string]$message) {
    if (-not $condition) { throw $message }
}
function Set-Instance([int]$major) {
    $script:instanceJson = ConvertTo-Json -InputObject @(@{
        installationPath = "C:\VS$major"
        installationVersion = "$major.14.123.4"
    })
    $script:overrides = @{}
    $global:issues = 0
    $global:vspath = ''
    $global:vsversion = $null
}

foreach ($major in @(17, 18)) {
    Set-Instance $major
    Assert (Test-VisualStudioInstall) "VS $major discovery failed"
    Assert (Test-VisualStudioComponents) "VS $major component check failed"
    Assert ($global:issues -eq 0) "VS $major incorrectly reported issues"

    Set-Instance $major
    $null = Test-VisualStudioInstall
    $script:overrides['Microsoft.Component.MSBuild'] = ''
    Assert (-not (Test-VisualStudioComponents)) "VS $major missing component was accepted"
    Assert ($global:issues -eq 1) "VS $major missing component was not counted for exit status"

    Set-Instance $major
    $null = Test-VisualStudioInstall
    $script:overrides['Microsoft.VisualStudio.Component.NuGet'] = "C:\AnotherVS`r`n"
    Assert (-not (Test-VisualStudioComponents)) "VS $major accepted a component from a different installation"
    Assert ($global:issues -eq 1) "VS $major split-install failure was not counted"

    Set-Instance $major
    $null = Test-VisualStudioInstall
    $script:instanceJson = '[]'
    Assert (-not (Test-VisualStudioInstall)) "VS $major no-installation case was accepted"
    Assert ($global:issues -eq 1) "VS $major no-installation failure was not counted"
    Assert ([string]::IsNullOrEmpty($global:vspath)) "VS $major stale installation path survived"
    Assert ($null -eq $global:vsversion) "VS $major stale installation version survived"
}

Set-Instance 17
$null = Test-VisualStudioInstall
foreach ($component in @(
    'Microsoft.NetCore.Component.Runtime.6.0',
    'Microsoft.NetCore.Component.Runtime.7.0',
    'Microsoft.VisualStudio.Component.LiveUnitTesting',
    'Component.Microsoft.VisualStudio.LiveShare.2022',
    'Microsoft.VisualStudio.Component.IntelliCode'
)) {
    $script:overrides[$component] = ''
}
Assert (Test-VisualStudioComponents) 'Build-ready VS2022 was rejected without obsolete runtimes or optional IDE features'
Assert ($global:issues -eq 0) 'Optional VS2022 components incorrectly reported issues'

Write-Output 'PASS: VS2022, VS2026, VS2022 pipeline image, missing component, split installations, and no installation'
exit 0
