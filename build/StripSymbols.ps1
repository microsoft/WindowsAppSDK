param(
    [parameter(mandatory)][string] $InputDirectory,
    [parameter(mandatory)][string] $OutputDirectory
)

$ErrorActionPreference = "Stop"
function Get-Is64Bit
{
    return $env:PROCESSOR_ARCHITECTURE -eq "AMD64"
}

function Get-DebuggingToolsRoot
{
    # Constants
    $windowsSDKRegPath = if (Get-Is64Bit) { "HKLM:\Software\WOW6432Node\Microsoft\Windows Kits\Installed Roots" } else { "HKLM:\Software\Microsoft\Windows Kits\Installed Roots" }
    $windowsDebuggingToolsRegRootKey = "WindowsDebuggersRoot10"

    try
    {
        return Get-ItemProperty -Path $windowsSDKRegPath | Select-Object -ExpandProperty $windowsDebuggingToolsRegRootKey
    }
    catch
    {
        return $null
    }
}

function Remove-PrivateSymbolInformation(
    [parameter(mandatory)][ValidateNotNullOrEmpty()] [string] $inputPdbPath,
    [parameter(mandatory)][ValidateNotNullOrEmpty()] [string] $outputPdbPath)
{
    $debuggingToolsRoot = Get-DebuggingToolsRoot
    if (Get-Is64Bit)
    {
        $pdbCopy = Join-Path $debuggingToolsRoot "x64\pdbcopy.exe"
    }
    else
    {
        $pdbCopy = Join-Path $debuggingToolsRoot "x86\pdbcopy.exe"
    }

    $arguments = "$inputPdbPath $outputPdbPath -p"

    Write-Host "$inputPdbPath => $outputPdbPath"
    Start-Process -Wait -NoNewWindow $pdbCopy $arguments
} 

Write-Host -NoNewline "Checking for installed Debugging Tools for Windows..."

$debuggingToolsRoot = Get-DebuggingToolsRoot
if ($debuggingToolsRoot)
{
    Write-Host -ForegroundColor Green "FOUND"
}
else
{
    Write-Host -ForegroundColor Yellow "MISSING"
}

if (Test-Path $OutputDirectory)
{
    Remove-Item -Recurse $OutputDirectory
}
New-Item -ItemType Directory $OutputDirectory | Out-Null

Write-Host "Stripping private information from symbols..."

foreach ($inputPdb in (Get-ChildItem -Recurse -Filter "*.pdb" $InputDirectory))
{
    $outputPdbDir = $inputPdb.DirectoryName -replace [regex]::Escape($InputDirectory), $OutputDirectory

    if (!(Test-Path $outputPdbDir))
    {
        New-Item -ItemType Directory $outputPdbDir | Out-Null
    }

    $inputPdbPath = $inputPdb.FullName
    $outputPdbPath = Join-Path $outputPdbDir $inputPdb.Name
    Remove-PrivateSymbolInformation $inputPdbPath $outputPdbPath
}
