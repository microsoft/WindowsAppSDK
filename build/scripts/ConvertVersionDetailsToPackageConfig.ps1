Param(
    [Parameter(Position=0)]
    [string]$versionDetailsPath = "",
    [Parameter(Position=1)]
    [string]$packageConfigPath = ""
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

[xml]$buildConfig = Get-Content -Path $versionDetailsPath

$packagesText =
@"
<?xml version="1.0" encoding="utf-8"?>
<packages>
	<!-- Transport packages from the feeder repositories -->

"@
foreach ($dependency in $buildConfig.Dependencies.ProductDependencies.Dependency)
{
    $name = $dependency.name
    $ver = $dependency.version
    Write-Host "id: " $name
    Write-Host "ver: " $ver

    if ($name -eq "Microsoft.WindowsAppSDK.AppLicensingInternal.TransportPackage")
    {
        Write-Host "##vso[task.setvariable variable=AppLicensingInternalPackageName;]$name"
        Write-Host "##vso[task.setvariable variable=AppLicensingInternalPackageVersion;]$ver"
    }

    $packagesText += '	<package id="' + $name + '" version="' + $ver + '" targetFramework="native" />
'

}
$packagesText +=
@"
</packages>
"@

Write-Host $packagesText

New-Item -Path $packageConfigPath -Type file -Force
Set-Content -Path $packageConfigPath -Value $packagesText