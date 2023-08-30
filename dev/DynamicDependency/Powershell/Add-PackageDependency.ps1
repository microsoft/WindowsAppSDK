# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Add to the current process' package graph.

.DESCRIPTION
    Add a run-time reference for the package dependency created earlier via
    the TryCreate-PackageDependency cmdlet, with the specified options. After
    successful completion you can use content from the package.

.PARAMETER PackageDependencyId
    ID of the package dependency to be resolved and added to the invoking
    process' package graph. This parameter must match a package dependency
    defined by the TryCreate-PackageDependency cmdlet for the calling
    user or the system (via the TryCreate-PackageDependencyOptions -ScopeIsSystem option).

.PARAMETER Rank
    The rank to add the resolved package to the caller's package graph.
    For more information, see https://learn.microsoft.com/windows/win32/api/appmodel/nf-appmodel-addpackagedependency#remarks

.PARAMETER PrependIfRankCollision
    If multiple packages are present in the package graph with the same rank,
    the resolved package is added before others of the same rank. For more
    information, see https://learn.microsoft.com/windows/win32/api/appmodel/ne-appmodel-addpackagedependencyoptions

.LINK
    https://learn.microsoft.com/windows/win32/api/appmodel/nf-appmodel-addpackagedependency
#>
[CmdletBinding(SupportsShouldProcess=$true)]
param(
    [Parameter(Mandatory=$true)]
    [string]$PackageDependencyId,

    [int]$Rank=0,

    [switch]$PrependIfRankCollision
)

Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"

# Import the MSIX Dynamic Dependency module
if (-not (Get-Module | Where-Object {$_.Name -eq 'MsixDynamicDependency'}))
{
    $module = Join-Path $PSScriptRoot 'MsixDynamicDependency.psm1'
    Import-Module -Name $module -ErrorAction Stop
}

$options = [Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions]::None
if ($PrependIfRankCollision -eq $true)
{
    $options = $options -bor [Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions]::PrependIfRankCollision
}

$packageDependencyContext = [IntPtr]0
$packageFullName = ""
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Add(
        $PackageDependencyId, $Rank, $options, [ref] $packageDependencyContext, [ref] $packageFullName)
if ($hr -lt 0)
{
    $win32ex = [System.ComponentModel.Win32Exception]::new($hr)
    Write-Error "Error 0x$($hr.ToString('X')): $($win32ex.Message)" -ErrorAction Stop
}

$o = New-Object System.Object
$o | Add-Member -type NoteProperty -name "PackageDependencyContext" -value $packageDependencyContext
$o | Add-Member -type NoteProperty -name "PackageFullName" -value $packageFullName
$o
