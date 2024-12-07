# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Verify the environment for Windows App SDK development

.DESCRIPTION
    Review the current environment and fix or warn if anything is amiss. This includes...
    * Developer mode is enabled
    * Test certificate to sign test MSIX packages is installed
    * TAEF service is installed and running
    * Visual Studio 2022 is installed and properly configured
    * Dependencies in use are in the approved list of packages and versions

.PARAMETER CertPassword
    Password for new certificates

.PARAMETER Clean
    Run as if it's the first time (ignore any previous cached artifacts from previous runs).

.PARAMETER CheckAll
    Check all. If not specified this is set to true if all other -Check... options are false

.PARAMETER CheckDependencies
    Verify dependencies in projects (*proj, packages.config, eng\Version.*.props) match defined dependencies (eng\Version.*.xml)

.PARAMETER CheckDeveloperMode
    Check developer mode

.PARAMETER CheckTAEFService
    Check the TAEF service

.PARAMETER CheckTestCert
    Check the Test certificate

.PARAMETER CheckTestPfx
    Check the MSIX Test signing certificate (to sign developer test MSIXs)

.PARAMETER CheckVisualStudio
    Check Visual Studio

.PARAMETER NoInteractive
    Run in non-interactive mode (fail if any need for user input)

.PARAMETER InstallWindowsSDK
    Download and install Windows Platform SDKs (if necessary).

.PARAMETER Offline
    Do not access the network

.PARAMETER OnlineVSWhere
    Download and use the latest vswhere.exe on the network

.PARAMETER RemoveAll
    Remove all

.PARAMETER RemoveTestCert
    Remove the Test certificate (i.e. undoc CheckTestCert)

.PARAMETER RemoveTestPfx
    Remove the MSIX Test signing certificate (i.e. undoc CheckTestPfx)

.PARAMETER SaveSettingsFile
    Save settings file

.PARAMETER SaveUserSettingsFile
    Save settings file

.PARAMETER Settings
    Load settings file

.PARAMETER SettingsFile
    Settings file to load (if present). Relative filenames are resolved to .user directory. Default="DevCheck-Settings.ps1"

.PARAMETER ShowSystemInfo
    Display system information

.PARAMETER StartTAEFService
    Start the TAEF service

.PARAMETER StopTAEFService
    Stop the TAEF service

.PARAMETER SyncDependencies
    Update dependencies (*proj, packages.config, eng\Version.*.props) to match defined dependencies (eng\Version.*.xml)

.PARAMETER UserSettings
    Load settings file

.PARAMETER UserSettingsFile
    Settings file to load (if present). Relative filenames are resolved to .user directory.

.PARAMETER Verbose
    Display detailed information

.EXAMPLE
    DevCheck -Verbose
#>

Param(
    [SecureString]$CertPassword=$null,

    [String]$CertPasswordFile=$null,

    [String]$CertPasswordUser=$true,

    [Switch]$CheckAll=$false,

    [Switch]$CheckTAEFService=$false,

    [Switch]$CheckTestCert=$false,

    [Switch]$CheckTestPfx=$false,

    [Switch]$CheckVisualStudio=$false,

    [Switch]$CheckDependencies=$false,

    [Switch]$CheckDeveloperMode=$false,

    [Switch]$Clean=$false,

    [Switch]$InstallWindowsSDK=$false,

    [Switch]$NoInteractive=$false,

    [Switch]$Offline=$false,

    [Switch]$OnlineVSWhere=$false,

    [Switch]$RemoveAll=$false,

    [Switch]$RemoveTestCert=$false,

    [Switch]$RemoveTestPfx=$false,

    [String]$SaveSettingsFile=$null,

    [String]$SaveUserSettingsFile=$null,

    [Switch]$Settings=$true,

    [String]$SettingsFile='DevCheck-Settings.ps1',

    [Switch]$ShowSystemInfo=$false,

    [Switch]$StartTAEFService=$false,

    [Switch]$StopTAEFService=$false,

    [Switch]$SyncDependencies=$false,

    [Switch]$UserSettings=$true,

    [String]$UserSettingsFile='DevCheck-UserSettings.ps1',

    [Switch]$Verbose=$false
)

Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"

$global:issues = 0

$global:isadmin = $null

$global:vswhere = ''
$global:vswhere_url = ''

$global:dependency_paths = ('dev', 'test', 'installer', 'tools')

function Get-SettingsFile
{
    if ([string]::IsNullOrEmpty($SettingsFile))
    {
        return $null
    }

    $file = [IO.Path]::GetFullPath($SettingsFile)
    if (-not(Test-Path -Path $file -PathType Leaf))
    {
        $root = Get-ProjectRoot
        $userdir = Join-Path $root '.user'
        $file = Join-Path $userdir $SettingsFile
        if (-not(Test-Path -Path $file -PathType Leaf))
        {
            return $null
        }
    }
    return $file
}

function Get-Settings
{
    if ($Settings -eq $false)
    {
        return $null
    }

    $settings_file = Get-SettingsFile $true
    if ([string]::IsNullOrEmpty($settings_file))
    {
        return $null
    }

    $file = [IO.Path]::GetFullPath($settings_file)
    if (-not(Test-Path -Path $file -PathType Leaf))
    {
        $root = Get-ProjectRoot
        $userdir = Join-Path $root '.user'
        $file = Join-Path $userdir $settings_file
        if (-not(Test-Path -Path $file -PathType Leaf))
        {
            return $null
        }
    }
    Write-Host "Loading settings file $($file)..."
    $null = . $file
    Write-Host "Loaded settings file $($file)"
    return $file
}

function Set-Settings
{
    $file = $SaveSettingsFile
    if ([string]::IsNullOrEmpty($file))
    {
        return $null
    }

    if (Test-Path -Path $file)
    {
        Write-Host "ERROR: -SaveSettings file exists; will not overwrite $($file)" -ForegroundColor Red -BackgroundColor Black
        $ERROR_ALREADY_EXISTS = 183
        Exit $ERROR_ALREADY_EXISTS
    }

    $content = @'
# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

# DevCheck Settings

# Do not alter contents except in the Customization block
# Everything else is owned by DevCheck and subject to change without warning

$me = (Get-Item $PSScriptRoot ).FullName
Write-Verbose "$me BEGIN Customization"
#-----------------------------------------------------------------------
# BEGIN Customization
#...insert customization here...
# END   Customization
#-----------------------------------------------------------------------
$me = (Get-Item $PSScriptRoot ).FullName
Write-Verbose "$me END Customization"
'@

    Write-Host "Saving settings file $($file)..."
    Set-Content -Path $file -Value $content -Encoding utf8
    return $file
}

