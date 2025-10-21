# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Return the process ids of processes using the package dependency.

.DESCRIPTION
    Return the process ids of processes using the package dependency.

    This does not add the package to the invoking process' package graph.

    NOTE: -All, -PackageDependencyId and -PackageFamilyName are mutually exclusive.

.PARAMETER PackageDependencyId
    Find package dependencies with this id.

.PARAMETER All
    Find all package dependencies.

.PARAMETER PackageFamilyName
    Find package dependencies with this package family.

.PARAMETER ScopeIsSystem
    Find package dependencies created with CreatePackageDependencyOptions_ScopeIsSystem.

.LINK
    https://learn.microsoft.com/windows/win32/api/appmodel/nf-appmodel-findpackagedependency
    https://learn.microsoft.com/windows/win32/api/appmodel/nf-appmodel-getpackagedependencyinformation
    https://learn.microsoft.com/windows/win32/api/appmodel/nf-appmodel-getprocessesusingpackagedependency
#>
[CmdletBinding(SupportsShouldProcess=$true)]
param(
    [Parameter(ParameterSetName='All')]
    [switch]$All,

    [Parameter(ParameterSetName='Id')]
    [string]$PackageDependencyId,

    [Parameter(ParameterSetName='Package')]
    [string]$PackageFamilyName,

    [switch]$ScopeIsSystem
)

Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"

$ERROR_SUCCESS = 0

function Is-PackageDependencyId
{
    param(
        [string]$id
    )

    if (($id -ne $null) -and ($id.Length -ge 3))
    {
        $prefix = $id.Substring(0, 2)
        return (($prefix -eq 'T:') -or ($prefix -eq 'P:'))
    }
    return $false
}

function Is-PackageFamilyName
{
    param(
        [string]$packageFamilyName
    )

    $rc = [Microsoft.Windows.ApplicationModel.PackageFamilyName]::Verify($packageFamilyName)
    return $rc == $ERROR_SUCCESS
}

function Get-Processes
{
    param(
        [string]$id
    )

    [uint32]$processIdsCount = 0
    [uint32[]]$processIds = $null
    $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetProcesses(
            $id, $ScopeIsSystem, [ref] $processIdsCount, [ref] $processIds)
    if ($hr -lt 0)
    {
        $win32ex = [System.ComponentModel.Win32Exception]::new($hr)
        Write-Error "Error 0x$($hr.ToString('X')): $($win32ex.Message)" -ErrorAction Stop
    }
    return $processIds
}

# Import the MSIX Dynamic Dependency module
if (-not (Get-Module | Where-Object {$_.Name -eq 'MsixDynamicDependency'}))
{
    $module = Join-Path $PSScriptRoot 'MsixDynamicDependency.psm1'
    Import-Module -Name $module -ErrorAction Stop
}

$ids = [ordered]@{}
if ($PSCmdlet.ParameterSetName -eq 'None')
{
    if ([string]::IsNullOrWhiteSpace($PackageDependencyId))
    {
        $All = $true
    }
    elseif (Is-PackageFamilyName $PackageDependencyId)
    {
        $PackageFamilyName = $PackageDependencyId
        $PackageDependencyId = $null
        $PSCmdlet.ParameterSetName = 'Package'
    }
    else
    {
        $PSCmdlet.ParameterSetName = 'Id'
    }
}



if (-not [string]::IsNullOrWhiteSpace($PackageDependencyId))
{
    $ids.Add($PackageDependencyId, $null)
}
else #if ($PSCmdlet.ParameterSetName -eq 'Package')
{
    $findPackageDependencyCriteria = New-Object Microsoft.Windows.ApplicationModel.DynamicDependency.FindPackageDependencyCriteria
    $findPackageDependencyCriteria.User = [IntPtr]::Zero
    $findPackageDependencyCriteria.ScopeIsSystem = $ScopeIsSystem
    if ($PSCmdlet.ParameterSetName -eq 'Package')
    {
        $findPackageDependencyCriteria.PackageFamilyName = $PackageFamilyName
    }
    else # -All
    {
        $findPackageDependencyCriteria.PackageFamilyName = "" #$null
    }
    [uint]$packageDependencyIdsCount = 0
    [string[]]$packageDependencyIds = $null
    $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Find(
            $findPackageDependencyCriteria, [ref] $packageDependencyIdsCount, [ref] $packageDependencyIds);
    if ($hr -lt 0)
    {
        $win32ex = [System.ComponentModel.Win32Exception]::new($hr)
        Write-Error "Error 0x$($hr.ToString('X')): $($win32ex.Message)" -ErrorAction Stop
    }
    else
    {
        Write-Host "Package Dependencies: $packageDependencyIdsCount"
    }
    ForEach ($pdi in $packageDependencyIds)
    {
        $ids.Add($pdi, $null)
    }
}

ForEach ($pdi in $ids.Keys)
{
    $pids = Get-Processes $pdi

    [string]$familyName = $null
    [ulong]$minVersion = 0
    $processorArchitectures = 0
    $lifetimeKind = 0
    [string]$lifetimeArtifact = $null
    $options = 0
    $lifetimeExpiration = New-Object DateTime
    $hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetInfo(
            $pdi, [ref] $familyName, [ref] $minVersion, [ref] $processorArchitectures,
            [ref] $lifetimeKind, [ref] $lifetimeArtifact, [ref] $options, [ref] $lifetimeExpiration)
    if ($hr -lt 0)
    {
        $win32ex = [System.ComponentModel.Win32Exception]::new($hr)
        Write-Error "Error 0x$($hr.ToString('X')): $($win32ex.Message)" -ErrorAction Stop
    }
    if ($lifetimeExpiration.Ticks -eq 0)
    {
        $lifetimeExpiration = $null
    }

    $packageFullName = .\Get-PackageDependencyResolved.ps1 $pdi

    $pd = [PSCustomObject]@{
        PackageDependencyId     = $pdi
        PackageFamilyName       = $familyName
        ResolvedPackage         = $packageFullName
        MinVersion              = $minVersion
        ProcessorArchitectures  = $processorArchitectures
        LifetimeKind            = $lifetimeKind
        LifetimeArtifact        = $lifetimeArtifact
        Options                 = $options
        LifetimeExpiration      = $lifetimeExpiration
        ProcessIDs              = $pids
    }
    $pd | Format-List
}
