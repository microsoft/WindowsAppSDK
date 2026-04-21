Param(
    [Parameter(Position=0)]
    [string]$directoryPackagesPropsPath = "",
    [Parameter(Position=1)]
    [string]$packageConfigPath = ""
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

# Read internal package versions from Directory.Packages.props (CPM).
# Discovers packages dynamically from the ItemGroup with Label="Internal WinAppSDK Packages".
# Internal packages use ValueOrDefault - extract the fallback version via regex.
$dppContent = Get-Content -Path $directoryPackagesPropsPath -Raw

# Find all PackageVersion entries inside the "Internal WinAppSDK Packages" ItemGroup.
# The regex captures each Include="<name>" ... Version="...'<fallback>')" pair within that group.
$groupMatch = [regex]::Match($dppContent, '<ItemGroup\s+Label="Internal WinAppSDK Packages">(.*?)</ItemGroup>', [System.Text.RegularExpressions.RegexOptions]::Singleline)
if (-not $groupMatch.Success) {
    Write-Host "ERROR: Could not find ItemGroup with Label='Internal WinAppSDK Packages' in $directoryPackagesPropsPath"
    exit 1
}
$groupContent = $groupMatch.Groups[1].Value

# Extract each package name and its fallback version from ValueOrDefault('$(WindowsAppSDKVersionPinned)', '<version>')
$packageMatches = [regex]::Matches($groupContent, 'Include="([^"]+)"\s+Version="\$\(\[MSBuild\]::ValueOrDefault\(''[^'']*'',\s*''([^'']+)''\)\)"')

$packagesText = @"
<?xml version="1.0" encoding="utf-8"?>
<packages>
        <!-- Transport packages - versions from Directory.Packages.props (CPM) -->

"@
foreach ($m in $packageMatches)
{
    $name = $m.Groups[1].Value
    $ver = $m.Groups[2].Value

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