function Get-UserSettingsFile
{
    if ([string]::IsNullOrEmpty($UserSettingsFile))
    {
        return $null
    }

    $file = [IO.Path]::GetFullPath($UserSettingsFile)
    if (-not(Test-Path -Path $file -PathType Leaf))
    {
        $root = Get-ProjectRoot
        $userdir = Join-Path $root '.user'
        $file = Join-Path $userdir $UserSettingsFile
        if (-not(Test-Path -Path $file -PathType Leaf))
        {
            return $null
        }
    }
    return $file
}

function Get-UserSettings
{
    if ($UserSettings -eq $false)
    {
        return $null
    }

    $settings_file = Get-UserSettingsFile $true
    if ([string]::IsNullOrEmpty($settings_file))
    {
        return $null
    }

    $file = [IO.Path]::GetFullPath($settings_file)
    if (-not(Test-Path -Path $file -PathType Leaf))
    {
        $root = Get-ProjectRoot
        $userdir = Join-Path $root '.user'
        $file = Join-Path $userdir $settings_file
        if (-not(Test-Path -Path $file -PathType Leaf))
        {
            return $null
        }
    }
    Write-Host "Loading user settings file $($file)..."
    $null = . $file
    Write-Host "Loaded user settings file $($file)"
    return $file
}

function Set-UserSettings
{
    $file = $SaveUserSettingsFile
    if ([string]::IsNullOrEmpty($file))
    {
        return $null
    }

    if (Test-Path -Path $file)
    {
        Write-Host "ERROR: -SaveUserSettings file exists; will not overwrite $($file)" -ForegroundColor Red -BackgroundColor Black
        $ERROR_ALREADY_EXISTS = 183
        Exit $ERROR_ALREADY_EXISTS
    }

    $content = @'
# DevCheck User Settings

#...insert user customization here...
'@

    Write-Host "Saving user settings file $($file)..."
    Set-Content -Path $file -Value $content -Encoding utf8
    return $file
}

function Write-Verbose
{
    param(
        [Parameter(Mandatory=$true)]
        [string]$Message
    )

    if ($Verbose -eq $true)
    {
        Write-Host $Message
    }
}

function Get-IsAdmin
{
    if ($global:isadmin -eq $null)
    {
        $global:isadmin = [Security.Principal.WindowsIdentity]::GetCurrent().Groups -contains 'S-1-5-32-544'
    }
    return $global:isadmin
}

function Get-ProjectRoot
{
    return (Get-Item $PSScriptRoot ).parent.parent.FullName
}

function Get-TempPath
{
    $root = Get-ProjectRoot
    $temp = Join-Path $root 'temp'
    if (-not(Test-Path -Path $temp -PathType Container))
    {
        Write-Host "Creating $temp..."
        New-Item -Path $temp -ItemType Directory -Force
    }
    return $temp
}

function Get-UserPath
{
    $root = Get-ProjectRoot
    $user = Join-Path $root '.user'
    if (-not(Test-Path -Path $user -PathType Container))
    {
        Write-Host "Creating $user..."
        $null = New-Item -Path $user -ItemType Directory -Force
    }
    return $user
}

function Get-CpuArchitecture
{
    $architecture = $(Get-WmiObject Win32_Processor).Architecture
    if ($architecture -eq 0)
    {
        return "x86"
    }
    elseif ($architecture -eq 9)
    {
        return "x64"
    }
    elseif ($architecture -eq 12)
    {
        return "arm64"
    }
    else
    {
        throw "Unknown CPU Architecture $architecture"
    }
}

function Test-SemVer
{
    param(
        [string]$left,
        [string]$right
    )

    $lefty = $left.Split('.')
    $righty = $right.Split('.')

    $cmp = [int]$lefty[0] - [int]$righty[0]
    if ($cmp -ne 0)
    {
        return $cmp
    }

    $cmp = [int]$lefty[1] - [int]$righty[1]
    if ($cmp -ne 0)
    {
        return $cmp
    }

    $null = $lefty[2] -Match "(\d+)(-[^+]+)?(\+.+)?$"
    $lefty2 = $Matches[1]
    $lefty2prerelease = $Matches[2]
    $null = $righty[2] -Match "(\d+)(-[^+]+)?(\+.+)?$"
    $righty2 = $Matches[1]
    $righty2prerelease = $Matches[2]
    $cmp = [int]$lefty2 - [int]$righty2
    if ($cmp -ne 0)
    {
        return $cmp
    }
    if ($lefty2prerelease -ilt $righty2prerelease)
    {
        return -1
    }
    elseif ($lefty2prerelease -igt $righty2prerelease)
    {
        return 1
    }
    else
    {
        return 0
    }
}

function Get-TAEFPackageVersion
{
    $root = Get-ProjectRoot
    $filename = Join-Path $root 'eng'
    $filename = Join-Path $filename 'Version.Dependencies.xml'
    $xml = [xml](Get-Content $filename -EA:Stop)
    $taef = $xml.SelectSingleNode("/Dependencies/Dependency[@Name='Microsoft.Taef']")
    return $taef.Version
}

function Get-VSWhereOffline
{
    # Absolute Path = "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"

    $programfilesx86 = [Environment]::GetFolderPath([Environment+SpecialFolder]::ProgramFilesX86)
    $path = Join-Path $programfilesx86 "Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not(Test-Path -Path $path -PathType Leaf))
    {
        return $null
    }
    return $path
}

function Get-VSWhereOnline
{
    $path = Join-Path $env:TEMP 'vswhere.exe'
    if ($Clean -eq $true -And (Test-Path -Path $path -PathType Leaf))
    {
        Write-Verbose "Found $path. Deleting per -Clean..."
        Remove-Item -Path $path -Force
    }
    if (-not(Test-Path -Path $path -PathType Leaf))
    {
        if ($Offline -eq $true)
        {
            return $null
        }
        $global:vswhere_url = 'https://github.com/microsoft/vswhere/releases/download/3.1.7/vswhere.exe'
        Write-Host "Downloading $global:vswhere from $global:vswhere_url..."
        Write-Verbose "Executing: curl.exe --output $path -L -# $global:vswhere_url"
        $null = Start-Process curl.exe -ArgumentList "--output $path -L -# $global:vswhere_url" -Wait -NoNewWindow -PassThru
    }
    if (-not(Test-Path -Path $path -PathType Leaf))
    {
        return $null
    }
    return $path
}

