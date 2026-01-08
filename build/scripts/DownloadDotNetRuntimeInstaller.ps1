param(
    [Parameter(Mandatory=$true)]
    [string]$Platform,
    [Parameter(Mandatory=$true)]
    [string]$OutputDirectory
)

$ProgressPreference = "SilentlyContinue"
$ErrorActionPreference = "Stop"
Set-StrictMode -Version 3.0

$outputPath = Join-Path $OutputDirectory "dotnet-windowsdesktop-runtime-installer.exe"
if(-not(Test-Path $OutputDirectory))
{
    $null = New-Item -ItemType Directory -Path $OutputDirectory
}

# Find direct download links at https://dotnet.microsoft.com/download/dotnet/5.0
$downloadurlx86 = "https://download.visualstudio.microsoft.com/download/pr/c089205d-4f58-4f8d-ad84-c92eaf2f3411/5cd3f9b3bd089c09df14dbbfb64124a4/windowsdesktop-runtime-5.0.5-win-x86.exe"
$downloadurlx64 = "https://download.visualstudio.microsoft.com/download/pr/c1ef0b3f-9663-4fc5-85eb-4a9cadacdb87/52b890f91e6bd4350d29d2482038df1c/windowsdesktop-runtime-5.0.5-win-x64.exe"
$downloadurlArm64 = "https://download.visualstudio.microsoft.com/download/pr/1201ea91-3344-4745-9143-ad4f7eb0a88d/f04108de4f95817aa1b832061a467be0/dotnet-runtime-5.0.5-win-arm64.exe"

if($Platform -eq "x86")
{
    $downloadurl = $downloadurlx86
}
elseif($Platform -eq "x64")
{
    $downloadurl = $downloadurlx64
}
elseif($Platform -eq "arm64")
{
    $downloadurl = $downloadurlArm64
}
else
{
    Write-Host "dotnet Desktop runtime not available for arch $Platform"
    return
}

if(-not(Test-Path $outputPath))
{
    Write-Host "Downloading $downloadurl to $outputPath"
    Invoke-WebRequest $downloadurl -OutFile $outputPath -UseBasicParsing
}
else
{
    Write-Host "The file '$outputPath' already exists. Skipping download."
}
