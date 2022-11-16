# Use pdbcopy to strip private information from all
# pdbs in the $InputDirectory and place the new pdbs
# in the $OutputDirectory

param(
    [parameter(mandatory)][string] $InputDirectory,
    [parameter(mandatory)][string] $OutputDirectory,
    [string] $WindowsBuildNumber = [string] "19041",
    [string] $Verbosity = "quiet",
    [string] $LogsDirectory
)

$ErrorActionPreference = "Stop"

Import-Module -Name $PSScriptRoot\WindowsSdkInstallerFunctions.psm1 -DisableNameChecking -Force

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

function Install-DebuggingTools(
    [parameter(mandatory)][ValidateNotNullOrEmpty()] [string] $buildNumber)
{
    $installerPath = Ensure-WindowsSDKInstaller $buildNumber

    try
    {
        Write-Host -NoNewLine "Installing Debugging Tools for Windows..."

        $windowsSDKOptions = @("OptionId.WindowsDesktopDebuggers")

        $options = "/features $($windowsSDKOptions -join " ")"
        if ($Verbosity -eq "quiet") { $options += " /q" }
        if ($LogsDirectory) { $options += " /log $LogsDirectory\DebuggingToolsInstall.log" }

        Start-Process -Wait $installerPath $options

        Write-Host -ForegroundColor Green "OK"
    }
    catch
    {
        Write-Host -ForegroundColor Red "FAILED"
        Write-Host -ForegroundColor Red "Error: $PSItem"
        throw
    }

    return $installerPath
}

function Uninstall-DebuggingTools(
    [parameter(mandatory)][ValidateNotNullOrEmpty()] [string] $installerPath)
{
    try
    {
        Write-Host -NoNewLine "Uninstalling Debugging Tools for Windows..."

        $windowsSDKOptions = @("OptionId.WindowsDesktopDebuggers")

        $options = "/uninstall /features $($windowsSDKOptions -join " ")"
        if ($Verbosity -eq "quiet") { $options += " /q" }
        if ($LogsDirectory) { $options += " /log $LogsDirectory\DebuggingToolsUninstall.log" }

        Start-Process -Wait $installerPath $options

        Write-Host -ForegroundColor Green "OK"
    }
    catch
    {
        Write-Host -ForegroundColor Red "FAILED"
        Write-Host -ForegroundColor Red "Error: $PSItem"
        throw
    }

    Cleanup-WindowsSDKInstaller $installerPath
}

function Strip-PrivateInformation(
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

$installerPath = $null
try
{
    Write-Host -NoNewLine "Checking for installed Debugging Tools for Windows..."

    $debuggingToolsRoot = Get-DebuggingToolsRoot
    if (!$debuggingToolsRoot)
    {
        Write-Host -ForegroundColor Yellow "MISSING"

        $installerPath = Install-DebuggingTools $WindowsBuildNumber
        $debuggingToolsRoot = Get-DebuggingToolsRoot
    }
    else
    {
        Write-Host -ForegroundColor Green "FOUND"
    }

    Write-Host "Stripping private information from symbols..."

    if (Test-Path $OutputDirectory)
    {
        Remove-Item -Recurse $OutputDirectory
    }
    New-Item -ItemType Directory $OutputDirectory | Out-Null

    foreach ($pdb in (Get-ChildItem -Recurse -Filter "*.pdb" $InputDirectory))
    {
        $inputPdbPath = $pdb.FullName
        $outputPdbPath = Join-Path $OutputDirectory $pdb.Name
        Strip-PrivateInformation $inputPdbPath $outputPdbPath
    }

    Write-Host -ForegroundColor Green "Finished."
}
finally
{
    # If we installed the debugging tools, uninstall them as part of cleanup
    if ($installerPath)
    {
        Uninstall-DebuggingTools $installerPath
    }
}