# Home of vswhere.exe: https://github.com/microsoft/vswhere
function Get-VSWhere
{
    Write-Verbose "Detecting vswhere.exe..."
    if ($OnlineVSWhere -eq $false)
    {
        $global:vswhere = Get-VSWhereOffline
    }
    if ([string]::IsNullOrEmpty($global:vswhere))
    {
        if ($Offline -eq $false)
        {
            $global:vswhere = Get-VSWhereOnline
        }
    }
    if ([string]::IsNullOrEmpty($global:vswhere))
    {
        Write-Host "ERROR: vswhere.exe not found" -ForegroundColor Red -BackgroundColor Black
        $global:issues++
        return $null
    }

    Write-Verbose "Using $global:vswhere"
    return $global:vswhere
}

function Run-Process([string]$exe, [string]$arguments, [Ref][string]$stderr, [int]$throwIfExitCodeIsFailure=$false)
{
    $pi = New-Object System.Diagnostics.ProcessStartInfo
    $pi.FileName = $exe
    if (-not([string]::IsNullOrEmpty($arguments)))
    {
        $pi.Arguments = $arguments
    }
    $pi.CreateNoWindow = $true
    $pi.RedirectStandardError = $true
    $pi.RedirectStandardOutput = $true
    $pi.UseShellExecute = $false
    $p = New-Object System.Diagnostics.Process
    $p.StartInfo = $pi
    $ok = $p.Start()
    $p.WaitForExit()
    $stdout = $p.StandardOutput.ReadToEnd()
    $stderr = $p.StandardError.ReadToEnd()
    if ($throwIfExitCodeIsFailure -eq $true)
    {
        if ($p.ExitCode -ne 0)
        {
            throw $p.ExitCode
        }
    }
    return $stdout
}

$global:vspath = ''
function Get-VisualStudio2022InstallPath
{
    Write-Verbose "Detecting VisualStudio 2022..."
    $vswhere_exe = Get-VSWhere
    if ([string]::IsNullOrEmpty($vswhere_exe))
    {
        return $null
    }
    $args = " -latest -products * -version [17.0,18.0) -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath"
    Write-Verbose "Executing $vswhere_exe $args"
    $path = Run-Process $vswhere_exe $args
    $path = $path -replace [environment]::NewLine, ''
    Write-Verbose "Visual Studio 2022 detected at $path"
    $global:vspath = $path
}

function Test-VisualStudioComponent
{
    param(
        [String]$component,
        [String]$versionRange
    )

    $vswhere_exe = Get-VSWhere
    if ([string]::IsNullOrEmpty($global:vswhere))
    {
        return 0
    }
    $args = " -latest -products * -version $versionRange -requires $component -property productDisplayVersion"
    Write-Verbose "Executing $vswhere_exe $args"
    try
    {
        $value = Run-Process $vswhere_exe $args -throwIfExitCodeIsFailure $true
        $path = $path -replace [environment]::NewLine, ''
        Write-Verbose "Visual Studio component $($component) = $($value)"
        return 0
    }
    catch
    {
        $e = $_
        Write-Host "...ERROR $($e): $($component) not found or valid" -ForegroundColor Red -BackgroundColor Black
        return 1
    }
}

function Test-VisualStudioComponents
{
    Write-Verbose "Detecting VisualStudio components..."
    $root = Get-ProjectRoot
    $path = Join-Path $root 'docs\Coding-Guidelines'
    $filename = Join-Path $path 'VisualStudio2022.vsconfig'

    $versionRange = "[17.0,18.0)"

    $json = Get-Content $filename -EA:Stop -Raw | ConvertFrom-Json
    Write-Host "...Scanning $($json.components.Length) components in $($filename)" -NoNewline
    $errors = 0
    $components = $json.components
    ForEach ($component in $components)
    {
        Write-Host "." -NoNewline
        $errors += (Test-VisualStudioComponent $component $versionRange)
    }
    if ($errors -gt 0)
    {
        Write-Host ""
        return $false
    }
    Write-Host "OK"
    return $true
}

function Test-VisualStudio2022Install
{
    $ok = $true
    $path = Get-VisualStudio2022InstallPath
    if ([string]::IsNullOrEmpty($path))
    {
        $global:issues++
        $ok = $false
    }
    Write-Host "VisualStudio 2022...$path"
    return $ok
}

function Install-WindowsSDK
{
    param(
        [String]$version,
        [uri]$url
    )

    $path = Join-Path $env:TEMP "winsdksetup-$($version).exe"
    if ($Clean -eq $true -And (Test-Path -Path $path -PathType Leaf))
    {
        Write-Verbose "Found $path. Deleting per -Clean..."
        Remove-Item -Path $path -Force
    }

    $log = Join-Path $env:TEMP "winsdksetup-$($version).log"
    if ($Clean -eq $true -And (Test-Path -Path $log -PathType Leaf))
    {
        Write-Verbose "Found $log. Deleting per -Clean..."
        Remove-Item -Path $log -Force
    }

    if (-not(Test-Path -Path $path -PathType Leaf))
    {
        Write-Host "Downloading Windows SDK $version from $url..."
        Write-Verbose "Executing: curl.exe --output $path -L -# $url"
        $null = Start-Process curl.exe -ArgumentList "--output $path -L -# $url" -Wait -NoNewWindow -PassThru
    }
    $p = Start-Process $path -ArgumentList "/features + /q /log $log" -Wait -NoNewWindow -PassThru
    if ($p.ExitCode -ne 0)
    {
        Write-Host "...ERROR: Windows SDK $($version) install failed. See $log" -ForegroundColor Red -BackgroundColor Black
        $global:issues++
        return $false
    }
    Write-Host "Install Windows SDK $($version)...OK"
    return $true
}

function Test-WindowsSDKInstall
{
    param(
        [String]$version,
        [uri]$url
    )

    $regkey = "HKLM:\SOFTWARE\Microsoft\Windows Kits\Installed Roots\$version"
    $found = Test-Path $regkey -PathType Container
    if ($found)
    {
        Write-Host "Windows SDK $($version) = OK"
    }
    elseif ($InstallWindowsSDK -eq $true)
    {
        Write-Warning "WARNING: Windows SDK $($version) not found. Installing..."
        $null = Install-WindowsSDK $version $url
    }
    else
    {
        Write-Host "...ERROR: Windows SDK $($version) not found or valid. See [Getting Started doc's Tooling Prerequisites](https://github.com/microsoft/WindowsAppSDK/blob/main/docs/Coding-Guidelines/GettingStarted.md#tooling-prerequisites)" -ForegroundColor Red -BackgroundColor Black
        $global:issues++
    }
    return $found
}

