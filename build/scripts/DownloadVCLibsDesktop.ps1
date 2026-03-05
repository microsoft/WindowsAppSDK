param(
    [Parameter(Mandatory=$true)]
    [string]$Platform,
    [Parameter(Mandatory=$true)]
    [string]$OutputDirectory
)

$ErrorActionPreference = "Stop"
Set-StrictMode -Version 3.0

$url = "https://aka.ms/Microsoft.VCLibs.$Platform.14.00.Desktop.appx"
$fileName = "Microsoft.VCLibs.$Platform.14.00.Desktop.appx"

& "$PSScriptRoot\Download-Package.ps1" -Url $url -OutputDirectory $OutputDirectory -FileName $fileName
exit $LASTEXITCODE

