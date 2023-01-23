[CmdLetBinding()]
Param(
    [string]$Platform = "x64",
    [string]$OutputDirectory = ""
)

$ProgressPreference = "SilentlyContinue"
$ErrorActionPreference = "Stop"

$outputPath = Join-Path $OutputDirectory "vc_redist.$Platform.exe"
if(!(Test-Path $OutputDirectory))
{
    New-Item -ItemType Directory -Path $OutputDirectory | Out-Null
}

# Find direct download links at https://dotnet.microsoft.com/download/dotnet/5.0
$downloadurl = "https://aka.ms/vs/17/release/vc_redist.$Platform.exe"

if(!(Test-Path $outputPath))
{
    Write-Host "Downloading $downloadurl to $outputPath"
    Invoke-WebRequest $downloadurl -OutFile $outputPath
}
else
{
    Write-Host "The file '$outputPath' already exists. Skipping download."
}