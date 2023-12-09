# This script is invoked by build.cmd to produce a WinUI transport package, and from that,
# a mock Windows App SDK package for tests/samples.

param(
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

# if($CleanOutput)
# {
#     . .\buildall.ps1 -clean
# }

$localPackagesPath = (Join-Path (Join-Path $RepoRoot "WindowsAppSDKAggregator") "localpackages")
$packLocationPath = (Join-Path (Join-Path $RepoRoot "WindowsAppSDKAggregator") "PackLocation")

$WindowsAppSDKPackageVersion = "$WindowsAppSDKPackageVersionBase-$TransportPackageVersion-$Platform-$Configuration"
Copy-Item $TransportPackagePath -destination $localPackagesPath

. .\buildall.ps1 -WindowsAppSDKPackageVersion $WindowsAppSDKPackageVersion -Platform $Platform -Configuration $Configuration -Channel "dev" -TransportPackages "" -BuildOutput $BuildOutput -NugetConfig $NugetConfig -PackageCache $PackageCache -PackageStore $PackageStore -LocalPackages $PackageStore -SkipVerifyProductVersion -AzurePipelineBuild:$AzurePipelineBuild -Fake:$Fake

$files = Get-ChildItem $packLocationPath -File -Filter "*.nukpg"
Write-host $files
Copy-Item -Path "$packLocationPath/*" -Destination $Output -Recurse -Filter "*.nupkg"
popd
# # Ensure WinUI transport and mock WinAppSDK packages are build-specific

# $BuildOutput = (Join-Path $RepoRoot "BuildOutput\WindowsAppSDK")
# $NugetConfig = (Join-Path $RepoRoot "nuget.config")

# if (-not $PackageCache)
# {
#     $PackageCache = (Join-Path $RepoRoot "packages")
# }

# $PackageStore = (Join-Path $RepoRoot "PackageStore")
# $PackageRoot = (Join-Path $RepoRoot "BuildOutput\packaging\$Configuration")

# # Check dependencies to see if we need to (re)create the WinUI transport package
# $WinUITransportPackageCached = (Join-Path $PackageCache "Microsoft.ProjectReunion.WinUI.TransportPackage.$WinUIPackageVersion")
# $WinUITransportPackageOutput = (Join-Path $PackageStore "Microsoft.ProjectReunion.WinUI.TransportPackage.$WinUIPackageVersion.nupkg")
# $CreateWinUITransportPackage = $true  # By default, create the WinUI transport package

# if(Test-Path $WinUITransportPackageOutput)
# {
#     # Check for any inputs newer than the WinUI transport package (not perfect - doesn't report missing dependencies)
#     $WinUITransportPackageOutputTime = (Get-ChildItem $WinUITransportPackageOutput).LastWriteTime
#     $NewerDependencies = (Get-ChildItem -Recurse $PackageRoot -File | Where-Object {$_.LastWriteTime -gt $WinUITransportPackageOutputTime})
#     $CreateWinUITransportPackage = $NewerDependencies -ne $null
#     if($CreateWinUITransportPackage)
#     {
#         $Dependencies = $NewerDependencies | Sort-Object -Descending -Property {$_.LastWriteTime} | Select-Object -First 5 | Format-Table LastWriteTime, FullName | Out-String
#         Write-Host "WinUI transport package has newer dependencies: $Dependencies ..." -ForegroundColor YELLOW
#     }
# }
# else
# {
#     Write-Host "WinUI transport package not found: $WinUITransportPackageOutput" -ForegroundColor YELLOW
# }

# if(!($Fake))
# {
#     if($CreateWinUITransportPackage)
#     {
#         # Clear previous WinUI transport package artifacts and rebuild
#         Remove-Item -Path $WinUITransportPackageCached -Recurse -Force -ErrorAction SilentlyContinue
#         Remove-Item -Path $WinUITransportPackageOutput -Force -ErrorAction SilentlyContinue
#         . (Join-Path $RepoRoot "build\nuspecs\build-nupkg.ps1") -VersionOverride $WinUIPackageVersion -PackageRoot $PackageRoot -OutputDir $PackageStore
#         if($LASTEXITCODE -ne 0)
#         {
#             Write-Host ".\build\nuspecs\build-nupkg.ps1 failed with exit code: $LASTEXITCODE" -ForegroundColor RED
#             exit $LASTEXITCODE
#         }
#     }

#     # Stage Mock WinAppSDK package customizations
#     $NugetStagingDir = (Join-Path $BuildOutput "WindowsAppSDKNugetPackage\build")
#     $null = New-Item -Path $NugetStagingDir -ItemType Directory -Force
#     Copy-Item (Join-Path $RepoRoot "scripts\MockWinAppSdkPackage.props") -destination (Join-Path $NugetStagingDir "Microsoft.WindowsAppSDK.Custom.props")
#     Copy-Item (Join-Path $RepoRoot "scripts\MockWinAppSdkPackage.targets") -destination (Join-Path $NugetStagingDir "Microsoft.WindowsAppSDK.Custom.targets")
# }

# pushd (Join-Path $RepoRoot "WindowsAppSDKAggregator")

# # Do WinAppSDK one-time setup (mainly, creating and installing test cert)
# if(!(Test-Path ".\.user\winappsdk.certificate.test.pfx" ))
# {
#     .\OneTimeSetupAll.ps1 -CertPassword "password"
#     if($LASTEXITCODE -ne 0)
#     {
#         popd
#         Write-Host ".\WindowsAppSDKAggregator\OneTimeSetupAll.ps1 failed with exit code: $LASTEXITCODE" -ForegroundColor RED
#         exit $LASTEXITCODE
#     }
# }

# # Build Mock WinAppSDK package, based on dependencies
# if($AzurePipelineBuild.IsPresent)
# {
#     Write-Host "##vso[task.setvariable variable=WindowsAppSDKMockPackagePath;]$PackageStore"
# }

# . .\buildall.ps1 -WindowsAppSDKPackageVersion $WindowsAppSDKPackageVersion -Platform $Platform -Configuration $Configuration -Channel "dev" -TransportPackages "" -BuildOutput $BuildOutput -NugetConfig $NugetConfig -PackageCache $PackageCache -PackageStore $PackageStore -LocalPackages $PackageStore -SkipVerifyProductVersion -AzurePipelineBuild:$AzurePipelineBuild -Fake:$Fake

# if($Fake)
# {
#     if($CreateWinUITransportPackage -or $CreateWindowsAppSDKPackage)
#     {
#         Write-Host "Fake: pack is required" -ForegroundColor YELLOW
#         exit 1
#     }
#     Write-Host "Fake: pack is not required" -ForegroundColor GREEN
#     exit 0
# }
# if($CleanOutput)
# {
#     # Delete WindowsAppSdkAggregator binaries to prevent pipelines from running BinSkim on them
#     Remove-Item -Path $BuildOutput -Recurse -Force -ErrorAction SilentlyContinue
# }
# popd
# if($LASTEXITCODE -ne 0)
# {
#     Write-Host ".\WindowsAppSDKAggregator\buildAll.ps1 failed with exit code: $LASTEXITCODE" -ForegroundColor RED
#     exit $LASTEXITCODE
# }
# exit 0