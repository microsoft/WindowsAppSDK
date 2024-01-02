# This script will be used by BuildAll.ps1 to build a mock WindowsAppSDK Package. A path to the TransportPackage used must be provided to
# the TransportPackagePath parameter along with the PackageName and PackageVersion in each respective parameters
param(
    [Parameter(Mandatory=$true)] [string] $TransportPackageName,
    [Parameter(Mandatory=$true)] [string] $TransportPackagePath,
    [Parameter(Mandatory=$false)] [string] $TransportPackageVersion,
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
Copy-Item -Path "$packLocationPath/*" -Destination $Output -Recurse -Filter "*.nupkg"
popd

if($LASTEXITCODE -ne 0)
{
    Write-Host ".\WindowsAppSDKAggregator\buildAll.ps1 failed with exit code: $LASTEXITCODE" -ForegroundColor RED
    exit $LASTEXITCODE
}
exit 0