function Test-DevTestPfx
{
    if ($Clean -eq $true)
    {
        return $false
    }

    $user = Get-UserPath
    $pfx_thumbprint = Join-Path $user 'winappsdk.certificate.test.thumbprint'
    if (-not(Test-Path -Path $pfx_thumbprint -PathType Leaf))
    {
        Write-Host "Test certificate thumbprint $pfx_thumbprint...Not Found"
        $global:issues++
        return $false
    }

    $thumbprint = Get-Content -Path $pfx_thumbprint -Encoding utf8
    $cert_path = "cert:\LocalMachine\TrustedPeople\$thumbprint"
    if (-not(Test-Path -Path $cert_path))
    {
        Write-Host "Test certificate for $pfx_thumbprint...Not Found"
        $global:issues++
        return $false
    }

    $cert = Get-ChildItem -Path $cert_path
    $expiration = $cert.NotAfter
    $now = Get-Date
    if ($expiration -lt $now)
    {
        Write-Host "Test certificate for $pfx_thumbprint...Expired ($expiration)"
        $global:issues++
        return $false
    }
    elseif ($expiration -lt ($now + (New-TimeSpan -Days 14)))
    {
        Write-Host "Test certificate for $pfx_thumbprint...Expires soon ($expiration)"
        $global:issues++
        return $true
    }

    Write-Host "Test certificate for $pfx_thumbprint...OK"
    return $true
}

function Repair-DevTestPfx
{
    $isadmin = Get-IsAdmin
    if ($isadmin -eq $false)
    {
        Write-Host "Test certificate .pfx...Access Denied. Run from an admin prompt"
        $global:issues++
        return $false
    }

    $user = Get-UserPath
    $pwd_file = Join-Path $user 'winappsdk.certificate.test.pwd'

    # -CertPassword <password> is a required parameter for this work
    $password = ''
    if (-not [string]::IsNullOrEmpty($CertPassword))
    {
        $password = $CertPassword
    }
    elseif (-not [string]::IsNullOrEmpty($CertPasswordFile))
    {
        if (-not(Test-Path -Path $CertPasswordFile -PathType Leaf))
        {
            Write-Host "Test certificate file $CertPasswordFile...Not Found"
            $global:issues++
            return $false
        }
        $password = Get-Content -Path $CertPasswordFile -Encoding utf8
    }
    elseif (($CertPasswordUser -eq $true) -and (Test-Path -Path $pwd_file -PathType Leaf))
    {
        $password = Get-Content -Path $pwd_file -Encoding utf8
    }
    elseif ([string]::IsNullOrEmpty($password) -And ($NoInteractive -eq $false))
    {
        $password = Read-Host -Prompt 'Creating test certificate. Please enter a password' -AsSecureString
    }
    else
    {
        $charSet = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@'
        $passwordLength = 20
        $password = New-Object -TypeName System.Security.SecureString
        # Generate random characters and append to SecureString
        for ($i = 0; $i -lt $passwordLength; $i++)
        {
            $randomChar = $charSet[(Get-Random -Maximum $charSet.Length)]
            $password.AppendChar($randomChar)
        }
    }

    # Convert back to plaintext. This is not secure but this cert is only use for development purposes.
    # Do not use for production purposes.
    $BSTR = [System.Runtime.InteropServices.Marshal]::SecureStringToBSTR($password)
    $passwordPlainText = [System.Runtime.InteropServices.Marshal]::PtrToStringAuto($BSTR)
    [Runtime.InteropServices.Marshal]::ZeroFreeBSTR($BSTR)
    Set-Content -Path $pwd_file -Value $passwordPlainText -Force

    # Prepare to record the pfx for the certificate
    $user = Get-UserPath
    $cert_thumbprint = Join-Path $user 'winappsdk.certificate.test.thumbprint'

    # Create the certificate
    $cert_path = "cert:\CurrentUser\My"
    $now = Get-Date
    $expiration = $now.AddMonths(12)
    $subject = 'CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US'
    $friendly_name = "Microsoft.WindowsAppSDK Test Certificate Create=$now"
    $key_friendly_name = "Microsoft.WindowsAppSDK Test PrivateKey Create=$now"
    $key_description = "Microsoft.WindowsAppSDK Test PrivateKey Create=$now"
    $eku_oid = '2.5.29.37'
    $eku_value = '1.3.6.1.5.5.7.3.3,1.3.6.1.4.1.311.10.3.13'
    $eku = "$eku_oid={text}$eku_value"
    $cert = New-SelfSignedCertificate -CertStoreLocation $cert_path -NotAfter $expiration -Subject $subject -FriendlyName $friendly_name -KeyFriendlyName $key_friendly_name -KeyDescription $key_description -TextExtension $eku

    # Save the thumbprint
    $thumbprint = $cert.Thumbprint
    Set-Content -Path $cert_thumbprint -Value $thumbprint -Force

    # Export the certificate
    $cer = Join-Path $user 'winappsdk.certificate.test.cer'
    $export_cer = Export-Certificate -Cert $cert -FilePath $cer -Force
    $cert_personal = "cert:\CurrentUser\My\$thumbprint"
    $pfx = Join-Path $user 'winappsdk.certificate.test.pfx'
    $export_pfx = Export-PfxCertificate -Cert $cert_personal -FilePath $pfx -Password $password

    # Delete the personal certiicate
    Remove-Item -Path $cert_personal -DeleteKey

    $ok = $true
    foreach ($f in $cer,$pfx,$pwd_file,$cert_thumbprint)
    {
        if (Test-Path -Path $f -PathType Leaf)
        {
            Write-Host "Create $f...OK"
        }
        else
        {
            Write-Host "Create $f...Error"
            $global:issues++
            $ok = $false
        }
    }

    return $ok
}

function Remove-DevTestPfx
{
    $user = Get-UserPath
    $cer = Join-Path $user 'winappsdk.certificate.test.cer'
    $pfx = Join-Path $user 'winappsdk.certificate.test.pfx'
    $pwd_file = Join-Path $user 'winappsdk.certificate.test.pwd'
    $pfx_thumbprint = Join-Path $user 'winappsdk.certificate.test.thumbprint'

    foreach ($f in $cer,$pfx,$pwd_file,$pfx_thumbprint)
    {
        if (Test-Path -Path $f -PathType Leaf)
        {
            Remove-Item -Path $f -Force
            Write-Host "Remove test certificate $f...OK"
        }
    }
    return $true
}

