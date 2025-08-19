
param(
    [Parameter(Mandatory=$true)]
    [string]$Platform,
    [Parameter(Mandatory=$true)]
    [string]$OutputDirectory
)

$ProgressPreference = "SilentlyContinue"
$ErrorActionPreference = "Stop"
Set-StrictMode -Version 3.0

$outputPath = Join-Path $OutputDirectory "Microsoft.VCLibs.$Platform.14.00.UWPDesktop.appx"
if(-not(Test-Path $OutputDirectory))
{
    $null = New-Item -ItemType Directory -Path $OutputDirectory
}

# UWPDesktop packages are distributed with Visual Studio SDK, not via web download
# Check Visual Studio SDK location first
$vsSDKPath = "${env:ProgramFiles(x86)}\Microsoft SDKs\Windows Kits\10\ExtensionSDKs\Microsoft.VCLibs.Desktop\14.0\Appx\Retail\$Platform\Microsoft.VCLibs.$Platform.14.00.UWPDesktop.appx"

if(Test-Path $vsSDKPath)
{
    Write-Host "Copying UWPDesktop VCLibs from Visual Studio SDK: $vsSDKPath"
    Copy-Item $vsSDKPath $outputPath
}
else
{
    Write-Host "WARNING: UWPDesktop VCLibs not found in Visual Studio SDK at: $vsSDKPath"
    Write-Host "UWPDesktop packages are not available for web download. Please install Visual Studio with UWP workload."
    Write-Host "Skipping UWPDesktop VCLibs download."
}
