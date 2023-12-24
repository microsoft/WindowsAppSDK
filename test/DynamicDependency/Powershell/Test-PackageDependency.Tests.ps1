# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"

# Repository paths
$root = (Get-Item $PSScriptRoot).parent.parent.parent.FullName
$dev = Join-Path $root 'dev'
$test = Join-Path $root 'test'
$buildOutput = Join-Path $root 'BuildOutput\Debug\x64'
$cmdlet = Join-Path $dev 'DynamicDependency\Powershell'

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

Describe "DynamicDependency cmdlets" {

    BeforeAll {
        Trace "BeforeAll"

        RemoveTestPackages
        AddTestPackages
    }

    AfterAll {
        Trace "AfterAll"

        CleanupPackageDependencies
        RemoveTestPackages
    }

    It "Get-PackageGraphRevisionId (expect 0)" {
        TraceEnter "Get-PackageGraphRevisionId (expect 0)"

        $rid = & "$cmdlet\Get-PackageGraphRevisionId.ps1"
        $rid | Should Be 0
    }

    It "TryCreate + Delete" {
        TraceEnter "TryCreate + Delete"

        $rid = & "$cmdlet\Get-PackageGraphRevisionId.ps1"
        LogComment "RevisionId: $rid"
        $rid | Should Be 0

        LogComment "TryCreate-PackageDependency"
        $pdid = "before"
        $pdid = & "$cmdlet\TryCreate-PackageDependency.ps1" -PackageFamilyName $packageFamilyName -MinVersion 0 -LifetimeKind Process
        LogComment "  PackageDependencyId: $pdid"
        $pdid | Should Not BeNullOrEmpty
        $packageDependencyIds.Add($pdid, $null)

        $rid = & "$cmdlet\Get-PackageGraphRevisionId.ps1"
        LogComment "RevisionId: $rid"
        $rid | Should Be 0

        LogComment "Get-PackageDependencyResolved"
        $pfn = "before"
        $pfn = & "$cmdlet\Get-PackageDependencyResolved.ps1" -PackageDependencyId $pdid
        LogComment "  PackageFullName: $pfn"
        $pfn | Should BeNullOrEmpty

        LogComment "Delete"
        & "$cmdlet\Delete-PackageDependency.ps1" -PackageDependencyId $pdid
        $packageDependencyIds.Remove($pdid)

        $rid = & "$cmdlet\Get-PackageGraphRevisionId.ps1"
        LogComment "RevisionId: $rid"
        $rid | Should Be 0
    }

    It "TryCreate + Add + Remove + Delete" {
        TraceEnter "TryCreate + Delete"

        $rid = & "$cmdlet\Get-PackageGraphRevisionId.ps1"
        LogComment "RevisionId: $rid"
        $rid | Should Be 0

        LogComment "TryCreate-PackageDependency"
        $pdid = "before"
        $pdid = & "$cmdlet\TryCreate-PackageDependency.ps1" -PackageFamilyName $packageFamilyName -MinVersion 0 -LifetimeKind Process
        LogComment "  PackageDependencyId: $pdid"
        $pdid | Should Not BeNullOrEmpty
        $packageDependencyIds.Add($pdid, $null)

        $rid = & "$cmdlet\Get-PackageGraphRevisionId.ps1"
        LogComment "RevisionId: $rid"
        $rid | Should Be 0

        LogComment "Get-PackageDependencyResolved"
        $pfn = "before"
        $pfn = & "$cmdlet\Get-PackageDependencyResolved.ps1" -PackageDependencyId $pdid
        LogComment "  PackageFullName: $pfn"
        $pfn | Should BeNullOrEmpty

        LogComment "Add-PackageDependency"
        $pdc = 0
        $pfn = "before"
        $h = & "$cmdlet\Add-PackageDependency.ps1" -PackageDependencyId $pdid
        $pdc = $h.PackageDependencyContext
        $pfn = $h.PackageFullName
        LogComment "  PackageDependencyContext: $pdc"
        LogComment "  PackageFullName: $pfn"
        $pdc | Should Not BeNullOrEmpty
        $packageDependencyContexts.Add($pdc, $null)
        $pfn | Should Not BeNullOrEmpty
        $packageDependencyContexts[$pdc] = $pfn

        $rid = & "$cmdlet\Get-PackageGraphRevisionId.ps1"
        LogComment "  RevisionId: $rid"
        $rid | Should Be 1

        LogComment "Get-PackageDependencyIdForContext"
        $id = "before"
        $id = & "$cmdlet\Get-PackageDependencyIdForContext.ps1" -PackageDependencyContext $pdc
        LogComment "  PackageDependencyId: $id"
        $id | Should Not BeNullOrEmpty

        LogComment "Get-PackageDependencyResolved"
        $pfn = "before"
        $pfn = & "$cmdlet\Get-PackageDependencyResolved.ps1" -PackageDependencyId $pdid
        LogComment "  PackageFullName: $pfn"

        # New a WinRT type from the package dynamically added to our package graph"
        $widget = [Microsoft.Test.DynamicDependency.Widgets.Widget1,Microsoft.Test.DynamicDependency.Widgets.Widget1,ContentType=WindowsRuntime]::GetStatic()
        $widget | Format-Custom
        $widget | Should Not Be $null

        LogComment "Remove"
        & "$cmdlet\Remove-PackageDependency.ps1" -PackageDependencyContext $pdc
        $packageDependencyContexts.Remove($pdc)

        $rid = & "$cmdlet\Get-PackageGraphRevisionId.ps1"
        LogComment "RevisionId: $rid"
        $rid | Should Be 2

        LogComment "Get-PackageDependencyResolved"
        $pfn = "before"
        $pfn = & "$cmdlet\Get-PackageDependencyResolved.ps1" -PackageDependencyId $pdid
        LogComment "  PackageFullName: $pfn"
        $pfn | Should BeNullOrEmpty

        LogComment "Delete"
        & "$cmdlet\Delete-PackageDependency.ps1" -PackageDependencyId $pdid
        $packageDependencyIds.Remove($pdid)

        $rid = & "$cmdlet\Get-PackageGraphRevisionId.ps1"
        LogComment "RevisionId: $rid"
        $rid | Should Be 2
    }

    It "Remove null" {
        TraceEnter "Remove null"

        $scriptBlock = { & "$cmdlet\Delete-PackageDependency.ps1" -PackageDependencyId $null }
        $scriptBlock | Should Throw "Cannot bind argument to parameter 'PackageDependencyId' because it is an empty string."
    }

    It "Get RevisionId" {
        TraceEnter "Get RevisionId"

        $rid = & "$cmdlet\Get-PackageGraphRevisionId.ps1"
        LogComment "RevisionId: $rid"
        $rid | Should Not BeLessThan 0
    }

    It "GetResolvedPackageFullName null" {
        TraceEnter "GetResolvedPackageFullName null"

        LogComment "Get-PackageDependencyResolved"
        $scriptBlock = { & "$cmdlet\Get-PackageDependencyResolved.ps1" -PackageDependencyId $null }
        $scriptBlock | Should Throw "Cannot bind argument to parameter 'PackageDependencyId' because it is an empty string."
    }

    It "Delete null" {
        TraceEnter "Delete null"

        $scriptBlock = { & "$cmdlet\Delete-PackageDependency.ps1" -PackageDependencyId $null -ErrorAction Stop }
        $scriptBlock | Should Throw "Cannot bind argument to parameter 'PackageDependencyId' because it is an empty string."
    }
}
