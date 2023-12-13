# This script is invoked by build.cmd to produce a WinUI transport package, and from that,
# a mock Windows App SDK package for tests/samples.

param(
    [Parameter(Mandatory=$true)] [string] $TransportPackageName,
    [Parameter(Mandatory=$true)] [string] $TransportPackagePath,
    [Parameter(Mandatory=$false)] [string] $TransportPackageVersion = "3.0.0-dev",
    [Parameter(Mandatory=$true)] [string] $Output,
    [Parameter(Mandatory=$true)] [string] $RepoRoot,
    [Parameter(Mandatory=$true)] [string] $Platform,
    [Parameter(Mandatory=$true)] [string] $Configuration,
    [Parameter(Mandatory=$false)] [string] $WindowsAppSDKPackageVersionBase = "999.0.0-mock",
    [Parameter(Mandatory=$false)] [string] $PackageCache,
    [switch] $AzurePipelineBuild,
    [switch] $CleanOutput,
    [switch] $Fake
)

pushd (Join-Path $RepoRoot "WindowsAppSDKAggregator")

if($CleanOutput)
{
    . .\buildall.ps1 -Platform $Platform -Configuration $Configuration -clean
}

# Do WinAppSDK one-time setup (mainly, creating and installing test cert)
if(!(Test-Path ".\.user\winappsdk.certificate.test.pfx" ))
{
    .\OneTimeSetupAll.ps1 -CertPassword "password"
    if($LASTEXITCODE -ne 0)
    {
        popd
        Write-Host ".\WindowsAppSDKAggregator\OneTimeSetupAll.ps1 failed with exit code: $LASTEXITCODE" -ForegroundColor RED
        exit $LASTEXITCODE
    }
}

New-Variable -Name ("$TransportPackageName"+"PackageVersion") $TransportPackageVersion
$localPackagesPath = (Join-Path (Join-Path $RepoRoot "WindowsAppSDKAggregator") "localpackages")
$packLocationPath = (Join-Path (Join-Path $RepoRoot "WindowsAppSDKAggregator") "PackLocation")

$WindowsAppSDKPackageVersion = "$WindowsAppSDKPackageVersionBase-$TransportPackageVersion-$Platform-$Configuration"
Copy-Item $TransportPackagePath -destination $localPackagesPath

. .\buildall.ps1 -WindowsAppSDKPackageVersion $WindowsAppSDKPackageVersion -Platform $Platform -Configuration $Configuration -Channel "dev" -TransportPackages "" -BuildOutput $BuildOutput -NugetConfig $NugetConfig -PackageCache $PackageCache -PackageStore $PackageStore -LocalPackages $PackageStore -SkipVerifyProductVersion -AzurePipelineBuild:$AzurePipelineBuild -Fake:$Fake

$files = Get-ChildItem $packLocationPath -File -Filter "*.nukpg"
Write-host $files
Copy-Item -Path "$packLocationPath/*" -Destination $Output -Recurse -Filter "*.nupkg"
popd

if($LASTEXITCODE -ne 0)
{
    Write-Host ".\WindowsAppSDKAggregator\buildAll.ps1 failed with exit code: $LASTEXITCODE" -ForegroundColor RED
    exit $LASTEXITCODE
}
exit 0
