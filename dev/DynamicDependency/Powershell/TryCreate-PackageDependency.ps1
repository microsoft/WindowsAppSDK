# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
TODO
#>
[CmdletBinding(SupportsShouldProcess=$true)]
param(
    [Parameter(Mandatory=$true)]
    [string]$PackageFamilyName,

    [long]$MinVersion,

    [switch]$NoVerifyDependencyResolution,
    [switch]$System,

    [ValidateSet('Process', 'File', 'Registry')]
    [string]$LifetimeKind,
    [string]$LifetimeArtifact
)

Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"

Write-Host $PSScriptRoot
ForEach ($path in $env:PSModulePath -Split ';')
{
    Write-Host $path
}

# Import the MSIX Dynamic Dependency module
$module = Join-Path $PSScriptRoot 'MsixDynamicDependency.psm1'
Import-Module -Name $module -Verbose:$false -ErrorAction Stop

$options = [Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions]::None
if ($NoVerifyDependencyResolution -eq $true)
{
    $options = $options -bor [Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions]::DoNotVerifyDependencyResolution
}
if ($System -eq $true)
{
    $options = $options -bor [Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions]::ScopeIsSystem
}

$lifetime = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyLifetimeKind]::Process
if ($LifetimeKind -eq 'File')
{
    $lifetime = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyLifetimeKind]::FilePath
}
elseif ($LifetimeKind -eq 'Registry')
{
    $lifetime = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyLifetimeKind]::RegistryKey
}

$architectures = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyProcessorArchitectures]::None
$pdid = ""
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::TryCreate(
        $PackageFamilyName, $MinVersion, $architectures, $lifetime, $LifetimeArtifact, $options, [ref] $pdid)
if ($hr -lt 0)
{
    $win32ex = [System.ComponentModel.Win32Exception]::new($hr)
    Write-Error "Error 0x$($hr.ToString('X')): $($win32ex.Message)" -ErrorAction Stop
}

$pdid
