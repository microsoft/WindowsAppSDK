# Make a valid AppxManifest.xml from a templated file and variable substititon

<#
.SYNOPSIS
    Verify the environment for Windows App SDK development

.DESCRIPTION
    Review the current environment and fix or warn if anything is amiss. This includes...
    * TAEF service is installed and running
    * Test certificate to sign test MSIX packages is installed
    * Visual Studio 2022 is installed and properly configured

.PARAMETER CertPassword
    Password for new certificates

.PARAMETER Clean
    Run as if it's the first time (ignore any previous cached artifacts from previous runs).

.PARAMETER CheckAll
    Check all. If not specified this is set to true if all other -Check... options are false

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

.PARAMETER Offline
    Do not access the network

.PARAMETER RemoveAll
    Remove all.

.PARAMETER RemoveTestCert
    Remove the Test certificate (i.e. undoc CheckTestCert)

.PARAMETER RemoveTestPfx
    Remove the MSIX Test signing certificate (i.e. undoc CheckTestPfx)

.PARAMETER Verbose
    Display detailed information

.EXAMPLE
    DevCheck -Verbose
#>

Param(
    [String]$CertPassword=$null,

    [String]$CertPasswordFile=$null,

    [String]$CertPasswordUser=$true,

    [Switch]$CheckAll=$false,

    [Switch]$CheckTAEFService=$false,

    [Switch]$CheckTestCert=$false,

    [Switch]$CheckTestPfx=$false,

    [Switch]$CheckVisualStudio=$false,

    [Switch]$Clean=$false,

    [Switch]$NoInteractive=$false,

    [Switch]$Offline=$false,

    [Switch]$RemoveAll=$false,

    [Switch]$RemoveTestCert=$false,

    [Switch]$RemoveTestPfx=$false,

    [Switch]$Verbose=$false
)

$global:issues = 0

$remove_any = ($RemoveAll -eq $true) -or ($RemoveTestCert -eq $true) -or ($RemoveTestCert -eq $true)
if (($remove_any -eq $false) -And ($CheckTAEFService -eq $false) -And ($CheckTestCert -eq $false) -And ($CheckTestPfx -eq $false) -And ($CheckVisualStudio -eq $false))
{
    $CheckAll = $true
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
    return [Security.Principal.WindowsIdentity]::GetCurrent().Groups -contains 'S-1-5-32-544'
}

function Get-ProjectRoot
{
    return Split-Path -Path $PSScriptRoot
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

# Home of vswhere.exe: https://github.com/microsoft/vswhere
$vswhere = ''
$vswhere_url = ''
function Get-VSWhere
{
    if ([string]::IsNullOrEmpty($global:vswhere))
    {
        Write-Verbose "Detecting vswhere.exe..."
        $vswhere = Join-Path $env:TEMP 'vswhere.exe'
        if ($Clean -eq $true -And (Test-Path -Path $vswhere -PathType Leaf))
        {
            Write-Verbose "Found $vswhere. Deleting per -Clean..."
            Remove-Item -Path $vswhere -Force
        }
        if (-not(Test-Path -Path $vswhere -PathType Leaf))
        {
            if ($Offline -eq $true)
            {
                Write-Host "vswhere.exe not detected"
                $global:issues += 1
                return
            }
            $vswhere_url = 'https://github.com/microsoft/vswhere/releases/download/2.8.4/vswhere.exe'
            Write-Host "Downloading $vswhere from $vswhere_url..."
            Write-Verbose "Executing: curl.exe --output $vswhere -L -# $vswhere_url"
            $p = Start-Process curl.exe -ArgumentList "--output $vswhere -L -# $vswhere_url" -Wait -NoNewWindow -PassThru
        }
        Write-Verbose "Using $vswhere"
        $global:vswhere = $vswhere
    }
    return $global:vswhere
}

function Run-Process([string]$exe, [string]$arguments, [Ref][string]$stderr)
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
    return $stdout
}

$vspath = ''
function Get-VisualStudio2022InstallPath
{
    if ([string]::IsNullOrEmpty($global:vspath))
    {
        Write-Verbose "Detecting VisualStudio 2022..."
        $vswhere = Get-VSWhere
        $args = " -latest -products * -version [17.0,18.0) -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath"
        Write-Verbose "Executing $vswhere $args"
        $path = Run-Process $vswhere $args
        $path = $path -replace [environment]::NewLine, ''
        Write-Verbose "Visual Studio 2022 detected at $path"
        $global:vspath = $path
    }
    return $global:vspath
}

