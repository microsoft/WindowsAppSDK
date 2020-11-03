[CmdLetBinding()]
Param(
    [string]$Platform,
    [string]$Configuration
)

$payloadDir = "HelixPayload\$buildConfiguration\$Platform"

$nugetPackagesDir = Join-Path (Split-Path -Parent $script:MyInvocation.MyCommand.Path) "packages"

# Create the payload directory. Remove it if it already exists.
If(test-path $payloadDir)
{
    Remove-Item $payloadDir -Recurse
}

New-Item -ItemType Directory -Force -Path $payloadDir


# Copy files from nuget packages
cp C:\"Program Files (x86)"\"Windows Kits"\10\Testing\Runtimes\TAEF\$Platform\WTTLog.dll $payloadDir

cp build/Helix/runtests.cmd $payloadDir

cp build/Helix/ConvertWttLogToXUnit.cs $payloadDir

cp build/Helix/ConvertWttLogToXUnit.ps1 $payloadDir

cp $Platform-$Configuration-taeftest/ProjectReunionHelix.dll $payloadDir

cp BuildOutput/$Configuration/$Platform/BaseUnitTests/BaseUnitTests.dll $payloadDir

cp build/Helix/packages/Taef.Redist.Wlk.10.57.200918006-develop/build/Binaries/$Platform/* $payloadDir

cp build/Helix/packages/Taef.Redist.Wlk.10.57.200918006-develop/build/Binaries/$Platform/CoreClr/* $payloadDir

dir $payloadDir