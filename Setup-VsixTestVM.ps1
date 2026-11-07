<#
.SYNOPSIS
Creates a Windows VM, installs the VSIX test prerequisites, and runs the C# VSIX template tests.

.DESCRIPTION
Builds or reuses the Windows App SDK C# LocalDev VSIX, creates a small test
payload, and provisions a Desktop VM with IXPTools. During first-logon
provisioning, the VM installs Visual Studio 2026 Community and WinApp CLI,
installs the LocalDev VSIX, and runs dev\Templates\VSIX\Test-Vsix-Templates.ps1.

The tests use live UI automation. Keep VMConnect open in Basic Session Mode,
leave the VM unlocked, and do not interact with it while the tests run.

.PARAMETER RepoRoot
Windows App SDK repository root. Defaults to the directory containing this script.

.PARAMETER VmName
Name assigned to the new VM.

.PARAMETER VhdSavePath
Directory where IXPTools stores the VM.

.PARAMETER WindowsBranch
Optional Windows branch passed to New-TestMachine.

.PARAMETER Latest
Requests the latest available build for WindowsBranch.

.PARAMETER VsixPath
Path to an existing C# LocalDev VSIX. When specified, the host-side VSIX build is skipped.

.PARAMETER SkipVsixBuild
Reuses the newest C# LocalDev VSIX under the repository's VSIX publish directory.

.PARAMETER WindowsAppSDKVersion
Optional Microsoft.WindowsAppSDK package version passed to Build-VSIX-Local.ps1.

.PARAMETER NupkgSourceDir
Optional directory containing Windows App SDK packages passed to Build-VSIX-Local.ps1.

.PARAMETER TemplateId
One or more template IDs to test. When omitted, all C# VSIX templates are tested.

.PARAMETER VisualStudioComponents
Visual Studio workload or component IDs installed in the VM.

.PARAMETER VisualStudioVersionRange
Visual Studio version range used for installation validation, VSIX installation, and testing.

.PARAMETER SkipVisualStudioInstall
Requires a suitable Visual Studio installation to already exist in the VM.

.PARAMETER SkipWinAppCliInstall
Requires WinApp CLI to already be installed in the VM.

.PARAMETER KeepPayload
Keeps the generated host-side payload after New-TestMachine completes.

.EXAMPLE
.\Setup-VsixTestVM.ps1 -Latest

Builds the LocalDev VSIX, creates a VM from the latest default Windows build,
installs prerequisites, and runs all C# VSIX template tests.