function Test-VisualStudio2022Install
{
    $path = Get-VisualStudio2022InstallPath
    if ([string]::IsNullOrEmpty($path))
    {
        $global:issues++
    }
    Write-Host "VisualStudio 2022...$path"
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
        $global:issues += 1
        return $false
    }

    $thumbprint = Get-Content -Path $pfx_thumbprint -Encoding utf8
    $cert_path = "cert:\LocalMachine\TrustedPeople\$thumbprint"
    if (-not(Test-Path -Path $cert_path))
    {
        Write-Host "Test certificate for $pfx_thumbprint...Not Found"
        $global:issues += 1
        return $false
    }

    $cert = Get-ChildItem $cert_path
    $expiration = $cert.NotAfter
    $now = Get-Date
    if ($expiration -lt $now)
    {
        Write-Host "Test certificate for $pfx_thumbprint...Expired ($expiration)"
        $global:issues += 1
        return $false
    }
    elseif ($expiration -lt ($now + (New-TimeSpan -Days 14)))
    {
        Write-Host "Test certificate for $pfx_thumbprint...Expires soon ($expiration)"
        $global:issues += 1
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
        $global:issues += 1
        return $false
    }

    $user = Get-UserPath
    $pwd_file = Join-Path $user 'winappsdk.certificate.test.pwd'

    # -CertPassword <password> is a required parameter for this work
    $password = ''
    if (-not [string]::IsNullOrEmpty($CertPassword))
    {
        $password_plaintext = $CertPassword
    }
    elseif (-not [string]::IsNullOrEmpty($CertPasswordFile))
    {
        if (-not(Test-Path -Path $CertPasswordFile -PathType Leaf))
        {
            Write-Host "Test certificate file $CertPasswordFile...Not Found"
            $global:issues += 1
            return $false
        }
        $password = Get-Content -Path $CertPasswordFile -Encoding utf8
    }
    elseif (($CertPasswordUser -eq $true) -and (Test-Path -Path $pwd_file -PathType Leaf))
    {
        $password = Get-Content -Path $pwd_file -Encoding utf8
    }
    elseif ($NoInteractive -eq $false)
    {
        $password_plaintext = Read-Host -Prompt 'Creating test certificate. Please enter a password'
    }
    if ([string]::IsNullOrEmpty($password_plaintext))
    {
        Write-Host "Test certificate .pfx...password parameter (-CertPassword | -CertPasswordFile | -CertPasswordUser) or prompting required"
        $global:issues += 1
        return $false
    }
    $password = ConvertTo-SecureString -String $password_plaintext -Force -AsPlainText
    Set-Content -Path $pwd_file -Value $password_plaintext -Force

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
            $global:issues += 1
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
        $global:issues += 1
        return $false
    }

    $cert = Get-ChildItem -Path $cert_path
    $expiration = $cert.NotAfter
    $now = Get-Date
    if ($expiration -lt $now)
    {
        Write-Host "Test certificate $thumbprint...Expired ($expiration)"
        $global:issues += 1
        return $false
    }
    elseif ($expiration -lt ($now + (New-TimeSpan -Days 14)))
    {
        Write-Host "Test certificate $thumbprint...Expires soon ($expiration)"
        $global:issues += 1
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
        $global:issues += 1
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
        $global:issues += 1
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

function Test-TAEFService
{
    $service = Get-Service |Where-Object {$_.Name -eq "TE.Service"}
    if ([string]::IsNullOrEmpty($service))
    {
        Write-Host "TAEF service...Not Installed"
        return 'NotFound'
    }
    elseif ($service.Status -ne "Running")
    {
        Write-Host "TAEF service...Not running ($service.Status)"
        return 'NotRunning'
    }
    else
    {
        Write-Host "TAEF service...Running"
        return 'Running'
    }
}

function Repair-TAEFService
{
    $isadmin = Get-IsAdmin
    if ($isadmin -eq $false)
    {
        Write-Host "Install TAEF service...Access Denied. Run from an admin prompt"
        $global:issues += 1
        return
    }

    $root = Get-ProjectRoot
    $cpu = Get-CpuArchitecture
    $taef = 'Microsoft.Taef.10.58.210222006-develop'
    $path = "$root\packages\$taef\build\Binaries\$cpu\Wex.Services.exe"
    if (-not(Test-Path -Path $path -PathType Leaf))
    {
        Write-Host "Install TAEF service...Not Found ($path)"
        $global:issues += 1
        return 'TAEFNotFound'
    }

    $args = '/install:TE.Service'
    $output = Run-Process $path $args
    $service = Get-Service |Where-Object {$_.Name -eq "TE.Service"}
    if ([string]::IsNullOrEmpty($service))
    {
        Write-Host "Install TAEF service...Failed"
        $global:issues += 1
        return 'InstallError'
    }
    else
    {
        Write-Host "Install TAEF service...OK"
        return 'NotRunning'
    }
}

function Start-TAEFService
{
    $isadmin = Get-IsAdmin
    if ($isadmin -eq $false)
    {
        Write-Host "Install TAEF service...Access Denied. Run from an admin prompt"
        $global:issues += 1
        return
    }

    $ok = Start-Service 'TE.Service'
    $service = Get-Service |Where-Object {$_.Name -eq "TE.Service"}
    if ($service.Status -ne "Running")
    {
        Write-Host "Start TAEF service...Failed"
        $global:issues += 1
    }
    else
    {
        Write-Host "Start TAEF service...OK"
        return $true
    }
}

Write-Output "Checking developer environment..."

$cpu = Get-CpuArchitecture
Write-Verbose("Processor...$cpu")

$project_root = Get-ProjectRoot
Write-Output "Windows App SDK location...$project_root"

if (($CheckAll -ne $false) -Or ($CheckVisualStudio -ne $false))
{
    Test-VisualStudio2022Install
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
        Repair-DevTestCert
    }
}

if (($CheckAll -ne $false) -Or ($CheckTAEFService -ne $false))
{
    $test = Test-TAEFService
    if ($test -eq 'NotFound')
    {
        $test = Repair-TAEFService
    }
    if ($test -eq 'NotRunning')
    {
        $test = Start-TAEFService
    }
}

if (($RemoveAll -ne $false) -Or ($RemoveTestCert -ne $false))
{
    $test = Remove-DevTestCert
}

if (($RemoveAll -ne $false) -Or ($RemoveTestPfx -ne $false))
{
    $test = Remove-DevTestPfx
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
