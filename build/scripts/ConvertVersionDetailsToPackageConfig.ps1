Param(
    [Parameter(Position=0)]
    [string]$versionDetailsPath = "",
    [Parameter(Position=1)]
    [string]$packageConfigPath = ""
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

# Read internal package versions from eng\Version.Dependencies.props (CPM).
# The parameter is still called versionDetailsPath for backward compatibility with
# pipeline YAML that passes it, but we now read Version.Dependencies.props from the
# same eng\ directory.
$engDir = Split-Path $versionDetailsPath -Parent
$versionDepsPropsPath = Join-Path $engDir 'Version.Dependencies.props'
[xml]$propsXml = Get-Content -Path $versionDepsPropsPath

# Extract internal package name->version pairs from the PropertyGroup
$internalPackages = @{
    'Microsoft.FrameworkUdk' = $propsXml.Project.PropertyGroup.MicrosoftFrameworkUdkPackageVersion
    'Microsoft.ProjectReunion.InteractiveExperiences.TransportPackage' = $propsXml.Project.PropertyGroup.MicrosoftProjectReunionInteractiveExperiencesTransportPackagePackageVersion
    'Microsoft.WindowsAppSDK.AppLicensingInternal.TransportPackage' = $propsXml.Project.PropertyGroup.MicrosoftWindowsAppSDKAppLicensingInternalTransportPackagePackageVersion
    'Microsoft.WindowsAppSDK.Base' = $propsXml.Project.PropertyGroup.MicrosoftWindowsAppSDKBasePackageVersion
    'Microsoft.WindowsAppSDK.InteractiveExperiences' = $propsXml.Project.PropertyGroup.MicrosoftWindowsAppSDKInteractiveExperiencesPackageVersion
}

$packagesText = @"
<?xml version="1.0" encoding="utf-8"?>
<packages>
        <!-- Transport packages - versions from eng/Version.Dependencies.props (CPM) -->

"@
foreach ($entry in $internalPackages.GetEnumerator())
{
    $name = $entry.Key
    $ver = $entry.Value
    Write-Host "id: " $name
    Write-Host "ver: " $ver

    if ($name -eq "Microsoft.WindowsAppSDK.AppLicensingInternal.TransportPackage")
    {
        Write-Host "##vso[task.setvariable variable=AppLicensingInternalPackageName;]$name"
        Write-Host "##vso[task.setvariable variable=AppLicensingInternalPackageVersion;]$ver"
    }

    $packagesText += '  <package id="' + $name + '" version="' + $ver + '" targetFramework="native" />
'

}
$packagesText += @"
</packages>
"@

Write-Host $packagesText

New-Item -Path $packageConfigPath -Type file -Force
Set-Content -Path $packageConfigPath -Value $packagesText