#
# This script launches sdksetup.exe from a folder under TEMP to mitigate potential conflicts with Visual Studio 2015.
#

param(
    # TODO: Use version, currently hardwire to only support 2 specific versions.
    [string]$SdkVersion = $null
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = "Stop"

function Install-EXE
{
    Param
    (
        [String]$Url,
        [String]$Name,
        [String[]]$ArgumentList
    )

    $exitCode = -1

    try
    {
        Write-Host "Downloading $Name..."
        $FilePath = "${env:Temp}\$Name"

        Invoke-WebRequest -Uri $Url -OutFile $FilePath -UseBasicParsing

        Write-Host "Starting Install $Name..."
        $process = Start-Process -FilePath $FilePath -ArgumentList $ArgumentList -Wait -PassThru
        $exitCode = $process.ExitCode

        if ($exitCode -eq 0 -or $exitCode -eq 3010)
        {
            Write-Host -Object 'Installation successful'
            return $exitCode
        }
        else
        {
            Write-Host -Object "Non zero exit code returned by the installation process : $exitCode."
            return $exitCode
        }
    }
    catch
    {
        Write-Host -Object "Failed to install the Executable $Name"
        Write-Host -Object $_.Exception.Message
        return -1
    }
}

$ErrorCodes = Data {
    ConvertFrom-StringData @'
    Success = 0
    NoScriptPath = 1
    InvalidArguments = 2
    AccessDenied = 3
    MissingSdkVersion = 4
    ScriptException = 5
'@
}

function PrintMessage($Message)
{
    Write-Host $Message
    if ($LogFile)
    {
        Out-File -FilePath $LogFile -InputObject $Message -Append
    }
}

function PrintMessageAndExit($Message, $ReturnCode)
{
    PrintMessage $Message
    exit $ReturnCode
}

#
# Main execution sequence
#

if ($SdkVersion -eq "10.1.17763")
{
    # Requires Windows SDK with the same version number as the WDK
    $winSdkUrl = "https://go.microsoft.com/fwlink/p/?LinkID=2023014"
    $wdkUrl = "https://go.microsoft.com/fwlink/?linkid=2026156"

    # `winsdksetup.exe /features + /quiet` installs all features without showing the GUI
    $sdkExitCode = Install-EXE -Url $winSdkUrl -Name "winsdksetup.exe" -ArgumentList ("/features", "+", "/quiet")

    if ($sdkExitCode -ne 0)
    {
        Write-Host "Failed to install the Windows SDK."
        exit $sdkExitCode
    }

    # `wdksetup.exe /features + /quiet` installs all features without showing the GUI
    $wdkExitCode = Install-EXE -Url $wdkUrl -Name "wdksetup.exe" -ArgumentList ("/features", "+", "/quiet")

    if ($wdkExitCode -ne 0)
    {
        Write-Host "Failed to install the Windows Driver Kit."
        exit $wdkExitCode
    }
}
elseif ($SdkVersion -eq "10.0.26100")
{
    # Install Windows SDK for Windows 11 (10.0.26100.4654).
    # Link came from https://developer.microsoft.com/en-us/windows/downloads/sdk-archive/
    $winSdkUrl = "https://go.microsoft.com/fwlink/?linkid=2327008"

    # `winsdksetup.exe /features + /quiet` installs all features without showing the GUI
    $sdkExitCode = Install-EXE -Url $winSdkUrl -Name "winsdksetup.exe" -ArgumentList ("/features", "+", "/quiet")

    if ($sdkExitCode -ne 0)
    {
        Write-Host "Failed to install the Windows SDK."
        exit $sdkExitCode
    }
}
else
{
    Write-Host -Object "WARNING: The supplied SdkVersion is current unsupported : $SdkVersion."
}

Write-Host "Done"