function Test-DevTestCert
{
    $user = Get-UserPath
    $pfx_thumbprint = Join-Path $user 'winappsdk.certificate.test.thumbprint'
    $thumbprint = Get-Content -Path $pfx_thumbprint -Encoding utf8

    $cert_path = "cert:\LocalMachine\TrustedPeople\$thumbprint"
    if (-not(Test-Path -Path $cert_path))
    {
        Write-Host "Test certificate $pfx_thumbprint thumbprint $thumbprint...Not Found"
        $global:issues++
        return $false
    }

    $cert = Get-ChildItem -Path $cert_path
    $expiration = $cert.NotAfter
    $now = Get-Date
    if ($expiration -lt $now)
    {
        Write-Host "Test certificate $thumbprint...Expired ($expiration)"
        $global:issues++
        return $false
    }
    elseif ($expiration -lt ($now + (New-TimeSpan -Days 14)))
    {
        Write-Host "Test certificate $thumbprint...Expires soon ($expiration)"
        $global:issues++
        return $false
    }

    Write-Host "Test certificate $thumbprint...OK"
    return $true
}

function Repair-DevTestCert
{
    $isadmin = Get-IsAdmin
    if ($isadmin -eq $false)
    {
        Write-Host "Install test certificate...Access Denied. Run from an admin prompt"
        $global:issues++
        return
    }

    $user = Get-UserPath
    $cer = Join-Path $user 'winappsdk.certificate.test.cer'
    $pfx = Join-Path $user 'winappsdk.certificate.test.pfx'
    $pfx_thumbprint = Join-Path $user 'winappsdk.certificate.test.thumbprint'
    $thumbprint = Get-Content -Path $pfx_thumbprint -Encoding utf8

    $cert_path = "cert:\LocalMachine\TrustedPeople"
    $x509certificates = Import-Certificate -FilePath $cer -CertStoreLocation $cert_path
    Write-Host "Install test certificate $cer...OK"
}

function Remove-DevTestCert
{
    $isadmin = Get-IsAdmin
    if ($isadmin -eq $false)
    {
        Write-Host "Remove test certificate...Access Denied. Run from an admin prompt"
        $global:issues++
        return $false
    }

    $user = Get-UserPath
    $pfx_thumbprint = Join-Path $user 'winappsdk.certificate.test.thumbprint'
    if (-not(Test-Path -Path [System.IO.FileInfo]$pfx_thumbprint -PathType Leaf))
    {
        Write-Host "Remove test certificate $pfx_thumbprint...OK (Not Found)"
        return $true
    }

    $thumbprint = Get-Content -Path $pfx_thumbprint -Encoding utf8
    $cert_path = "cert:\LocalMachine\TrustedPeople\$thumbprint"
    if (-not(Test-Path -Path $cert_path))
    {
        Write-Host "Remove test certificate for $thumbprint...OK (Not Found)"
        return $true
    }
    Remove-Item -Path $cert_path -DeleteKey
    Write-Host "Remove test certificate for $thumbprint...OK"
    return $true
}

function Get-TAEFServiceImagePath
{
    $regkey = 'Registry::HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Te.Service'
    if (-not(Test-Path -Path $regkey))
    {
        return $null
    }

    $path = Get-ItemProperty -Path $regkey | Select-Object 'ImagePath'
    $path.ImagePath
}

function Test-TAEFServiceVersion
{
    $path = Get-TAEFServiceImagePath
    if ([string]::IsNullOrEmpty($path))
    {
        return $null
    }
    if (-not($path -imatch '^.*Microsoft.Taef[\.](.+?)\\'))
    {
        return $null
    }
    $actual_taef_version = $Matches[1]

    $expected_taef_version = Get-TAEFPackageVersion

    $cmp = Test-SemVer $actual_taef_version $expected_taef_version

    if ($cmp -lt 0)
    {
        Write-Warning "WARNING: TAEF service older than the expected version (expected=$expected_taef_version, actual=$actual_taef_version)"
        return 'OlderVersion'
    }
    elseif ($cmp -gt 0)
    {
        Write-Warning "WARNING: TAEF service newer than the expected version (expected=$expected_taef_version, actual=$actual_taef_version)"
        return 'NewerVersion'
    }
    else
    {
        Write-Verbose "Expected TAEF service is registered ($actual_taef_version)"
        return 'OK'
    }
}

function Test-TAEFService
{
    $taef_version_status = Test-TAEFServiceVersion
    if ([string]::IsNullOrEmpty($taef_version_status))
    {
        Write-Host "TAEF service...Not Installed"
        return 'NotFound'
    }

    # Double-check the TAEF service is known as a service as far as Windows is concerned
    $service = Get-Service |Where-Object {$_.Name -eq "TE.Service"}
    if ([string]::IsNullOrEmpty($service))
    {
        Write-Host "TAEF service...Not Installed"
        return 'NotFound'
    }

    if ($service.Status -ne "Running")
    {
        Write-Host "TAEF service...Not running ($service.Status)"
        if ($taef_version_status -eq 'OlderVersion')
        {
            return 'NotRunning-OlderVersion'
        }
        else
        {
            return 'NotRunning'
        }
    }
    else
    {
        Write-Host "TAEF service...Running"
        if ($taef_version_status -eq 'OlderVersion')
        {
            return 'Running-OlderVersion'
        }
        else
        {
            return 'Running'
        }
    }
}

function Install-TAEFService
{
    $isadmin = Get-IsAdmin
    if ($isadmin -eq $false)
    {
        Write-Host "Install TAEF service...Access Denied. Run from an admin prompt"
        $global:issues++
        return
    }

    $root = Get-ProjectRoot
    $cpu = Get-CpuArchitecture
    $taef_version = Get-TAEFPackageVersion
    $taef = "Microsoft.Taef.$($taef_version)"
    $path = "$root\redist\$taef\build\Binaries\$cpu\Wex.Services.exe"
    if (-not(Test-Path -Path $path -PathType Leaf))
    {
        Write-Host "Install TAEF service...Not Found ($path)"
        $global:issues++
        return 'TAEFNotFound'
    }

    $args = '/install:TE.Service'
    $output = Run-Process $path $args
    $service = Get-Service |Where-Object {$_.Name -eq "TE.Service"}
    if ([string]::IsNullOrEmpty($service))
    {
        Write-Host "Install TAEF service...Failed"
        $global:issues++
        return 'InstallError'
    }
    else
    {
        Write-Host "Install TAEF service...OK"
        return 'NotRunning'
    }
}

