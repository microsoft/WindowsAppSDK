[CmdLetBinding()]
Param(
    [string]$Platform = "x64",
    [string]$OutputDirectory = "D:\WindowsAppSDK\build\scripts"
)

$ProgressPreference = "SilentlyContinue"
$ErrorActionPreference = "Stop"

$outputPath = Join-Path $OutputDirectory "Microsoft.VCLibs.$Platform.14.00.Desktop.appx"
if(!(Test-Path $OutputDirectory))
{
    New-Item -ItemType Directory -Path $OutputDirectory | Out-Null
}

# Find direct download links at https://learn.microsoft.com/en-us/troubleshoot/developer/visualstudio/cpp/libraries/c-runtime-packages-desktop-bridge
$downloadurl = "https://aka.ms/Microsoft.VCLibs.$Platform.14.00.Desktop.appx"

if(!(Test-Path $outputPath))
{
    Write-Host "Downloading $downloadurl to $outputPath"
    Invoke-WebRequest $downloadurl -OutFile $outputPath
}
else
{
    Write-Host "The file '$outputPath' already exists. Skipping download."
}