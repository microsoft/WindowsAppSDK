param(
    [Parameter(Mandatory=$true)]
    [string]$Platform,
    [Parameter(Mandatory=$true)]
    [string]$OutputDirectory
)

$ErrorActionPreference = "Stop"
Set-StrictMode -Version 3.0

# Find direct download links at https://learn.microsoft.com/en-US/cpp/windows/latest-supported-vc-redist?view=msvc-170
$url = "https://aka.ms/vs/17/release/vc_redist.$Platform.exe"
$fileName = "vc_redist.$Platform.exe"

& "$PSScriptRoot\Download-Package.ps1" -Url $url -OutputDirectory $OutputDirectory -FileName $fileName
exit $LASTEXITCODE