function Uninstall-TAEFService
{
    $isadmin = Get-IsAdmin
    if ($isadmin -eq $false)
    {
        Write-Host "Uninstall TAEF service...Access Denied. Run from an admin prompt"
        $global:issues++
        return
    }

    $ok = Stop-TAEFService
    if ($ok -ne $true)
    {
        return $ok
    }

    $filename = Get-TAEFServiceImagePath
    $args = '/remove:TE.Service'
    $output = Run-Process $filename $args
    $service = Get-Service |Where-Object {$_.Name -eq "TE.Service"}
    if (-not([string]::IsNullOrEmpty($service)))
    {
        Write-Host "Uninstall TAEF service...Failed"
        $global:issues++
        return 'UninstallError'
    }
    else
    {
        Write-Host "Uninstall TAEF service...OK"
        return 'NotRunning'
    }
}

function Start-TAEFService
{
    $isadmin = Get-IsAdmin
    if ($isadmin -eq $false)
    {
        Write-Host "Install TAEF service...Access Denied. Run from an admin prompt"
        $global:issues++
        return
    }

    $ok = Start-Service 'TE.Service'
    $service = Get-Service |Where-Object {$_.Name -eq "TE.Service"}
    if ($service.Status -ne "Running")
    {
        Write-Host "Start TAEF service...Failed"
        $global:issues++
    }
    else
    {
        Write-Host "Start TAEF service...OK"
        return $true
    }
}

function Stop-TAEFService
{
    $isadmin = Get-IsAdmin
    if ($isadmin -eq $false)
    {
        Write-Host "Stop TAEF service...Access Denied. Run from an admin prompt"
        $global:issues++
        return $false
    }

    $service = Get-Service |Where-Object {$_.Name -eq "TE.Service"}
    if ($service -eq $null)
    {
        return 'NotFound'
    }
    elseif ($service.Status -ne "Stopped")
    {
        $ok = Stop-Service 'TE.Service'
    }
    $service = Get-Service |Where-Object {$_.Name -eq "TE.Service"}
    if ($service -eq $null)
    {
        return 'NotFound'
    }
    elseif ($service.Status -ne "Stopped")
    {
        Write-Host "Stop TAEF service...Failed"
        $global:issues++
        return $false
    }
    else
    {
        Write-Host "Stop TAEF service...OK"
        return $true
    }
}

function Get-DependencyVersions
{
    # Dependencies are defined in Version.Details.xml
    #   - Automagically updated by Maestro
    # Dependencies are defined in Version.Dependencies.xml
    #   - Manually updated by human beings
    # Return the pair of lists
    $dependencies = @{ Automagic=$null; Manual=$null }

    $root = Get-ProjectRoot
    $path = Join-Path $root 'eng'

    # Parse the Version.Details.xml dependencies
    $versionDetailsFileName = Join-Path $path 'Version.Details.xml'
    Write-Host "Reading $($versionDetailsFileName)..."
    $automagicXml = [xml](Get-Content $versionDetailsFileName -EA:Stop)
    $automagicVersions = [ordered]@{}
    ForEach ($dependency in $automagicXml.SelectNodes("/Dependencies/ProductDependencies/Dependency"))
    {
        $name = $dependency.Name
        $version = $dependency.Version
        $automagicVersions.Add($name, $version)
    }
    ForEach ($dependency in $automagicXml.SelectNodes("/Dependencies/ToolsetDependencies/Dependency"))
    {
        $name = $dependency.Name
        $version = $dependency.Version
        $automagicVersions.Add($name, $version)
    }
    $dependencies.Automagic = $automagicVersions

    # Parse The Version.Dependencies.xml dependencies
    $versionDependenciesFileName = Join-Path $path 'Version.Dependencies.xml'
    Write-Host "Reading $($versionDependenciesFileName)..."
    $manualXml = [xml](Get-Content $versionDependenciesFileName -EA:Stop)
    # Parse the Version.Dependencies.xml dependencies
    $manualVersions = [ordered]@{}
    ForEach ($dependency in $manualXml.SelectNodes("/Dependencies/Dependency"))
    {
        $name = $dependency.Name
        $version = $dependency.Version
        $manualVersions.Add($name, $version)
    }
    $dependencies.Manual = $manualVersions

    if ($Verbose -eq $true)
    {
        ForEach ($list in @($dependencies.AutoMagic, $dependencies.Manual))
        {
            ForEach ($name in $list.Keys)
            {
                Write-Verbose "...$($name) = $($list[$name])"
            }
        }
    }

    return $dependencies
}

function Test-PackagesConfig
{
    param(
        [string] $filename,
        $versions
    )

    Write-Verbose "Scanning $filename"
    $xml = [xml](Get-Content $filename -EA:Stop)
    $changed = $false
    ForEach ($package in $xml.packages.package)
    {
        $name = $package.id
        $version = $package.version

        if (-not($versions.Contains($name)))
        {
            Write-Host "ERROR: Unknown package $name in $filename" -ForegroundColor Red -BackgroundColor Black
            $global:issues++
        }
        elseif ($version -ne $versions[$name])
        {
            if ($SyncDependencies -eq $true)
            {
                Write-Host "Updating $name $($version) -> $($versions[$name]) in $filename"
                $package.version = $versions[$name]
                $changed = $true
            }
            else
            {
                Write-Host "ERROR: Unknown version $name=$version in $filename" -ForegroundColor Red -BackgroundColor Black
                $global:issues++
            }
        }

        if (-not($package.HasAttribute("targetFramework")))
        {
            Write-Host "ERROR: targetFramework=""native"" missing in $filename" -ForegroundColor Red -BackgroundColor Black
            $global:issues++
        }
        else
        {
            $targetFramework = $package.targetFramework
            if (($targetFramework -ne "native") -And ($targetFramework -ne "net45"))
            {
                Write-Host "ERROR: targetFramework != ""native"" in $filename" -ForegroundColor Red -BackgroundColor Black
                $global:issues++
            }
        }

    }

    if ($changed -eq $true)
    {
        $xml.Save($filename)

        # Save() doesn't add a newline at the end-of-file
        # No newline at end-of-file makes git, GitHub diff and other tools cranky
        # Make sure they're not cranky
        $content = Get-Content $filename -EA:Stop -Encoding utf8
        Set-Content -Path $filename -Value $content -Force -Encoding utf8
    }
}