.EXAMPLE
.\Setup-VsixTestVM.ps1 -VsixPath D:\artifacts\WindowsAppSDK.Cs.Extension.Dev17.LocalDev.2026.0929.1200.0.vsix `
    -TemplateId Microsoft.WinUI.Desktop.Cs.MvvmApp

Uses an existing VSIX and runs only the MVVM template test.
#>

[CmdletBinding()]
param(
    [Parameter()]
    [ValidateScript({ Test-Path -LiteralPath $_ -PathType Container })]
    [string]$RepoRoot = $PSScriptRoot,

    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [string]$VmName = 'WinAppSDK-VSIX-Test',

    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [string]$VhdSavePath = 'D:\VMs',

    [Parameter()]
    [string]$WindowsBranch,

    [Parameter()]
    [switch]$Latest,

    [Parameter()]
    [ValidateScript({ Test-Path -LiteralPath $_ -PathType Leaf })]
    [string]$VsixPath,

    [Parameter()]
    [switch]$SkipVsixBuild,

    [Parameter()]
    [string]$WindowsAppSDKVersion,

    [Parameter()]
    [ValidateScript({ Test-Path -LiteralPath $_ -PathType Container })]
    [string]$NupkgSourceDir,

    [Parameter()]
    [string[]]$TemplateId,

    [Parameter()]
    [ValidatePattern('^Microsoft\.VisualStudio\.(Workload|Component|ComponentGroup)\.[A-Za-z0-9.]+$')]
    [string[]]$VisualStudioComponents = @(
        'Microsoft.VisualStudio.Workload.ManagedDesktop',
        'Microsoft.VisualStudio.Workload.Universal'
    ),

    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [string]$VisualStudioVersionRange = '[18.0,19.0)',

    [Parameter()]
    [switch]$SkipVisualStudioInstall,

    [Parameter()]
    [switch]$SkipWinAppCliInstall,

    [Parameter()]
    [switch]$KeepPayload
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

function Assert-LastExitCode {
    param(
        [Parameter(Mandatory)]
        [string]$Operation
    )

    if ($LASTEXITCODE -ne 0) {
        throw "$Operation failed with exit code $LASTEXITCODE."
    }
}

$repoRootPath = (Resolve-Path -LiteralPath $RepoRoot).Path
$vsixDirectory = Join-Path $repoRootPath 'dev\Templates\VSIX'
$testScriptPath = Join-Path $vsixDirectory 'Test-Vsix-Templates.ps1'
$buildDirectory = Join-Path $vsixDirectory 'build-local-VSIX-package'
$buildScriptPath = Join-Path $buildDirectory 'Build-VSIX-Local.ps1'
$installScriptPath = Join-Path $buildDirectory 'Install-LocalDev-VSIX.ps1'
$publishDirectory = Join-Path $buildDirectory 'publish\VSIX'

foreach ($requiredPath in @($testScriptPath, $buildScriptPath, $installScriptPath)) {
    if (-not (Test-Path -LiteralPath $requiredPath -PathType Leaf)) {
        throw "Required repository file not found: $requiredPath"
    }
}

Import-Module IXPTools -DisableNameChecking
if (-not (Get-Command New-TestMachine -ErrorAction SilentlyContinue)) {
    throw 'IXPTools is not installed. Follow the current instructions at https://aka.ms/install-ixptools.'
}

if (Get-VM -Name $VmName -ErrorAction SilentlyContinue) {
    throw "A VM named '$VmName' already exists. Remove it or choose another -VmName."
}

if (-not $VsixPath) {
    if (-not $SkipVsixBuild) {
        $buildParameters = @{
            Configuration = 'Release'
            Deployment = 'LocalDev'
            RepoRoot = $repoRootPath
        }
        if ($WindowsAppSDKVersion) {
            $buildParameters.WindowsAppSDKVersion = $WindowsAppSDKVersion
        }
        if ($NupkgSourceDir) {
            $buildParameters.NupkgSourceDir = (Resolve-Path -LiteralPath $NupkgSourceDir).Path
        }

        Write-Host 'Building the C# LocalDev VSIX payload...'
        & $buildScriptPath @buildParameters
        Assert-LastExitCode 'LocalDev VSIX build'
    }

    $vsix = Get-ChildItem -LiteralPath $publishDirectory `
        -Filter 'WindowsAppSDK.Cs.Extension.Dev17.LocalDev.*.vsix' `
        -File `
        -ErrorAction SilentlyContinue |
        Sort-Object LastWriteTime -Descending |
        Select-Object -First 1
    if (-not $vsix) {
        throw "No C# LocalDev VSIX was found under '$publishDirectory'. Build one or specify -VsixPath."
    }
    $VsixPath = $vsix.FullName
}
else {
    $VsixPath = (Resolve-Path -LiteralPath $VsixPath).Path
}

$payloadRoot = Join-Path ([IO.Path]::GetTempPath()) "WinAppSDK-VsixTestVM-$([guid]::NewGuid().ToString('N'))"
$guestRunnerPath = Join-Path $payloadRoot 'Run-VsixTemplateTests.ps1'
$configurationPath = Join-Path $payloadRoot 'configuration.json'

try {
    New-Item -Path $payloadRoot -ItemType Directory -Force | Out-Null
    Copy-Item -LiteralPath $testScriptPath -Destination $payloadRoot
    Copy-Item -LiteralPath $installScriptPath -Destination $payloadRoot
    Copy-Item -LiteralPath $VsixPath -Destination $payloadRoot

    $configuration = [ordered]@{
        VsixFileName = Split-Path -Leaf $VsixPath
        TemplateId = @($TemplateId)
        VisualStudioComponents = @($VisualStudioComponents)
        VisualStudioVersionRange = $VisualStudioVersionRange
        InstallVisualStudio = -not $SkipVisualStudioInstall.IsPresent
        InstallWinAppCli = -not $SkipWinAppCliInstall.IsPresent
    }
    $configuration | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath $configurationPath -Encoding UTF8

    $guestRunner = @'
<#
.SYNOPSIS
Provisions and runs the Windows App SDK C# VSIX template tests inside a VM.
#>

[CmdletBinding()]
param()

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

function Assert-LastExitCode {
    param(
        [Parameter(Mandatory)]
        [string]$Operation
    )

    if ($LASTEXITCODE -ne 0) {
        throw "$Operation failed with exit code $LASTEXITCODE."
    }
}

function Get-VisualStudioInstance {
    param(
        [Parameter(Mandatory)]
        [string]$VersionRange
    )

    $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path -LiteralPath $vswhere -PathType Leaf)) {
        return $null
    }

    $instanceJson = & $vswhere `
        -products Microsoft.VisualStudio.Product.Community `
        -version $VersionRange `
        -latest `
        -format json
    if ($LASTEXITCODE -ne 0 -or -not $instanceJson) {
        return $null
    }

    return @($instanceJson | ConvertFrom-Json) | Select-Object -First 1
}

