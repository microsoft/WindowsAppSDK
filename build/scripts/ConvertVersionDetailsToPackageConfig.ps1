Param(
    [Parameter(Position=0)]
    [string]$directoryPackagesPropsPath = "",
    [Parameter(Position=1)]
    [string]$packageConfigPath = ""
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

# Read internal package versions from Directory.Packages.props (CPM).
# Internal packages use ValueOrDefault - extract the fallback version via regex.
$dppContent = Get-Content -Path $directoryPackagesPropsPath -Raw

# Internal packages to include in packages.config (transport + component packages)
$internalPackageNames = @(
    'Microsoft.FrameworkUdk',
    'Microsoft.ProjectReunion.InteractiveExperiences.TransportPackage',
    'Microsoft.WindowsAppSDK.AppLicensingInternal.TransportPackage',
    'Microsoft.WindowsAppSDK.Base',
    'Microsoft.WindowsAppSDK.InteractiveExperiences'
)

$packagesText = @"
<?xml version="1.0" encoding="utf-8"?>
<packages>
        <!-- Transport packages - versions from Directory.Packages.props (CPM) -->

"@
foreach ($name in $internalPackageNames)
{
    # Extract fallback version from ValueOrDefault('$(WindowsAppSDKVersionPinned)', '<version>')
    $escapedName = [regex]::Escape($name)
    $match = [regex]::Match($dppContent, "Include=""$escapedName""\s+Version=""\`$\(\[MSBuild\]::ValueOrDefault\('[^']*',\s*'([^']+)'\)\)""")
    if ($match.Success) {
        $ver = $match.Groups[1].Value
    } else {
        Write-Host "WARNING: Could not find version for $name in Directory.Packages.props"
        continue
    }

    Write-Host "id:  $name"
    Write-Host "ver: $ver"

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