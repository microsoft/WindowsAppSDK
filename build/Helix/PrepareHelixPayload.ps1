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

cp BuildOutput/$Configuration/$Platform/BaseUnitTests/BaseUnitTests.dll $payloadDir

#cp BuildOutput/$Configuration/$Platform/UnitTest/UnitTest.dll $payloadDir

cp dev/MRTCore/mrt/packages/Microsoft.Taef.Redist.Wlk.*/build/Binaries/$Platform/* $payloadDir

cp dev/MRTCore/mrt/packages/Microsoft.Taef.Redist.Wlk.*/build/Binaries/$Platform/netstandard2.0/* $payloadDir

mkdir $payloadDir/files

cp dev/MRTCore/mrt/mrm/UnitTests/files/* $payloadDir/files

cp dev/MRTCore/mrt/mrm/UnitTests/*.xml $payloadDir

dir $payloadDir