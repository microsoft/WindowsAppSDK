# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Return the package full name if the package dependency is resolved.

.DESCRIPTION
    Return the package full name that would be used if the package dependency
    were to be resolved.

    This does not add the package to the invoking process' package graph.

.PARAMETER PackageDependencyId
    The ID of the resolved package dependency.

.LINK
    https://learn.microsoft.com/windows/win32/api/appmodel/nf-appmodel-getresolvedpackagefullnameforpackagedependency
#>
[CmdletBinding(SupportsShouldProcess=$true)]
param(
    [Parameter(Mandatory=$true)]
    [string]$PackageDependencyId
)

Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"

# Import the MSIX Dynamic Dependency module
if (-not (Get-Module | Where-Object {$_.Name -eq 'MsixDynamicDependency'}))
{
    $module = Join-Path $PSScriptRoot 'MsixDynamicDependency.psm1'
    Import-Module -Name $module -ErrorAction Stop
}

$packageFullName = ""
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetResolvedPackageFullName(
        $PackageDependencyId, [ref] $packageFullName)
if ($hr -lt 0)
{
    $win32ex = [System.ComponentModel.Win32Exception]::new($hr)
    Write-Error "Error 0x$($hr.ToString('X')): $($win32ex.Message)" -ErrorAction Stop
}

$packageFullName
