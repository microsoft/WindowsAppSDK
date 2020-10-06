[CmdLetBinding()]
Param(
    [string]$Platform,
    [string]$Configuration
)

$payloadDir = "HelixPayload\$Configuration\$Platform"

$nugetPackagesDir = Join-Path (Split-Path -Parent $script:MyInvocation.MyCommand.Path) "packages"

# Create the payload directory. Remove it if it already exists.
If(test-path $payloadDir)
{
    Remove-Item $payloadDir -Recurse
}

New-Item -ItemType Directory -Force -Path $payloadDir


# Copy files from nuget packages
cp C:\"Program Files (x86)"\"Windows Kits"\10\Testing\Runtimes\TAEF\$(Platform)\WTTLog.dll $payloadDir

cp DCPP/Helix/runtests.cmd $payloadDir

cp DCPP/Helix/ConvertWttLogToXUnit.cs $payloadDir

cp DCPP/Helix/ConvertWttLogToXUnit.ps1 $payloadDir

cp taeftest/$Platform-$Configuration-taeftest/ProjectReunionHelix.dll $payloadDir

cp DCPP/Helix/packages/Taef.Redist.Wlk.10.52.200221001/build/Binaries/$Platform/* $payloadDir

cp DCPP/Helix/packages/Taef.Redist.Wlk.10.52.200221001/build/Binaries/$Platform/CoreClr/* $payloadDir

dir $payloadDir