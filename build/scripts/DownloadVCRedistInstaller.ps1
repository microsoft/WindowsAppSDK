param(
    [Parameter(Mandatory=$true)]
    [string]$Platform,
    [Parameter(Mandatory=$true)]
    [string]$OutputDirectory
)

$ProgressPreference = "SilentlyContinue"
$ErrorActionPreference = "Stop"
Set-StrictMode -Version 3.0

$outputPath = Join-Path $OutputDirectory "vc_redist.$Platform.exe"
if(-not(Test-Path $OutputDirectory))
{
    $null = New-Item -ItemType Directory -Path $OutputDirectory
}

# Find direct download links at https://learn.microsoft.com/en-US/cpp/windows/latest-supported-vc-redist?view=msvc-170
$downloadurl = "https://aka.ms/vs/17/release/vc_redist.$Platform.exe"

if(-not(Test-Path $outputPath))
{
    Write-Host "Downloading $downloadurl to $outputPath"
    Invoke-WebRequest $downloadurl -OutFile $outputPath -UseBasicParsing
}
else
{
    Write-Host "The file '$outputPath' already exists. Skipping download."
}
