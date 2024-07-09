param(
    [Parameter(Position=0)]
    [string]$version = "",
    [switch]$skipLKG
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

$dotnetInstallScript = "$env:TEMP\dotnet-install.ps1"

$repoInstallDir  = [System.IO.Path]::GetFullPath("$PSScriptRoot\..\.dotnet")
$filename = "$PSScriptRoot\..\..\..\eng\Versions.Dependencies.props"
$xml = [xml](Get-Content $filename -EA:Stop)
$dotNotSdkVersion = $xml.SelectSingleNode("/Dependencies/ToolsetDependencies/Dependency[@Name='CsWinRT.Dependency.DotNetCoreSdk']").Version
$dotNotSdkVersionLkg = if (-not $skipLKG) $dotNotSdkVersion

if ($version -ne "")
{
    $dotNetSdkVersion = $version
}
# Use-RunAs function from TechNet Script Gallery
# https://gallery.technet.microsoft.com/scriptcenter/63fd1c0d-da57-4fb4-9645-ea52fc4f1dfb
function Use-RunAs {
    # Check if script is running as Adminstrator and if not use RunAs
    # Use Check Switch to check if admin
    param([Switch]$Check)

    $IsAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()`
        ).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")

    if ($Check) {
        return $IsAdmin
    }
    if ($MyInvocation.ScriptName -ne "") {
        if (-not $IsAdmin) {

            try {
                $arg = "-file `"$($MyInvocation.ScriptName)`""
                Write-Host "Installing .NET SDK (requires elevation)..."

                Write-Verbose "$psHome\powershell.exe -Verb RunAs -ArgumentList $arg -ErrorAction 'stop' -Wait"
                Start-Process "$psHome\powershell.exe" -Verb RunAs -ArgumentList $arg -ErrorAction 'stop' -Wait

                if (-not $latestAlreadyInstalled)
                {
                    Write-Host "Installed SDK (x64) version $dotNetSdkVersion to $x64InstallDir."
                    Write-Host "Installed SDK (x86) version $dotNetSdkVersion to $x86InstallDir."
                }

                if (-not $lkgAlreadyInstalled)
                {
                    Write-Host "Installed SDK (x64) version $dotNetSdkVersionLkg to $x64InstallDir."
                    Write-Host "Installed SDK (x86) version $dotNetSdkVersionLkg to $x86InstallDir."
                }
            }
            catch {
                Write-Warning "Error - Failed to restart script with runas"

                Write-Warning "$Error[0]"
                break
            }
            Exit # Quit this session of powershell
        }
    }
    else {
        Write-Warning "Error - Script must be saved as a .ps1 file first"
        break
    }
}
function Is-Installed
{
    param ([string]$version)
    $dotNetSdkVersionRegex = ([regex]"(.*?) \[(.*?)\]")

    $installed = $false
    Invoke-Expression "dotnet --list-sdks" | ForEach-Object {
        $sdkVersionMatch = $dotNetSdkVersionRegex.Match($_)
        $versionNumber = $sdkVersionMatch.Groups[1].Value
        $installPath = $sdkVersionMatch.Groups[2].Value

        # Ignore any SDKs installed to the repo directory - those ones won't be picked up by Visual Studio by default.
        if (-not $installPath.StartsWith($repoInstallDir, [StringComparison]::OrdinalIgnoreCase))
        {
            if ($versionNumber -imatch $version)
            {
                $installed = $true
                Write-Host ".NET SDK $versionNumber already installed"
            }
            elseif ($version.Contains("rtm") -and $version.StartsWith($versionNumber))
            {
                # For rtm version, the sdk version we could install with the script looks like
                # 5.0.100-rtm.20522.4, but the final version of the sdk will just be something like
                # 5.0.100.
                $installed = $true
                Write-Host ".NET SDK $versionNumber already installed"
            }
        }
    }

    return $installed
}

$x64InstallDir  = $repoInstallDir
$x86InstallDir  = "$x64InstallDir\x86"

# If we're not on a lab machine, we'll install to the program files directory,
# which enables solution files built using this .NET SDK to be opened directly from Visual Studio
# without needing to go through a command line that has run init.cmd.

$latestAlreadyInstalled = Is-Installed $dotNetSdkVersion
$lkgAlreadyInstalled = $true

# Only try to install the lkg sdk if specified
if ((-not [string]::IsNullOrEmpty($dotNetSdkVersionLkg)) -and ($dotNetSdkVersionLkg -ine '$(CsWinRTDependencyDotNetCoreSdkPackageVersion)'))
{
    $lkgAlreadyInstalled = Is-Installed $dotNetSdkVersionLkg
}

if (-not $env:AGENT_BUILDDIRECTORY)
{
    $x64InstallDir  = "$env:ProgramFiles\dotnet"
    $x86InstallDir  = "${env:ProgramFiles(x86)}\dotnet"
    $sdksAlreadyInstalled = Is-Installed $dotNetSdkVersion

    # Only try to install the lkg sdk if specified
    if (-not [string]::IsNullOrEmpty($dotNetSdkVersionLkg))
    {
        $lkgInstalled = Is-Installed $dotNetSdkVersionLkg
        $sdksAlreadyInstalled = $sdksAlreadyInstalled -And $lkgInstalled
    }

    if ($latestAlreadyInstalled -And $lkgAlreadyInstalled)
    {
        Write-Host ".NET SDKs already installed"
        Exit
    }

    Use-RunAs
}
function Install-SDK
{
    param ([string]$version, [string]$channel)
    . $dotnetInstallScript -Channel $channel -Version $version -InstallDir $x64InstallDir -Architecture x64
    Write-Host "Installed SDK (x64) version $version from channel $channel to $x64InstallDir."

    . $dotnetInstallScript -Channel $channel -Version $version -InstallDir $x86InstallDir -Architecture x86
    Write-Host "Installed SDK (x86) version $version to $x86InstallDir."

    Write-Host -ForegroundColor Green Done.
}

Write-Host "Installing .NET SDK..."

[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.SecurityProtocolType]'Ssl3,Tls,Tls11,Tls12'

Invoke-WebRequest https://dot.net/v1/dotnet-install.ps1 -OutFile $dotnetInstallScript

if (-not $latestAlreadyInstalled)
{
    Install-SDK -version $dotNetSdkVersion -channel "release\5.0.1xx"
}

if (-not $lkgAlreadyInstalled)
{
    Install-SDK -version $dotNetSdkVersionLkg -channel "master"
}
