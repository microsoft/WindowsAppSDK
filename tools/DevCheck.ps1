# Make a valid AppxManifest.xml from a templated file and variable substititon

<#
.SYNOPSIS
    Verify the environment for Project Reunion development

.DESCRIPTION
    Review the current environment and fix or warn if anything is amiss. This includes...
    * TAEF service is installed and running
    * Test certificate to sign test MSIX packages is installed
    * Visual Studio 2019 is installed and properly configured

.PARAMETER Clean
    Run as if it's the first time (ignore any previous cached artifacts from previous runs).

.PARAMETER CheckAll
    Check all. IF not specified this is set to true if all other -Check... options are false

.PARAMETER CheckTAEFService
    Check the TAEF service

.PARAMETER CheckTestCert
    Check the Test certificate

.PARAMETER CheckTestPfx
    Check the MSIX Test signing certificate (to sign developer test MSIXs)

.PARAMETER CheckVisualStudio
    Check Visual Studio

.PARAMETER Offline
    Do not access the network

.PARAMETER Verbose
    Display detailed information

.EXAMPLE
    DevCheck -Verbose
#>

Param(
    [Switch]$CheckAll=$false,

    [Switch]$CheckTestPfx=$false,

    [Switch]$CheckTAEFService=$false,

    [Switch]$CheckTestCert=$false,

    [Switch]$CheckVisualStudio=$false,

    [Switch]$Clean=$false,

    [Switch]$Offline=$false,

    [Switch]$Verbose=$false
)

$global:issues = 0

if (($CheckTestPfx -eq $false) -And ($CheckTAEFService -eq $false) -And ($CheckTestCert -eq $false) -And ($CheckVisualStudio -eq $false))
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
    return Split-Path -Path $PSScriptRoot -Parent
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
function Get-VisualStudio2019InstallPath
{
    if ([string]::IsNullOrEmpty($global:vspath))
    {
        Write-Verbose "Detecting VisualStudio 2019..."
        $vswhere = Get-VSWhere
        $args = " -latest -products * -version [16.0,17.0) -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath"
        Write-Verbose "Executing $vswhere $args"
        $path = Run-Process $vswhere $args
        $path = $path -replace [environment]::NewLine, ''
        Write-Verbose "Visual Studio 2019 detected at $path"
        $global:vspath = $path
    }
    return $global:vspath
}

function Test-VisualStudio2019Install
{
    $path = Get-VisualStudio2019InstallPath
    if ([string]::IsNullOrEmpty($path))
    {
        $global:issues++
    }
    Write-Host "VisualStudio 2019...$path"
}

function Test-DevTestPfx
{
    if ($Clean -eq $true)
    {
        return $false
    }

    $root = Get-ProjectRoot
    $pfx = Join-Path $root 'temp\MSTest.pfx'
    if (Test-Path -Path $pfx -PathType Leaf)
    {
        Write-Host 'Test temp\MSTest.pfx...OK'
        return $true
    }
    else
    {
        Write-Host 'Test temp\MSTest.pfx...Not Found'
        $global:issues += 1
        return $false
    }
}

function Repair-DevTestPfx
{
    $root = Get-ProjectRoot
    $temp = Join-Path $root 'temp'
    if (-not(Test-Path -Path $temp -PathType Container))
    {
        Write-Host 'Creating $temp...'
        New-Item -Path $temp -ItemType Directory -Force
    }

    $spfx = Join-Path $root 'build\MSTest.spfx'
    $pfx = Join-Path $temp 'MSTest.pfx'
    $args = " -decode $spfx $pfx"
    if ($Verbose -eq $true)
    {
        $args = " -v $args"
    }
    $output = Run-Process 'certutil.exe' $args
    if (Test-Path -Path $pfx -PathType Leaf)
    {
        Write-Host 'Create temp\MSTest.pfx...OK'
    }
    else
    {
        Write-Host 'Create temp\MSTest.pfx...Errpr'
        Write-Verbose $output
        $global:issues += 1
    }
}

function Test-DevTestCert
{
    # To manually determine the thumbprint of a *.cer file
    #     certutil.exe -dump filename.cer
    # and look for the sha256 hash e.g.
    #
    #   Cert Hash(sha1): 353556c5bf55045aa2375207d291e6bcd30b524b
    #
    # That 3535... value is the 'Thumbprint' property

    $root = Get-ProjectRoot
    $path = Join-Path $root 'temp\MSTest.pfx'
    $pfx = Get-PfxCertificate -FilePath $path
    $thumbprint = $pfx.Thumbprint

    $cert_path = "cert:\LocalMachine\TrustedPeople\$thumbprint"
    if (-not(Test-Path -Path $cert_path))
    {
        Write-Host 'Test certificate...Not Found'
        $global:issues += 1
    }
    else
    {
        $cert = Get-ChildItem -Path $cert_path
        $expiration = $cert.NotAfter
        $now = Get-Date
        if ($expiration -lt $now)
        {
            Write-Host "Test certificate...Expired ($expiration)"
            $global:issues += 1
        }
        elseif ($expiration -lt ($now + (New-TimeSpan -Days 30)))
        {
            Write-Host "Test certificate...Expires soon ($expiration)"
            $global:issues += 1
        }
        else
        {
            Write-Host "Test certificate...OK"
            return $true
        }
    }
    return $false
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

    $root = Get-ProjectRoot
    $cert = Join-Path $root 'build\MSTest.cer'
    $args = " -addstore TrustedPeople $cert"
    $output = Run-Process 'certutil.exe' $args
    $success = $output | Select-String -Pattern 'CertUtil: -addstore' -SimpleMatch -Quiet
    if ($success -eq $true)
    {
        Write-Host "Install test certificate...OK"
    }
    else
    {
        Write-Host "Install test certificate...Error"
        Write-Verbose $output
        $global:issues += 1
    }
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
Write-Output "ProjectReunion location...$project_root"

if (($CheckAll -ne $false) -Or ($CheckVisualStudio -ne $false))
{
    Test-VisualStudio2019Install
}

if (($CheckAll -ne $false) -Or ($CheckTestPfx -ne $false))
{
    $test = Test-DevTestPfx
    if ($test -ne $true)
    {
        Repair-DevTestPfx
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

if ($global:issues -eq 0)
{
    Write-Output "Coding time!"
}
else
{
    $n = $global:issues
    Write-Output "$n issue(s) detected"
}