function Test-VcxProj
{
    param(
        [string] $filename,
        $versions
    )

    Write-Verbose "Scanning $filename"
    $xml = [xml](Get-Content $filename -EA:Stop)
    $changed = $false
    ForEach ($package in $xml.project.import.project)
    {
        Write-Verbose "TODO scan packages/dependencies in .vcxproj"
    }
}

function Build-Dependencies
{
    param(
        [HashTable]$in
    )

    $automagic = $in["Automagic"]
    $manual = $in["Manual"]

    $output = @"
<?xml version="1.0" encoding="utf-8"?>
<!-- DO NOT EDIT!!! This is a generated file! See Version.Details.xml for more details -->
<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <PropertyGroup>
    <VersionDetailsXmlFilename>`$(MSBuildThisFileDirectory)Version.Details.xml</VersionDetailsXmlFilename>
    <VersionDetailsXml>`$([System.IO.File]::ReadAllText(`"`$(VersionDetailsXmlFilename)`"))</VersionDetailsXml>
    <VersionDependenciesXmlFilename>`$(MSBuildThisFileDirectory)Version.Dependencies.xml</VersionDependenciesXmlFilename>
    <VersionDependenciesXml>`$([System.IO.File]::ReadAllText("`$(VersionDependenciesXmlFilename)"))</VersionDependenciesXml>

"@

    $output = $output + "    <!-- Dependencies: Maestro -->`r`n"
    $lines = @{}
    ForEach ($name in $automagic.Keys)
    {
        # NOTE: Create macros per name.Replace(".","").Append("PackageVersion")=value
        $macro = $name.Replace(".","") + "PackageVersion"
        $value = $automagic[$name]
        $lines.Add("    <$($macro)>`$([System.Text.RegularExpressions.Regex]::Match(`$(VersionDetailsXml), 'Name=`"$($name)`"\s+Version=`"(.*?)`"').Groups[1].Value)</$macro>`r`n", $null)

    }
    $sortedLines = $lines.Keys | Sort-Object
    $output = $output + [String]::Join("", $sortedLines)

    $output = $output + "`r`n"
    $output = $output + "    <!-- Dependencies: Manual -->`r`n"
    $lines = @{}
    ForEach ($name in $manual.Keys)
    {
        # NOTE: Create macros per name.Replace(".","").Append("Version")=value
        $macro = $name.Replace(".","") + "Version"
        $value = $manual[$name]
        $lines.Add("    <$($macro)>`$([System.Text.RegularExpressions.Regex]::Match(`$(VersionDependenciesXml), 'Name=`"$($name)`"\s+Version=`"(.*?)`"').Groups[1].Value)</$macro>`r`n", $null)
    }
    $sortedLines = $lines.Keys | Sort-Object
    $output = $output + [String]::Join("", $sortedLines)

    $output = $output + @"

"@

    $output = $output + @"
  </PropertyGroup>
</Project>
"@

    return $output
}

function CheckAndSync-Dependencies
{
    param(
        [HashTable]$in
    )

    $automagic = $in["Automagic"]
    $manual = $in["Manual"]

    $expected = Build-Dependencies @{ Automagic=$automagic; Manual=$manual }

    $root = Get-ProjectRoot
    $path = Join-Path $root 'eng'
    $filename = Join-Path $path 'Version.Dependencies.props'
    Write-Host "Reading $($filename)..."
    if (-not(Test-Path -Path $filename -PathType Leaf))
    {
        if ($SyncDependencies -eq $false)
        {
            Write-Host "ERROR: $filename not found. Create with 'DevCheck -SyncDependencies'" -ForegroundColor Red -BackgroundColor Black
            $global:issues++
            return
        }
    }
    else
    {
        $content = Get-Content $filename -EA:Stop -Raw
        if ($content.TrimEnd() -eq $expected.TrimEnd()) # Ignore trailing whitespace
        {
            Write-Host "Verify $($filename)...OK"
            return
        }
        elseif ($SyncDependencies -eq $false)
        {
            Write-Host "ERROR: $($filename) out of date. Update with 'DevCheck -SyncDependencies'" -ForegroundColor Red -BackgroundColor Black
            $global:issues++
        }
    }

    if ($SyncDependencies -eq $true)
    {
        Write-Host "Updating $($filename)..."
        Set-Content -Path $filename -Value $expected -Force
    }
}

function Test-Dependencies
{
    # Get version information for dependencies
    $fatal_errors = 0
    $dependencies = Get-DependencyVersions
    if ([string]::IsNullOrEmpty($dependencies))
    {
        $global:issues++
        $fatal_errors++
    }
    $automagic = $dependencies.Automagic
    $manual = $dependencies.Manual
    if ([string]::IsNullOrEmpty($automagic))
    {
        $global:issues++
        $fatal_errors++
    }

    # Merge the lists
    $versions = [ordered]@{}
    ForEach ($name in $automagic.Keys)
    {
        if ($versions.Contains($name))
        {
            Write-Host "ERROR: Dependency defined multiple times ($name)" -ForegroundColor Red -BackgroundColor Black
            $global:issues++
            $fatal_errors++
        }
        else
        {
            $value = $automagic[$name]
            $versions.Add($name, $value)
        }
    }
    ForEach ($name in $manual.Keys)
    {
        if ($versions.Contains($name))
        {
            Write-Host "ERROR: Dependency defined multiple times ($name)" -ForegroundColor Red -BackgroundColor Black
            $global:issues++
            $fatal_errors++
        }
        else
        {
            $value = $manual[$name]
            $versions.Add($name, $value)
        }
    }
    Write-Host "$($versions.Count) dependencies detected"

    # Fatal errors detected?
    if ($fatal_errors++ -gt 0)
    {
        return
    }

    # Check Version.Dependencies.props
    $null = CheckAndSync-Dependencies  @{ Automagic=$automagic; Manual=$manual }

    # Scan for references - packages.config
    $root = Get-ProjectRoot
    $files = 0
    ForEach ($subtree in $global:dependency_paths)
    {
        $path = Join-Path $root $subtree
        Write-Host "Scanning packages.config..."
        ForEach ($file in (Get-ChildItem -Path $path -Recurse -File 'packages.config'))
        {
            $null = Test-PackagesConfig $file.FullName $versions
            $files++
        }
    }
    Write-Host "Scanned $($files) packages.config"

    $files = 0
    ForEach ($subtree in $global:dependency_paths)
    {
        $path = Join-Path $root $subtree
        Write-Host "Scanning *.vcxproj..."
        ForEach ($file in (Get-ChildItem -Path $path -Recurse -File '*.vcxproj'))
        {
            $null = Test-VcxProj $file.FullName $versions
            $files++
        }
    }
    Write-Host "Scanned $($files) *.vcxproj"
}

function Get-DeveloperMode
{
    $regkey = 'HKLM:\SOFTWARE\Microsoft\Windows\CurrentVersion\AppModelUnlock'
    if (Test-Path -Path $regkey -PathType Container)
    {
        $value = $(Get-Item -Path $regkey).GetValue('AllowDevelopmentWithoutDevLicense')
        return $value -eq 1
    }

    return $false
}

function Test-DeveloperMode
{
    $developermode = Get-DeveloperMode
    if ($developermode -eq $true)
    {
        Write-Host "Developer mode...Enabled"
    }
    else
    {
        Write-Host "ERROR: Developer mode is not enabled. Enable it via Settings" -ForegroundColor Red -BackgroundColor Black
        $global:issues++
    }
}

function Get-SystemInfo
{
    $regkey = 'HKLM:\SOFTWARE\Microsoft\Windows NT\CurrentVersion'
    $productname = $(Get-Item -Path $regkey).GetValue('ProductName')
    $displayversion = $(Get-Item -Path $regkey).GetValue('DisplayVersion')
    $currentmajor = $(Get-Item -Path $regkey).GetValue('CurrentMajorVersionNumber')
    $currentminor = $(Get-Item -Path $regkey).GetValue('CurrentMinorVersionNumber')
    $currentbuild = $(Get-Item -Path $regkey).GetValue('CurrentBuild')
    Write-Host "Product         : $($productname) $($displayversion) $($currentmajor).$($currentminor).$($currentbuild)"

    $installationtype = $(Get-Item -Path $regkey).GetValue('InstallationType')
    Write-Host "InstallationType: $($installationtype)"

    $editionid = $(Get-Item -Path $regkey).GetValue('EditionId')
    $compositioneditionid = $(Get-Item -Path $regkey).GetValue('CompositionEditionID')
    if ($editionid -eq $compositioneditionid)
    {
        Write-Host "Edition         : $($editionid)"
    }
    else
    {
        Write-Host "Edition         : $($editionid) [$($compositioneditionid)]"
    }

    $buildlabex = $(Get-Item -Path $regkey).GetValue('BuildLabEx')
    Write-Host "Build           : $($buildlabex)"

    $lcuver = $(Get-Item -Path $regkey).GetValue('LCUVer')
    Write-Host "LCU Version     : $($lcuver)"

    Write-Host "Powershell      : $($PSVersionTable.PSEdition) $($PSVersionTable.PSVersion)"
}

$null = Set-Settings
$null = Set-UserSettings
$null = Get-Settings
$null = Get-UserSettings

$remove_any = ($RemoveAll -eq $true) -or ($RemoveTestCert -eq $true) -or ($RemoveTestCert -eq $true)
if (($remove_any -eq $false) -And ($CheckTAEFService -eq $false) -And ($StartTAEFService -eq $false) -And
    ($StopTAEFService -eq $false) -And ($CheckTestCert -eq $false) -And ($CheckTestPfx -eq $false) -And
    ($CheckVisualStudio -eq $false) -And ($CheckDependencies -eq $false) -And ($SyncDependencies -eq $false) -And
    ($CheckDeveloperMode -eq $false) -And ($ShowSystemInfo -eq $false))
{
    $CheckAll = $true
}
if ($SyncDependencies -eq $true)
{
    $CheckDependencies = $true
}

Write-Output "Checking developer environment..."

$cpu = Get-CpuArchitecture
Write-Verbose("Processor...$cpu")

$project_root = Get-ProjectRoot
Write-Output "Windows App SDK location...$project_root"

if (($CheckAll -ne $false) -Or ($ShowSystemInfo -ne $false))
{
    Get-SystemInfo
}

if (($CheckAll -ne $false) -Or ($CheckVisualStudio -ne $false))
{
    $ok = Test-VisualStudio2022Install
    if ($ok -eq $true)
    {
        $null = Test-VisualStudioComponents
    }
    $null = Test-WindowsSDKInstall '10.0.17763.0' [uri]'https://go.microsoft.com/fwlink/p/?LinkID=2033908'
    #TODO Uncomment to require new SDK: $null = Test-WindowsSDKInstall '10.0.26100.0' [uri]'https://go.microsoft.com/fwlink/?linkid=2272610'
}

if (($CheckAll -ne $false) -Or ($CheckTestPfx -ne $false))
{
    $test = Test-DevTestPfx
    if ($test -ne $true)
    {
        $test = Repair-DevTestPfx
        if ($test -ne $true)
        {
            Write-Output "Fatal error. Aborting..."
            Exit 1
        }
    }
}

if (($CheckAll -ne $false) -Or ($CheckTestCert -ne $false))
{
    $test = Test-DevTestCert
    if ($test -ne $true)
    {
        $null = Repair-DevTestCert
    }
}

if (($CheckAll -ne $false) -Or ($CheckTAEFService -ne $false))
{
    $test = Test-TAEFService
    if ($test -eq 'NotFound')
    {
        $test = Install-TAEFService
        $test = Start-TAEFService
    }
    elseif ($test -eq 'NotRunning-OlderVersion')
    {
        $test = Uninstall-TAEFService
        $test = Install-TAEFService
        $test = Start-TAEFService
    }
    elseif ($test -eq 'NotRunning')
    {
        $test = Start-TAEFService
    }
    elseif ($test -eq 'Running-OlderVersion')
    {
        $test = Stop-TAEFService
        if ($test -ne $false)
        {
            if ($test -eq $true)
            {
                $test = Uninstall-TAEFService
            }
            $test = Install-TAEFService
            $test = Start-TAEFService
        }
    }
}

if (($CheckAll -ne $false) -Or ($CheckDependencies -ne $false))
{
    $null = Test-Dependencies
}

if (($CheckAll -ne $false) -Or ($CheckDeveloperMode -ne $false))
{
    $null = Test-DeveloperMode
}

if ($StartTAEFService -eq $true)
{
    $null = Start-TAEFService
}

if ($StopTAEFService -eq $true)
{
    $null = Stop-TAEFService
}

if (($RemoveAll -ne $false) -Or ($RemoveTestCert -ne $false))
{
    $null = Remove-DevTestCert
}

if (($RemoveAll -ne $false) -Or ($RemoveTestPfx -ne $false))
{
    $null = Remove-DevTestPfx
}

if ($global:issues -eq 0)
{
    Write-Output "Coding time!"
}
else
{
    $n = $global:issues
    Write-Output "$n issue(s) detected"
}
