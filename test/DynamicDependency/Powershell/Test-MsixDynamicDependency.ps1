# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"

# Repository paths
$root = (Get-Item $PSScriptRoot).parent.parent.parent.FullName
$dev = Join-Path $root 'dev'
$test = Join-Path $root 'test'
$buildOutput = Join-Path $root 'BuildOutput\Debug\x64'

# Test package(s)
$packageName = 'WindowsAppRuntime.Test.DynDep.Fwk.Widgets'
$packageFamilyName = 'WindowsAppRuntime.Test.DynDep.Fwk.Widgets_8wekyb3d8bbwe'
$packageFullName = 'WindowsAppRuntime.Test.DynDep.Fwk.Widgets_1.2.3.4_neutral__8wekyb3d8bbwe'
$packageMsixDir = 'Framework.Widgets'
$packageMsixFilename = 'Framework.Widgets.msix'
$packageMsixPath = Join-Path $buildOutput $packageMsixDir
$packageMsix = Join-Path $packageMsixPath $packageMsixFilename

Function RemoveTestPackages
{
    Write-Host "Removing $packageName..."

    # Remove our package(s) in case they were previously installed and incompletely removed
    Get-AppxPackage $packageName | Remove-AppxPackage
    $p = Get-AppxPackage $packageName
    if ($p -ne $null)
    {
        Write-Error $p
        Write-Error "Remove/Get-AppxPackage result not expected"
        Exit 1
    }
}

Function AddTestPackages
{
    Write-Host "Adding $packageMsix..."

    # Install our needed package(s)
    if (-not(Test-Path -Path $packageMsix -PathType Leaf))
    {
        Write-Error "$($packageMsix) not found"
        Exit 1
    }
    Add-AppxPackage $packageMsix
    $p = Get-AppxPackage $packageName
    if (($p -eq $null) -Or ($p.PackageFullName -ne $packageFullName))
    {
        Write-Error $p
        Write-Error "Get-AppxPackage result not expected"
        Exit 1
    }
    if ($p.PackageFullName -ne $packageFullName)
    {
        Write-Error "$p.PackageFullName not expected (expected=$packageFullName)"
        Exit 1
    }
}

Function Setup
{
    ""
    Write-Host "Testing setup..."
    RemoveTestPackages
    AddTestPackages
    Write-Host "Setup done."
}

Function Cleanup
{
    ""
    Write-Host "Testing cleanup..."
    $null = RemoveTestPackages
    Write-Host "Cleanup done."
}

# Setup test data
$null = Setup

# Import the MSIX Dynamic Dependency module
$module = Join-Path $dev 'DynamicDependency\Powershell\MsixDynamicDependency.psm1'
Import-Module -Name $module -Verbose:$true -ErrorAction Stop

# Test the module
""
Write-Host "Testing API..."
""

"API: RevisionId"
$rid = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageGraph]::RevisionId
"RevisionId: $rid"
if ($rid -ne 0)
{
    Write-Error "PackageGraph.RevisionId != 0 (expected=0)"
    Exit 1
}
""

"API: TryCreate"
$pdid = "before"
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::TryCreate(
        $packageFamilyName,
        0,
        [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyProcessorArchitectures]::None,
        [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyLifetimeKind]::Process,
        "",
        [Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions]::None,
        [ref] $pdid)
"HRESULT: 0x" + $hr.ToString("X")
"PackageDependencyId: $pdid"
if ([string]::IsNullOrEmpty($pdid))
{
    Write-Error "PackageDependencyId is blank"
    Exit 1
}
""

"API: GetResolvedPackageFullName"
$pfn = "before"
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetResolvedPackageFullName($pdid, [ref] $pfn)
"HRESULT: 0x" + $hr.ToString("X")
"PackageFullName: $pfn"
if (-not([string]::IsNullOrEmpty($pfn)))
{
    Write-Error "PackageDependency not resolved yet but PackageFullName is not blank"
    Exit 1
}
""

"API: Add"
$pdc = 0
$pfn = "before"
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Add(
        $pdid,
        [Microsoft.Windows.ApplicationModel.DynamicDependency.Rank]::Default,
        [Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions]::None,
        [ref] $pdc,
        [ref] $pfn)
"HRESULT: 0x" + $hr.ToString("X")
"PackageDependencyContext: $pdc"
"PackageFullName: $pfn"
if ([string]::IsNullOrEmpty($pdc))
{
    Write-Error "PackageDependencyContext is blank"
    Exit 1
}
if ([string]::IsNullOrEmpty($pfn))
{
    Write-Error "PackageFullName is blank"
    Exit 1
}
""

"API: RevisionId"
$rid = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageGraph]::RevisionId
"RevisionId: $rid"
if ($rid -ne 1)
{
    Write-Error "PackageGraph.RevisionId != 1 (expected=1)"
    Exit 1
}
""

"API: GetIdForContext"
$id = "before"
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetIdForContext($pdc, [ref] $id)
"HRESULT: 0x" + $hr.ToString("X")
"PackageDependencyId: $id"
if ([string]::IsNullOrEmpty($pdid))
{
    Write-Error "PackageDependencyId is blank"
    Exit 1
}
""

"API: GetResolvedPackageFullName"
$pfn = "before"
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetResolvedPackageFullName($pdid, [ref] $pfn)
"HRESULT: 0x" + $hr.ToString("X")
"PackageFullName: $pfn"
if ([string]::IsNullOrEmpty($pfn))
{
    Write-Error "PackageFullName is blank"
    Exit 1
}
""

"----------------------------------------"
"API: New a WinRT type from the package dynamically added to our package graph"
$widget = [Microsoft.Test.DynamicDependency.Widgets.Widget1,Microsoft.Test.DynamicDependency.Widgets.Widget1,ContentType=WindowsRuntime]::GetStatic()
#$widget = [Microsoft.Test.DynamicDependency.Widgets.Widget1,Microsoft.Test.DynamicDependency.Widgets.Widget1,ContentType=WindowsRuntime]::New()
$widget | Format-Custom
"----------------------------------------"
""

"API: Remove"
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Remove($pdc)
"HRESULT: 0x" + $hr.ToString("X")

"API: RevisionId"
$rid = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageGraph]::RevisionId
"RevisionId: $rid"
""

"API: GetResolvedPackageFullName"
$pfn = "before"
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetResolvedPackageFullName($pdid, [ref] $pfn)
"HRESULT: 0x" + $hr.ToString("X")
"PackageFullName: $pfn"
""

"API: Delete"
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Delete($pdid)
"HRESULT: 0x" + $hr.ToString("X")
""

# Cleanup test data
$null = Cleanup

""
Write-Host "Success!"
Exit 0
