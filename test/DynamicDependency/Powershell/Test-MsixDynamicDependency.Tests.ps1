# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

# Test Framework is Pester => https://pester.dev/docs/quick-start
# NOTE: Powershell 5.1.22621.1778 includes module Pester version 3.4.0
# NOTE: Powershell 7.3.6 includes module Pester version version 3.4.0

Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"

# Errors
$E_INVALIDARG = 0x80070057

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

# Track resources to ensure we clean up
$packageDependencyIds = [ordered]@{}
$packageDependencyContexts = [ordered]@{}

Function LogComment
{
    param([string]$message)

    "       $message" | Write-Host
}

Function Trace
{
    param([string]$message)

    Write-Host $message -ForegroundColor Magenta
}

Function TraceEnter
{
    param([string]$message)

    Trace " Test: $message"
}

Function RemoveTestPackages
{
    Write-Host "Removing $packageName..." -ForegroundColor Cyan

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
    Write-Host "Adding $packageMsix..." -ForegroundColor Cyan

    # Install our needed package(s)
    if (-not(Test-Path -Path $packageMsix -PathType Leaf))
    {
        Write-Error "$($packageMsix) not found"
        Exit 1
    }
    Add-AppxPackage $packageMsix
    $p = Get-AppxPackage $packageName
    if ($p -eq $null)
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

Function CleanupPackageDependencies
{
    if ($packageDependencyContexts.Count -gt 0)
    {
        Write-Host "Cleanup: Releasing $packageDependencyContexts.Count PackageDependency Contexts" -ForegroundColor Cyan
        ForEach ($pdc in $packageDependencyContexts.Keys)
        {
            if ([string]::IsNullOrEmpty($pdc))
            {
                continue
            }
            $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Remove($pdc)
            LogComment "Delete($pdc): 0x$($hr.ToString("X"))"
        }
    }

    if ($packageDependencyIds.Count -gt 0)
    {
        Write-Host "Cleanup: Releasing $packageDependencyIds.Count PackageDependency Ids" -ForegroundColor Cyan
        ForEach ($pdid in $packageDependencyIds.Keys)
        {
            if ([string]::IsNullOrEmpty($pdid))
            {
                continue
            }
            $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Delete($pdid)
            LogComment "Delete($pdid): 0x$($hr.ToString("X"))"
        }
    }
}

Describe "DynamicDependency API" {

    BeforeAll {
        Trace "BeforeAll"

        # Import the MSIX Dynamic Dependency module
        $module = Join-Path $dev 'DynamicDependency\Powershell\MsixDynamicDependency.psm1'
        Import-Module -Name $module -Verbose:$true -ErrorAction Stop

        RemoveTestPackages
        AddTestPackages
    }

    AfterAll {
        Trace "AfterAll"

        CleanupPackageDependencies
        RemoveTestPackages
    }

    It "Get RevisionId (expect 0)" {
        TraceEnter "Get RevisionId (expect 0)"

        $rid = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageGraph]::RevisionId
        $rid | Should Be 0
    }

    It "TryCreate + Delete" {
        TraceEnter "TryCreate + Delete"

        $rid = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageGraph]::RevisionId
        LogComment "RevisionId: $rid"
        $rid | Should Be 0

        $pdid = "before"
        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::TryCreate(
                $packageFamilyName,
                0,
                [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyProcessorArchitectures]::None,
                [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyLifetimeKind]::Process,
                "",
                [Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions]::None,
                [ref] $pdid)
        LogComment "TryCreate: 0x$($hr.ToString("X"))"
        LogComment "  PackageDependencyId: $pdid"
        $hr | Should Be 0
        $pdid | Should Not BeNullOrEmpty
        $packageDependencyIds.Add($pdid, $null)

        $rid = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageGraph]::RevisionId
        LogComment "RevisionId: $rid"
        $rid | Should Be 0

        $pfn = "before"
        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetResolvedPackageFullName($pdid, [ref] $pfn)
        LogComment "GetResolvedPackageFullName: 0x$($hr.ToString("X"))"
        LogComment "  PackageFullName: $pfn"
        $hr | Should Be 0
        $pfn | Should BeNullOrEmpty

        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Delete($pdid)
        LogComment "Delete: 0x$($hr.ToString("X"))"
        $hr | Should Be 0
        $packageDependencyIds.Remove($pdid)

        $rid = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageGraph]::RevisionId
        LogComment "RevisionId: $rid"
        $rid | Should Be 0
    }

    It "TryCreate + Add + Remove + Delete" {
        TraceEnter "TryCreate + Add + Remove + Delete"

        $rid = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageGraph]::RevisionId
        LogComment "RevisionId: $rid"
        $rid | Should Be 0

        $pdid = "before"
        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::TryCreate(
                $packageFamilyName,
                0,
                [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyProcessorArchitectures]::None,
                [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyLifetimeKind]::Process,
                "",
                [Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions]::None,
                [ref] $pdid)
        LogComment "TryCreate: 0x$($hr.ToString("X"))"
        LogComment "  PackageDependencyId: $pdid"
        $hr | Should Be 0
        $pdid | Should Not BeNullOrEmpty
        $packageDependencyIds.Add($pdid, $null)

        $pfn = "before"
        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetResolvedPackageFullName($pdid, [ref] $pfn)
        LogComment "GetResolvedPackageFullName: 0x$($hr.ToString("X"))"
        LogComment "  PackageFullName: $pfn"
        $hr | Should Be 0
        $pfn | Should BeNullOrEmpty

        $pdc = 0
        $pfn = "before"
        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Add(
                $pdid,
                [Microsoft.Windows.ApplicationModel.DynamicDependency.Rank]::Default,
                [Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions]::None,
                [ref] $pdc,
                [ref] $pfn)
        LogComment "Add: 0x$($hr.ToString("X"))"
        LogComment "  PackageDependencyContext: $pdc"
        LogComment "  PackageFullName: $pfn"
        $hr | Should Be 0
        $pdc | Should Not BeNullOrEmpty
        $packageDependencyContexts.Add($pdc, $null)
        $pfn | Should Not BeNullOrEmpty
        $packageDependencyContexts[$pdc] = $pfn

        $rid = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageGraph]::RevisionId
        LogComment "RevisionId: $rid"
        $rid | Should Be 1

        $id = "before"
        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetIdForContext($pdc, [ref] $id)
        LogComment "GetIdForContext: 0x$($hr.ToString("X"))"
        LogComment "  PackageDependencyId: $id"
        $hr | Should Be 0
        $id | Should Not BeNullOrEmpty

        $pfn = "before"
        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetResolvedPackageFullName($pdid, [ref] $pfn)
        LogComment "GetResolvedPackageFullName: 0x$($hr.ToString("X"))"
        LogComment "  PackageFullName: $pfn"
        $hr | Should Be 0
        $pfn | Should Not BeNullOrEmpty

        # New a WinRT type from the package dynamically added to our package graph"
        $widget = [Microsoft.Test.DynamicDependency.Widgets.Widget1,Microsoft.Test.DynamicDependency.Widgets.Widget1,ContentType=WindowsRuntime]::GetStatic()
        $widget | Format-Custom
        $widget | Should Not Be $null

        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Remove($pdc)
        LogComment "Remove: 0x$($hr.ToString("X"))"
        $hr | Should Be 0
        $packageDependencyContexts.Remove($pdc)

        $rid = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageGraph]::RevisionId
        LogComment "RevisionId: $rid"
        $rid | Should Be 2

        $pfn = "before"
        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetResolvedPackageFullName($pdid, [ref] $pfn)
        LogComment "GetResolvedPackageFullName: 0x$($hr.ToString("X"))"
        LogComment "  PackageFullName: $pfn"
        $hr | Should Be 0
        $pfn | Should BeNullOrEmpty

        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Delete($pdid)
        LogComment "Delete: 0x$($hr.ToString("X"))"
        $hr | Should Be 0
        $packageDependencyIds.Remove($pdid)

        $rid = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageGraph]::RevisionId
        LogComment "RevisionId: $rid"
        $rid | Should Be 2
    }

    It "Remove null" {
        TraceEnter "Remove null"

        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Remove([IntPtr]0)
        $hr | Should Be $E_INVALIDARG
    }

    It "Get RevisionId" {
        TraceEnter "Get RevisionId"

        $rid = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageGraph]::RevisionId
        LogComment "RevisionId: $rid"
        $rid | Should Not BeLessThan 0
    }

    It "GetResolvedPackageFullName null" {
        TraceEnter "GetResolvedPackageFullName null"

        $pdid = $null
        $pfn = "before"
        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetResolvedPackageFullName($pdid, [ref] $pfn)
        LogComment "HRESULT: 0x$($hr.ToString("X"))"
        LogComment "PackageFullName: $pfn"
        $hr | Should Be 0
        $pfn | Should Be $null
    }

    It "Delete null" {
        TraceEnter "Delete null"

        $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Delete([IntPtr]0)
        LogComment "HRESULT: 0x$($hr.ToString("X"))"
        $hr | Should Be 0
    }
}