function Install-VisualStudio {
    param(
        [Parameter(Mandatory)]
        [string[]]$Components,

        [Parameter(Mandatory)]
        [string]$VersionRange
    )

    $bootstrapperUrl = 'https://aka.ms/vs/stable/vs_community.exe'
    $bootstrapperPath = Join-Path $env:TEMP 'vs_community.exe'
    $installerArguments = @('--wait', '--quiet', '--norestart', '--includeRecommended')
    foreach ($component in $Components) {
        $installerArguments += @('--add', $component)
    }

    try {
        [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
        Invoke-WebRequest -Uri $bootstrapperUrl -OutFile $bootstrapperPath -UseBasicParsing

        $bootstrapper = Get-Item -LiteralPath $bootstrapperPath
        if ($bootstrapper.Length -lt 100KB) {
            throw "The Visual Studio bootstrapper download was unexpectedly small ($($bootstrapper.Length) bytes)."
        }

        $signature = Get-AuthenticodeSignature -LiteralPath $bootstrapperPath
        if ($signature.Status -ne 'Valid' -or
            -not $signature.SignerCertificate -or
            $signature.SignerCertificate.Subject -notmatch 'Microsoft') {
            throw "The Visual Studio bootstrapper signature is not valid: $($signature.Status)."
        }

        $installer = Start-Process -FilePath $bootstrapperPath `
            -ArgumentList $installerArguments `
            -Wait `
            -PassThru
        if ($installer.ExitCode -notin 0, 3010) {
            throw "Visual Studio installation failed with exit code $($installer.ExitCode)."
        }
        if ($installer.ExitCode -eq 3010) {
            Write-Warning 'Visual Studio installation requested a restart. The test will continue, but restart the VM before retrying if setup validation fails.'
        }
    }
    finally {
        Remove-Item -LiteralPath $bootstrapperPath -Force -ErrorAction SilentlyContinue
    }

    $instance = Get-VisualStudioInstance -VersionRange $VersionRange
    if (-not $instance) {
        throw "Visual Studio Community was not detected in version range '$VersionRange' after installation."
    }

    return $instance
}

function Install-WinAppCli {
    $winget = Get-Command winget.exe -ErrorAction SilentlyContinue
    if (-not $winget) {
        throw 'winget.exe was not found. Install App Installer in the VM or provide an image with WinApp CLI already installed.'
    }

    & $winget.Source install `
        --id Microsoft.winappcli `
        --exact `
        --source winget `
        --accept-package-agreements `
        --accept-source-agreements `
        --disable-interactivity
    Assert-LastExitCode 'WinApp CLI installation'

    $env:Path = [Environment]::GetEnvironmentVariable('Path', 'Machine') + ';' +
        [Environment]::GetEnvironmentVariable('Path', 'User')
}

$payloadRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$configuration = Get-Content -LiteralPath (Join-Path $payloadRoot 'configuration.json') -Raw |
    ConvertFrom-Json
$timestamp = Get-Date -Format 'yyyyMMdd-HHmmss'
$logRoot = Join-Path 'C:\VsixTest\Logs' $timestamp
$transcriptPath = Join-Path $logRoot 'orchestrator.log'
$summaryPath = Join-Path $logRoot 'summary.json'
$exitCode = 1

New-Item -Path $logRoot -ItemType Directory -Force | Out-Null
Start-Transcript -Path $transcriptPath -Force
try {
    Write-Host "VSIX test payload: $payloadRoot"
    Write-Host "Test logs: $logRoot"
    Write-Host 'Keep VMConnect open in Basic Session Mode and do not interact with the VM while tests run.'

    $developerModePath = 'HKLM:\SOFTWARE\Microsoft\Windows\CurrentVersion\AppModelUnlock'
    New-Item -Path $developerModePath -Force | Out-Null
    New-ItemProperty `
        -Path $developerModePath `
        -Name AllowDevelopmentWithoutDevLicense `
        -PropertyType DWord `
        -Value 1 `
        -Force |
        Out-Null

    $visualStudioInstance = Get-VisualStudioInstance -VersionRange $configuration.VisualStudioVersionRange
    if ($configuration.InstallVisualStudio) {
        $visualStudioInstance = Install-VisualStudio `
            -Components @($configuration.VisualStudioComponents) `
            -VersionRange $configuration.VisualStudioVersionRange
    }
    elseif (-not $visualStudioInstance) {
        throw "Visual Studio Community was not found in version range '$($configuration.VisualStudioVersionRange)'."
    }

    if ($configuration.InstallWinAppCli) {
        Install-WinAppCli
    }
    if (-not (Get-Command winapp.exe -ErrorAction SilentlyContinue)) {
        throw "WinApp CLI was not found after setup. Verify that 'winapp --version' succeeds for the VM's local administrator."
    }
    & winapp.exe --version
    Assert-LastExitCode 'WinApp CLI validation'

    $installScript = Join-Path $payloadRoot 'Install-LocalDev-VSIX.ps1'
    $vsixPath = Join-Path $payloadRoot $configuration.VsixFileName
    & $installScript `
        -Language CSharp `
        -VsixPath $vsixPath `
        -VsVersionRange $configuration.VisualStudioVersionRange `
        -UninstallFirst
    Assert-LastExitCode 'LocalDev VSIX installation'

    Write-Host 'Tests start in 60 seconds. Bring the VMConnect Basic Session window to the foreground.'
    Start-Sleep -Seconds 60

    $testScript = Join-Path $payloadRoot 'Test-Vsix-Templates.ps1'
    $testParameters = @{
        VisualStudioInstallPath = $visualStudioInstance.installationPath
        VisualStudioVersionRange = $configuration.VisualStudioVersionRange
        VsixDeploymentKind = 'LocalDev'
        ResultsDirectory = $logRoot
    }
    if (@($configuration.TemplateId).Count -gt 0) {
        $testParameters.TemplateId = @($configuration.TemplateId)
    }

    $startedAt = Get-Date
    & $testScript @testParameters 2>&1 |
        Tee-Object -FilePath (Join-Path $logRoot 'vsix-tests.log')
    $testExitCode = $LASTEXITCODE
    $finishedAt = Get-Date

    $summary = [ordered]@{
        Passed = $testExitCode -eq 0
        ExitCode = $testExitCode
        StartedAt = $startedAt
        FinishedAt = $finishedAt
        Duration = $finishedAt - $startedAt
        VisualStudio = $visualStudioInstance.displayName
        VisualStudioVersion = $visualStudioInstance.installationVersion
        VisualStudioPath = $visualStudioInstance.installationPath
        VsixPath = $vsixPath
        TemplateId = @($configuration.TemplateId)
        LogRoot = $logRoot
    }
    $summary | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath $summaryPath -Encoding UTF8
    $summary | Format-List

    if ($testExitCode -ne 0) {
        throw "VSIX template tests failed with exit code $testExitCode. See '$logRoot'."
    }

    Write-Host "All requested VSIX template tests passed. Summary: $summaryPath"
    $exitCode = 0
}
catch {
    Write-Error $_.Exception.Message -ErrorAction Continue
    if (-not (Test-Path -LiteralPath $summaryPath -PathType Leaf)) {
        [ordered]@{
            Passed = $false
            ExitCode = 1
            Error = $_.Exception.Message
            LogRoot = $logRoot
        } |
            ConvertTo-Json -Depth 3 |
            Set-Content -LiteralPath $summaryPath -Encoding UTF8
    }
}
finally {
    Stop-Transcript
}

exit $exitCode
'@

    Set-Content -LiteralPath $guestRunnerPath -Value $guestRunner -Encoding UTF8
    New-Item -Path $VhdSavePath -ItemType Directory -Force | Out-Null

    $thingsToCopy = @{
        $payloadRoot = 'VsixTest\Payload'
    }
    $newVmParameters = @{
        Name = $VmName
        Flavor = 'Desktop'
        SavePath = $VhdSavePath
        Cache = $true
        VmDiskSizeInGb = 160
        VmMemInGb = 12
        VmNumProcessors = 4
        VmResolution = '1920x1080'
        ThingsToCopy = $thingsToCopy
        LocalAdminScripts = @('C:\VsixTest\Payload\Run-VsixTemplateTests.ps1')
        Wait = $true
    }
    if ($WindowsBranch) {
        $newVmParameters.Branch = $WindowsBranch
    }
    if ($Latest) {
        $newVmParameters.Latest = $true
    }

    Write-Warning @"
The VM will install or update Visual Studio, install WinApp CLI and the LocalDev C# VSIX,
and then run UI automation during first-logon provisioning.

Keep VMConnect visible in Basic Session Mode, leave the VM unlocked, and do not interact
with it until the final report appears. Results are written inside the VM under:
C:\VsixTest\Logs
"@

    New-TestMachine @newVmParameters
}
finally {
    if (-not $KeepPayload -and (Test-Path -LiteralPath $payloadRoot -PathType Container)) {
        Remove-Item -LiteralPath $payloadRoot -Recurse -Force
    }
    elseif ($KeepPayload) {
        Write-Host "Generated payload retained at: $payloadRoot"
    }
}

exit 0
