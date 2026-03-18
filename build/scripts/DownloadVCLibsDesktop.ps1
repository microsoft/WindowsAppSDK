param(
    [Parameter(Mandatory=$true)]
    [string]$Platform,
    [Parameter(Mandatory=$true)]
    [string]$OutputDirectory
)

$ProgressPreference = "SilentlyContinue"
$ErrorActionPreference = "Stop"
Set-StrictMode -Version 3.0

$outputPath = Join-Path $OutputDirectory "Microsoft.VCLibs.$Platform.14.00.Desktop.appx"
if(-not(Test-Path $OutputDirectory))
{
    $null = New-Item -ItemType Directory -Path $OutputDirectory
}

# Find direct download links at https://learn.microsoft.com/en-us/troubleshoot/developer/visualstudio/cpp/libraries/c-runtime-packages-desktop-bridge
$downloadurl = "https://aka.ms/Microsoft.VCLibs.$Platform.14.00.Desktop.appx"

if(-not(Test-Path $outputPath))
{
    Write-Host "Downloading $downloadurl to $outputPath"
    Invoke-WebRequest $downloadurl -OutFile $outputPath -UseBasicParsing
}
else
{
    Write-Host "The file '$outputPath' already exists. Skipping download."
}
