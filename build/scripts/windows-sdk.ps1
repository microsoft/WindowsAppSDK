#
# This script launches sdksetup.exe from a folder under TEMP to mitigate potential conflicts with Visual Studio 2015.
#

param(
    # TODO: Use version, currently hardwire to only support 2 specific versions.
    [string]$SdkVersion = $null
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = "Stop"

function Assert-Executable
{
    Param
    (
        [String]$FilePath,
        $Response
    )

    # Throws, describing what was downloaded instead, unless the file starts like a Windows program.
    $bytes = New-Object byte[] 64
    $stream = [IO.File]::OpenRead($FilePath)
    try
    {
        $count = $stream.Read($bytes, 0, $bytes.Length)
        $length = $stream.Length
    }
    finally
    {
        $stream.Dispose()
    }

    if (($count -ge 2) -and ($bytes[0] -eq 0x4D) -and ($bytes[1] -eq 0x5A))
    {
        return
    }

    $start = ''
    if ($count -gt 0)
    {
        $start = -join ($bytes[0..($count - 1)] | ForEach-Object { if (($_ -ge 0x20) -and ($_ -lt 0x7F)) { [char]$_ } else { '.' } })
    }
    $contentType = ''
    if ($Response -and $Response.Headers.ContainsKey('Content-Type'))
    {
        $contentType = $Response.Headers['Content-Type']
    }
    throw "The download isn't a program: $length bytes, HTTP status $($Response.StatusCode), Content-Type '$contentType', starting '$start'."
}

function Install-EXE
{
    Param
    (
        [String]$Url,
        [String]$Name,
        [String[]]$ArgumentList
    )

    # A download occasionally gives a file that Windows can't start ("not a valid application for this OS platform"),
    # so check each download, and retry the download and the launch a few times before giving up.
    $maxAttempts = 3
    for ($attempt = 1; $attempt -le $maxAttempts; $attempt++)
    {
        try
        {
            # Download into a new folder each time, so a bad file from an earlier attempt can't get in the way.
            $folder = Join-Path $env:Temp ([Guid]::NewGuid().ToString('N'))
            New-Item -ItemType Directory -Path $folder | Out-Null
            $FilePath = Join-Path $folder $Name

            Write-Host "Downloading $Name..."
            $response = Invoke-WebRequest -Uri $Url -OutFile $FilePath -UseBasicParsing -PassThru
            Assert-Executable -FilePath $FilePath -Response $response

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
            Write-Host -Object "Failed to install the Executable $Name (attempt $attempt of $maxAttempts)"
            Write-Host -Object $_.Exception.Message
            if ($attempt -lt $maxAttempts)
            {
                Start-Sleep -Seconds (15 * $attempt)
            }
        }
    }

    return -1
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
