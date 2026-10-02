# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Dynamically create a package dependency.

.DESCRIPTION
    Create a package dependency, using package family name, minimum version,
    and additional criteria.

.PARAMETER PackageDependencyId
    ID of the package dependency to be resolved and added to the invoking
    process' package graph. This parameter must match a package dependency
    defined by the TryCreate-PackageDependency cmdlet for the calling
    user or the system (via the TryCreate-PackageDependencyOptions -ScopeIsSystem option).

.PARAMETER MinVersion
    The minimum version of the target package on which to take a dependency.

.PARAMETER NoVerifyDependencyResolution
    Disables dependency resolution when pinning a package dependency. This is
    useful for installers running as user contexts other than the target user
    (for example, installers running as LocalSystem).

.PARAMETER System
    Defines the package dependency for the system, accessible to all users (by
    default, the package dependency is defined for a specific user). This
    option requires the caller has administrative privileges.

.PARAMETER LifetimeKind
    The type of artifact to use to define the lifetime of the package
    dependency. For more information, see
    https://learn.microsoft.com/windows/win32/api/appmodel/nf-appmodel-trycreatepackagedependency#remarks

.PARAMETER LifetimeArtifact
    The name of the artifact used to define the lifetime of the package
    dependency. N/A -LifetimeKind=Process. For more information, see
    https://learn.microsoft.com/windows/win32/api/appmodel/nf-appmodel-trycreatepackagedependency#remarks

.LINK
    https://learn.microsoft.com/windows/win32/api/appmodel/nf-appmodel-addpackagedependency
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

# Import the MSIX Dynamic Dependency module
if (-not (Get-Module | Where-Object {$_.Name -eq 'MsixDynamicDependency'}))
{
    $module = Join-Path $PSScriptRoot 'MsixDynamicDependency.psm1'
    Import-Module -Name $module -ErrorAction Stop
}

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
