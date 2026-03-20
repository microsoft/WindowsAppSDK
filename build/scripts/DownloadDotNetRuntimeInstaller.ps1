param(
    [Parameter(Mandatory=$true)]
    [string]$Platform,
    [Parameter(Mandatory=$true)]
    [string]$OutputDirectory
)

$ErrorActionPreference = "Stop"
Set-StrictMode -Version 3.0

# Find direct download links at https://dotnet.microsoft.com/download/dotnet/5.0
$downloadurlx86 = "https://download.visualstudio.microsoft.com/download/pr/c089205d-4f58-4f8d-ad84-c92eaf2f3411/5cd3f9b3bd089c09df14dbbfb64124a4/windowsdesktop-runtime-5.0.5-win-x86.exe"
$downloadurlx64 = "https://download.visualstudio.microsoft.com/download/pr/c1ef0b3f-9663-4fc5-85eb-4a9cadacdb87/52b890f91e6bd4350d29d2482038df1c/windowsdesktop-runtime-5.0.5-win-x64.exe"
$downloadurlArm64 = "https://download.visualstudio.microsoft.com/download/pr/1201ea91-3344-4745-9143-ad4f7eb0a88d/f04108de4f95817aa1b832061a467be0/dotnet-runtime-5.0.5-win-arm64.exe"

if ($Platform -eq "x86")
{
    $url = $downloadurlx86
}
elseif ($Platform -eq "x64")
{
    $url = $downloadurlx64
}
elseif ($Platform -eq "arm64")
{
    $url = $downloadurlArm64
}
else
{
    Write-Host "dotnet Desktop runtime not available for arch $Platform"
    return
}

$fileName = "dotnet-windowsdesktop-runtime-installer.exe"

& "$PSScriptRoot\Download-Package.ps1" -Url $url -OutputDirectory $OutputDirectory -FileName $fileName
exit $LASTEXITCODE

