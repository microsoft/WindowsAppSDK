<#
This script is to build the Foundation transport package that will be used to generate the windows app sdk package.
This script is called from BuildAll.ps1 from the aggregator repo and should not be called directly.

PackageVersion: NuGet Package Version that will be used in the packing of Foundation Transport Package
ComponentPackageVersion: NuGet Package Version that will be used in the packing of Foundation Component Package
Platform: Comma delimited string of platforms to run.
Configuration: Comma delimited string of configurations to run.
AzureBuildStep: Only used by the pipeline to perform tasks such as signing in between the steps
OutputDirectory: Pack Location of the Nuget Package
UpdateVersionDetailsPath: Path to a ps1 or cmd that updates version.details.xml.
Clean: Performs a clean on BuildOutput, Obj, and build\override

Note about building in different environments.
The feed the NuGet.config points to changes depending on the branch.
Develop branch points to the internal feed.
Main branch points to the external feed.
#>

Param(
    [string]$PackageVersion = "",
    [string]$ComponentPackageVersion = "",
    [string]$Platform = "x64",
    [string]$Configuration = "Release",
    [string]$AzureBuildStep = "all",
    [string]$OutputDirectory = (Split-Path $MyInvocation.MyCommand.Path) + "\BuildOutput",
    [string]$PGOBuildMode = "Optimize",
    [string]$UpdateVersionDetailsPath = $null,
    [switch]$Clean = $false
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

$env:Build_SourcesDirectory = (Split-Path $MyInvocation.MyCommand.Path)
$buildOverridePath = "build\override"
$BasePath = "BuildOutput/FullNuget"
$ComponentBasePath = "BuildOutput/ComponentNuget"
$BasePackagePath = "BuildOutput/BaseNuget"
$BaseComponentPath = "BuildOutput/BaseComponentNuget"

# FUTURE(YML2PS): Update build to no longer place generated files in sources directory
if ($Clean)
{
    $CleanTargets = @(
      "BuildOutput",
      "obj",
      ".user",
      $buildOverridePath
    )

    foreach ($CleanTarget in $CleanTargets)
    {
      $CleanTargetPath = (Join-Path $env:Build_SourcesDirectory $CleanTarget)

      if (Test-Path ($CleanTargetPath)) {
        Remove-Item $CleanTargetPath -recurse
      }
    }

    Exit
}

# Find the Version Value provided by WindowsAppSDKConfig in Version.Details.xml
# The version field of Microsoft.WindowsAppSDK.Version is the value provided byWindowsAppSDKConfig
[xml]$versionDetailsPath = Get-Content -Path "$env:Build_SourcesDirectory\eng\Version.Details.xml"
$versionFromConfig = $versionDetailsPath.Dependencies.ToolsetDependencies.Dependency | Where-Object { $_.Name -eq "Microsoft.WindowsAppSDK.Version" }
if ([string]::IsNullOrEmpty($PackageVersion))
{
    $PackageVersion = $versionFromConfig.Version;
    Write-Host "Updating PackageVersion from Microsoft.WindowsAppSDK.Version in eng\Version.Details.xml: $PackageVersion"
}

if ([string]::IsNullOrEmpty($ComponentPackageVersion))
{
    Write-Host $versionFromConfig.Version
    $ComponentPackageVersion = $versionFromConfig.Version;
    Write-Host "Updating ComponentPackageVersion from Microsoft.WindowsAppSDK.Version in eng\Version.Details.xml: $ComponentPackageVersion"
}

$configurationForMrtAndAnyCPU = "Release"
$MRTSourcesDirectory = "dev\MRTCore"

$VCToolsInstallDir = . "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -Latest -prerelease -requires Microsoft.Component.MSBuild -property InstallationPath
write-host "VCToolsInstallDir: $VCToolsInstallDir"

$msBuildPath = "$VCToolsInstallDir\MSBuild\Current\Bin\msbuild.exe"
write-host "msBuildPath: $msBuildPath"

# Generate overrides
# Make sure override directory exists.
if(-not (test-path "$buildOverridePath"))
{
    new-item -path "$buildOverridePath" -itemtype "directory"
}

function NugetRestore([string] $Label, [string] $Target)
{
    if ($AzureBuildStep -ne "all")
    {
        $env:NUGET_RESTORE_MSBUILD_ARGS = "/binaryLogger:BuildOutput\binlogs\$Label.restore.$Platform.$Configuration.binlog /p:Platform=$Platform /p:Configuration=$Configuration"
    }
    nuget restore $Target -configfile NuGet.config
    if ($lastexitcode -ne 0)
    {
        write-host "ERROR: nuget.exe restore $Label FAILED."
        exit 1
    }
}

Try {
    $WindowsAppSDKBuildPipeline = 0
    $WindowsAppSDKVersionProperty = ""

    .\tools\GenerateDynamicDependencyOverrides.ps1 -Path "$buildOverridePath"
    .\tools\GeneratePushNotificationsOverrides.ps1 -Path "$buildOverridePath"

    if ($AzureBuildStep -ne "all")
    {
        # Some builds have "-branchname" appended, but when this happens the environment variable
        # TFS_BUILDNUMBER has the un-modified version.
        if ($env:TFS_BUILDNUMBER)
        {
            $env:BUILD_BUILDNUMBER = $env:TFS_BUILDNUMBER
        }
        Write-Host "BuildNumber : " $env:BUILD_BUILDNUMBER
        $yymm = $env:BUILD_BUILDNUMBER.substring($env:BUILD_BUILDNUMBER.length - 10, 4)
        $dd = $env:BUILD_BUILDNUMBER.substring($env:BUILD_BUILDNUMBER.length - 5, 2)
        $revision = $env:BUILD_BUILDNUMBER.substring($env:BUILD_BUILDNUMBER.length - 3, 3)

        $WindowsAppSDKVersionProperty = "/p:WindowsAppSDKVersionBuild=$yymm /p:WindowsAppSDKVersionRevision=$dd$revision"

        # If $AzureBuildStep is not "all", that means we are in the pipeline
        $WindowsAppSDKBuildPipeline = 1
    }
    # PreFastSetup is specifically for use when preparing for PREFast scans. It triggers the same actions below as BuildFoundation or BuildMRT, except
    # PreFastSetup stops short of calling msBuild.exe to build the target, which the Guardian:PREFast task does _not_ support, so the caller of this
    # script needs to resort to calling the MSBuild/VSBuild task later to build the target, which the Guardian:PREFast task does support. Structuring
    # the code this way allows minimally diveraging the flow while supporting building the target both via this script and the VSBuild/MSBuild task.
    if (($AzureBuildStep -eq "all") -Or (($AzureBuildStep -eq "BuildFoundation") -Or ($AzureBuildStep -eq "BuildMRT") -Or ($AzureBuildStep -eq "PreFastSetup")))
    {
        NugetRestore "WindowsAppRuntime" "WindowsAppRuntime.sln"
        NugetRestore "Microsoft.WindowsAppRuntime.Bootstrap.Net" "base\dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj"

        $srcPath = Get-Childitem -Path 'dev\WindowsAppRuntime_Insights\packages' -File 'MicrosoftTelemetry.h' -Recurse

        if (($srcPath -ne $null))
        {
            $destinationPaths = Get-Childitem -Path 'packages' -File 'Traceloggingconfig.h' -Recurse

            if (($destinationPaths -ne $null)) 
            {
                foreach ($destPath in $destinationPaths) {
                Write-Host 'SourcePath:' $srcPath.FullName
                Write-Host 'DestinationPath:' $destPath.FullName
                Copy-Item -Force $srcPath.FullName $destPath.FullName
                }
            }
        }

        if ($lastexitcode -ne 0)
        {
            write-host "ERROR: Copy-Item -Force $srcPath.FullName $destPath.FullName FAILED."
            exit 1
        }
    }
    # PreFastSetup intentionally skips the call to MSBuild.exe below.
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "BuildFoundation"))
    {
        foreach($configurationToRun in $configuration.Split(","))
        {
            foreach($platformToRun in $platform.Split(","))
            {
                write-host "Building WindowsAppRuntime.sln for configuration $configurationToRun and platform:$platformToRun"
                & $msBuildPath /restore `
                                WindowsAppRuntime.sln `
                                /p:Configuration=$configurationToRun `
                                /p:Platform=$platformToRun `
                                /p:RestoreConfigFile=NuGet.config `
                                /binaryLogger:"BuildOutput/binlogs/WindowsAppRuntime.$platformToRun.$configurationToRun.binlog" `
                                $WindowsAppSDKVersionProperty `
                                /p:PGOBuildMode=$PGOBuildMode `
                                /p:WindowsAppSDKCleanIntermediateFiles=true `
                                /p:AppxSymbolPackageEnabled=false `
                                /p:WindowsAppSDKBuildPipeline=$WindowsAppSDKBuildPipeline
                if ($lastexitcode -ne 0)
                {
                    write-host "ERROR: msbuild.exe WindowsAppRuntime.sln FAILED."
                    exit 1
                }
            }
        }
    }
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "BuildMRT") -Or ($AzureBuildStep -eq "PreFastSetup"))
    {
        #------------------
        #    Build mrtcore.sln and move output to staging.
        #------------------

        #Restore packages from mrt.
        NugetRestore "MrtCore" "$MRTSourcesDirectory\mrt\MrtCore.sln"
        NugetRestore "Microsoft.Windows.ApplicationModel.Resources" "$MRTSourcesDirectory\mrt\Microsoft.Windows.ApplicationModel.Resources\src\packages.config"
        NugetRestore "mrmex" "$MRTSourcesDirectory\mrt\mrm\mrmex\packages.config"
        NugetRestore "mrmmin" "$MRTSourcesDirectory\mrt\mrm\mrmmin\packages.config"
        NugetRestore "unittests" "$MRTSourcesDirectory\mrt\mrm\unittests\packages.config"

        # Init mrtcore
        foreach($platformToRun in $platform.Split(","))
        {
            & $MRTSourcesDirectory\build\init.cmd /envonly $platformToRun\fre

            if ($lastexitcode -ne 0)
            {
                write-host "ERROR: init.cmd /envonly $platformToRun\fre FAILED."
            }
        }

        # PreFastSetup intentionally skips the call to MSBuild.exe below.
        if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "BuildMRT"))
        {
            # Build mrt core.
            foreach($platformToRun in $platform.Split(","))
            {
                write-host "Building MrtCore.sln for configuration $configurationForMrtAndAnyCPU and platform:$platformToRun"
                & $msBuildPath /restore "$MRTSourcesDirectory\mrt\MrtCore.sln" `
                                /p:Configuration=$configurationForMrtAndAnyCPU `
                                /p:Platform=$platformToRun `
                                /p:RestoreConfigFile=NuGet.config `
                                /p:PGOBuildMode=$PGOBuildMode `
                                /binaryLogger:"BuildOutput/binlogs/MrtCore.$platformToRun.$configurationForMrtAndAnyCPU.binlog"

                if ($lastexitcode -ne 0)
                {
                    write-host "ERROR: msbuild.exe '$MRTSourcesDirectory\mrt\MrtCore.sln' FAILED."
                    exit 1
                }
            }
        }
    }
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "BuildAnyCPU"))
    {
        #------------------
        #    Build windowsAppRuntime.sln (anyCPU) and move output to staging.
        #------------------
        # build and restore AnyCPU
        & $msBuildPath /restore "base\dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj" /p:Configuration=$configurationForMrtAndAnyCPU /p:Platform=AnyCPU /p:RestoreConfigFile=NuGet.config
        if ($lastexitcode -ne 0)
        {
            write-host "ERROR: msbuild.exe Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj FAILED."
            exit 1
        }
    }

    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "StageFiles"))
    {
        #------------------
        #    Stage files for Packing
        #------------------
        if(-not (test-path "$BasePath"))
        {
            new-item -path "$BasePath" -itemtype "directory"
        }

        if(-not (test-path "$ComponentBasePath"))
        {
            new-item -path "$ComponentBasePath" -itemtype "directory"
        }

        if(-not (test-path "$BasePath\build\native"))
        {
            new-item -path "$BasePath\build\native" -itemtype "directory"
        }

        if(-not (test-path "$ComponentBasePath\build\native"))
        {
            new-item -path "$ComponentBasePath\build\native" -itemtype "directory"
        }

        # Copy WindowsAppRuntime.sln files
        foreach($configurationToRun in $configuration.Split(","))
        {
            foreach($platformToRun in $platform.Split(","))
            {
                # TODO: $windowsAppSdkBinariesPath may not be defined. Remove the temp downgrade to 1.0 once this issue has been fixed (b#52130179). 
                Set-StrictMode -Version 1.0
                .\build\CopyFilesToStagingDir.ps1 -BuildOutputDir 'BuildOutput' -OverrideDir "$buildOverridePath" -PublishDir "$windowsAppSdkBinariesPath" -NugetDir "$BasePath" -Platform $PlatformToRun -Configuration $ConfigurationToRun
                Set-StrictMode -Version 3.0
                if ($lastexitcode -ne 0)
                {
                    write-host "ERROR: msCopyFilesToStagingDir.ps1 FAILED."
                    exit 1
                }
            }
        }

        $nuSpecsPath = "build\NuSpecs"
        Copy-Item -Path "$nuSpecsPath\native\Microsoft.WindowsAppSDK.targets" -Destination "$BasePath\build\native\Microsoft.WindowsAppSDK.Foundation.targets"
        Copy-Item -Path "$nuSpecsPath\native\Microsoft.WindowsAppSDK.props" -Destination "$BasePath\build\native\Microsoft.WindowsAppSDK.Foundation.props"
        Copy-Item -Path "$nuSpecsPath\native\Microsoft.WindowsAppSDK.C.props" -Destination "$BasePath\build\native"
        Copy-Item -Path "$nuSpecsPath\native\Microsoft.WindowsAppSDK.WinRt.props" -Destination "$BasePath\build\native"

        # Bootstrapper and auto-initialization native targets have moved to the Base package.

        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.props" -Destination "$BasePath\build"

        # Bootstrapper and auto-initialization managed targets have moved to the Base package.

        Copy-Item -Path "$nuSpecsPath\AppxManifest.xml" -Destination "$BasePath\AppxManifest.xml"

        # Copy over mrt files
        foreach($platformToRun in $platform.Split(","))
        {
            Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\mrm\MRM.dll" -destination "$BasePath\runtimes\win10-$platformToRun\native" -force
            Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\mrm\MRM.pdb" -destination "$BasePath\runtimes\win10-$platformToRun\native" -force
            Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.pdb" -destination "$BasePath\runtimes\win10-$platformToRun\native" -force
            Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.dll" -destination "$BasePath\runtimes\win10-$platformToRun\native" -force

            Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\mrm\MRM.lib" -destination "$BasePath\lib\win10-$platformToRun" -force

            if($platformToRun -eq "x86")
            {
                Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources.Projection\Microsoft.Windows.ApplicationModel.Resources.Projection.dll" -destination "$BasePath\lib\net6.0-windows10.0.17763.0" -force
                Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources.Projection\Microsoft.Windows.ApplicationModel.Resources.Projection.pdb" -destination "$BasePath\lib\net6.0-windows10.0.17763.0" -force
                Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.winmd" -destination "$BasePath\lib\uap10.0" -force
                Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.Globalization.winmd" -destination "$BasePath\lib\uap10.0" -force
            }
        }

        # Copy MRT metadata files.
        Copy-Item -Path "$MRTSourcesDirectory\packaging\native\MrtCore.C.props" -Destination "$BasePath\build\native"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\native\MrtCore.props" -Destination "$BasePath\build\native"
        Copy-Item -Path "$MRTSourcesDirectory\mrt\core\src\MRM.h" -Destination "$BasePath\include"
        Copy-Item -Path "$MRTSourcesDirectory\mrt\Microsoft.Windows.ApplicationModel.Resources\src\Microsoft.Windows.ApplicationModel.Resources.idl" -Destination "$BasePath\include"

        # Bootstrap.Net.dll has moved to the Base package.

        #------------------
        #    Move other files and prepare manifest and appxmanifest.xml
        #------------------

        Copy-Item -Path "$nuSpecsPath\AppxManifest.xml" -Destination "$BasePath"

        if ($lastexitcode -ne 0)
        {
            write-host "ERROR: Copy-Item -Path AppxManifest.xml FAILED."
            exit 1
        }

        Copy-Item -Path "LICENSE" -Destination "$BasePath" -force

        if ($lastexitcode -ne 0)
        {
            write-host "ERROR: Copy-Item -Path LICENSE FAILED."
            exit 1
        }

        if ([string]::IsNullOrEmpty($env:Channel))
        {
            $componentLicenseFilePath = "LICENSE"
        }
        else
        {
            $componentLicenseFilePath = "WindowsAppSDKConfig\NuGetLicense\preview\license.txt"
            if ($env:Channel -eq 'stable')
            {
                $componentLicenseFilePath = "WindowsAppSDKConfig\NuGetLicense\release\license.txt"
            }
        }

        Copy-Item -Path $componentLicenseFilePath -Destination "$ComponentBasePath\license.txt" -force

        if ($lastexitcode -ne 0)
        {
            write-host "ERROR: Copy-Item -Path $componentLicenseFilePath FAILED."
            exit 1
        }

        # for some reason xslt.load changes the working directory to C:\windows\system32.
        # store the current working directory here.
        $workingDirectory = get-location
        $manifestPath = "$BasePath\manifests"

        # Make Microsoft.WindowsAppSDK.Foundation.manifest.
        $newitem = New-Item -ItemType Directory -Force -Path $manifestPath
        $xslt = New-Object System.Xml.Xsl.XslCompiledTransform
        $xslt.Load("$workingDirectory\build\TransformAppxManifest.xslt")
        $xslt.Transform("$workingDirectory\$BasePath\AppxManifest.xml", "$workingDirectory\$manifestPath\Microsoft.WindowsAppSdk.Foundation.manifest")

        if ($lastexitcode -ne 0)
        {
            write-host "ERROR: xslt.Transform FAILED."
            exit 1
        }

        build\Scripts\RobocopyWrapper.ps1 `
            -Source (Join-Path $BasePath 'build') `
            -dest (Join-Path $ComponentBasePath 'build')

        build\Scripts\RobocopyWrapper.ps1 `
            -Source (Join-Path $BasePath 'include') `
            -dest (Join-Path $ComponentBasePath 'include')

        build\Scripts\RobocopyWrapper.ps1 `
            -Source (Join-Path $BasePath 'build') `
            -dest (Join-Path $ComponentBasePath 'buildTransitive')

        # Copy transport package specific props / targets after we are done copying
        # for the other package.
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.TransportPackage.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.TransportPackage.props" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.TransportPackage.targets" -Destination "$BasePath\build\native"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.TransportPackage.props" -Destination "$BasePath\build\native"

        build\Scripts\RobocopyWrapper.ps1 `
            -Source (Join-Path $BasePath 'lib\uap10.0') `
            -dest (Join-Path $ComponentBasePath 'metadata')

        build\scripts\CopyContents.ps1 `
            -SourceDir "$PSScriptRoot\$BasePath" `
            -ContentsList @('lib') `
            -Exclude @('*.winmd', '*.pdb', '*.lib') `
            -TargetDir $ComponentBasePath

        build\scripts\CopyContents.ps1 `
            -SourceDir "$PSScriptRoot\$BasePath" `
            -ContentsList @('runtimes\win-*') `
            -Exclude @('*.pdb') `
            -TargetDir $ComponentBasePath

        foreach($platformToRun in $platform.Split(","))
        {
            build\Scripts\RobocopyWrapper.ps1 `
                -Source "$PSScriptRoot\$BasePath\lib\win10-$platformToRun" `
                -dest "$ComponentBasePath\lib\native\$platformToRun"

            build\scripts\CopyContents.ps1 `
                -SourceDir "$PSScriptRoot\$BasePath\runtimes\win10-$platformToRun" `
                -ContentsList @(
                    'native\DeploymentAgent.exe',
                    'native\Microsoft.Windows.ApplicationModel.Resources.dll',
                    'native\Microsoft.WindowsAppRuntime.dll',
                    'native\Microsoft.WindowsAppRuntime.Insights.Resource.dll',
                    'native\Microsoft.WindowsAppRuntime.pri',
                    'native\MRM.dll',
                    'native\PushNotificationsLongRunningTask.ProxyStub.dll',
                    'native\RestartAgent.exe') `
                -TargetDir "$ComponentBasePath\runtimes-framework\win-$platformToRun"
        }

        # Populate ARM64EC folders with x64 content
        if ($platform.Split(",") -contains "x64")
        {
            build\Scripts\RobocopyWrapper.ps1 `
                -Source "$ComponentBasePath\lib\native\x64" `
                -dest "$ComponentBasePath\lib\native\arm64ec"

            build\Scripts\RobocopyWrapper.ps1 `
                -Source "$ComponentBasePath\runtimes\win-x64" `
                -dest "$ComponentBasePath\runtimes\win-arm64ec"

            build\Scripts\RobocopyWrapper.ps1 `
                -Source "$ComponentBasePath\runtimes-framework\win-x64" `
                -dest "$ComponentBasePath\runtimes-framework\win-arm64ec"
        }

        Copy-Item -Path "$nuSpecsPath\package.appxfragment" -Destination "$ComponentBasePath\runtimes-framework\package.appxfragment"

        # Populate Intellisense files
        $IntellisensePath = "$PSScriptRoot\build\NuSpecs\Intellisense"

        $LibPaths = @(
            (Join-Path $ComponentBasePath "metadata"),
            (Join-Path $ComponentBasePath "lib\net6.0-windows10.0.17763.0")
        )

        foreach ($File in Get-ChildItem -Path $LibPaths)
        {
            if ($File.Extension -ne ".dll" -and $File.Extension -ne ".winmd")
            {
                continue
            }

            $IntellisenseFile = (Join-Path $IntellisensePath "$($File.BaseName).xml")
            $DestinationDir = ($File.DirectoryName)

            if (-not (Test-Path $IntellisenseFile))
            {
                Write-Host "Intellisense file not found: $IntellisenseFile"
                continue
            }

            Copy-Item -Path $IntellisenseFile -Destination $DestinationDir
        }
    }
    if ($AzureBuildStep -eq "BuildBase")
    {
        #------------------
        #    Build the Bootstrap DLL and Bootstrap.Net for the Base package.
        #    No Foundation build dependency required.
        #------------------

        # Restore NuGet packages for the solution (packages.config projects)
        # Clear NUGET_RESTORE_MSBUILD_ARGS to avoid multi-platform arg issues
        $savedMsBuildArgs = $env:NUGET_RESTORE_MSBUILD_ARGS
        $env:NUGET_RESTORE_MSBUILD_ARGS = ""
        nuget restore WindowsAppRuntime.sln -configfile NuGet.config
        if ($lastexitcode -ne 0)
        {
            write-host "ERROR: nuget.exe restore WindowsAppRuntime.sln FAILED."
            exit 1
        }
        $env:NUGET_RESTORE_MSBUILD_ARGS = $savedMsBuildArgs

        foreach($configurationToRun in $configuration.Split(","))
        {
            foreach($platformToRun in $platform.Split(","))
            {
                write-host "Building WindowsAppRuntime_BootstrapDLL for Base: $configurationToRun|$platformToRun"
                & $msBuildPath /restore `
                                "base\dev\WindowsAppRuntime_BootstrapDLL\WindowsAppRuntime_BootstrapDLL.vcxproj" `
                                /p:Configuration=$configurationToRun `
                                /p:Platform=$platformToRun `
                                /p:RestoreConfigFile=NuGet.config `
                                /binaryLogger:"BuildOutput/binlogs/WindowsAppRuntime_BootstrapDLL.$platformToRun.$configurationToRun.binlog" `
                                $WindowsAppSDKVersionProperty `
                                /p:WindowsAppSDKCleanIntermediateFiles=true `
                                /p:AppxSymbolPackageEnabled=false `
                                /p:WindowsAppSDKBuildPipeline=$WindowsAppSDKBuildPipeline
                if ($lastexitcode -ne 0)
                {
                    write-host "ERROR: msbuild.exe WindowsAppRuntime_BootstrapDLL FAILED."
                    exit 1
                }
            }
        }

        # Build Bootstrap.Net (AnyCPU)
        & $msBuildPath /restore "base\dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj" /p:Configuration=$configurationForMrtAndAnyCPU /p:Platform=AnyCPU /p:RestoreConfigFile=NuGet.config
        if ($lastexitcode -ne 0)
        {
            write-host "ERROR: msbuild.exe Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj FAILED."
            exit 1
        }
    }
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "StageBaseFiles"))
    {
        #------------------
        #    Stage files for Base Package
        #------------------
        if(-not (test-path "$BasePackagePath"))
        {
            new-item -path "$BasePackagePath" -itemtype "directory"
        }
        if(-not (test-path "$BaseComponentPath"))
        {
            new-item -path "$BaseComponentPath" -itemtype "directory"
        }
        if(-not (test-path "$BasePackagePath\build\native"))
        {
            new-item -path "$BasePackagePath\build\native" -itemtype "directory" -force
        }
        if(-not (test-path "$BaseComponentPath\build\native"))
        {
            new-item -path "$BaseComponentPath\build\native" -itemtype "directory" -force
        }
        if(-not (test-path "$BasePackagePath\include"))
        {
            new-item -path "$BasePackagePath\include" -itemtype "directory" -force
        }

        $nuSpecsPath = "base\build\NuSpecs"

        # Stage Base native targets
        Copy-Item -Path "$nuSpecsPath\native\Microsoft.WindowsAppSDK.Base.targets" -Destination "$BasePackagePath\build\native\Microsoft.WindowsAppSDK.Base.targets"
        Copy-Item -Path "$nuSpecsPath\native\Microsoft.WindowsAppSDK.AutoInitializer.targets" -Destination "$BasePackagePath\build\native"
        Copy-Item -Path "$nuSpecsPath\native\Microsoft.WindowsAppSDK.Bootstrap.targets" -Destination "$BasePackagePath\build\native"
        Copy-Item -Path "$nuSpecsPath\native\Microsoft.WindowsAppSDK.CompatibilitySetter.targets" -Destination "$BasePackagePath\build\native"
        Copy-Item -Path "$nuSpecsPath\native\Microsoft.WindowsAppSDK.DeploymentManager.targets" -Destination "$BasePackagePath\build\native"
        Copy-Item -Path "$nuSpecsPath\native\Microsoft.WindowsAppSDK.UndockedRegFreeWinRT.targets" -Destination "$BasePackagePath\build\native"

        # Stage Base managed targets
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Base.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Base.props" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.BaseCommon.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.AutoInitializer.CS.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.AutoInitializerCommon.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Bootstrap.CS.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.BootstrapCommon.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.CompatibilitySetter.CS.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.DeploymentManager.CS.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.DeploymentManagerCommon.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.UndockedRegFreeWinRT.CS.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.UndockedRegFreeWinRTCommon.targets" -Destination "$BasePackagePath\build"

        # Stage deployment-mode targets (from aggregator)
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.SelfContained.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.SingleFile.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.SingleProject.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Arm64Ec.targets" -Destination "$BasePackagePath\build"

        # Stage native props (delegates to parent props)
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Base.Native.props" -Destination "$BasePackagePath\build\native\Microsoft.WindowsAppSDK.Base.props"

        # Stage auto-initializer source files from their source locations (no build needed)
        Copy-Item -path "base\dev\include\WindowsAppRuntimeAutoInitializer.cpp" -destination "$BasePackagePath\include" -force
        Copy-Item -path "base\dev\include\WindowsAppRuntimeAutoInitializer.cs" -destination "$BasePackagePath\include" -force
        Copy-Item -path "base\dev\include\DeploymentManagerAutoInitializer.cpp" -destination "$BasePackagePath\include" -force
        Copy-Item -path "base\dev\include\DeploymentManagerAutoInitializer.cs" -destination "$BasePackagePath\include" -force
        Copy-Item -path "base\dev\include\UndockedRegFreeWinRT-AutoInitializer.cpp" -destination "$BasePackagePath\include" -force
        Copy-Item -path "base\dev\include\UndockedRegFreeWinRT-AutoInitializer.cs" -destination "$BasePackagePath\include" -force
        Copy-Item -path "base\dev\WindowsAppRuntime_BootstrapDLL\MddBootstrap.h" -destination "$BasePackagePath\include" -force
        Copy-Item -path "base\dev\WindowsAppRuntime_BootstrapDLL\MddBootstrapAutoInitializer.cpp" -destination "$BasePackagePath\include" -force
        Copy-Item -path "base\dev\WindowsAppRuntime_BootstrapDLL\MddBootstrapAutoInitializer.cs" -destination "$BasePackagePath\include" -force

        # Generate WindowsAppSDK-VersionInfo.h for the Base package
        # Parse version from ComponentPackageVersion (e.g., "2.0.260326000-experimental")
        $versionParts = $ComponentPackageVersion -split '-'
        $numericParts = $versionParts[0] -split '\.'
        $vi_major = [int]$numericParts[0]
        $vi_minor = [int]$numericParts[1]
        $vi_patch = [int]$numericParts[2]
        $vi_channel = if ($versionParts.Length -gt 1) { $versionParts[1] } else { "" }
        $vi_tag = $vi_channel
        $vi_shorttag = if ($vi_tag.Length -gt 0) { $vi_tag.Substring(0,1) + ($vi_tag -replace '[^0-9]','') } else { "" }
        $vi_formatted_tag = if ($vi_tag.Length -gt 0) { "-$vi_tag" } else { "" }
        $vi_formatted_shorttag = if ($vi_shorttag.Length -gt 0) { "-$vi_shorttag" } else { "" }
        $vi_majorminor = ($vi_major -shl 16) -bor $vi_minor
        $vi_majorminor_hex = "{0:X8}" -f $vi_majorminor
        $vi_version_uint64 = [uint64]$vi_major -shl 48 -bor [uint64]$vi_minor -shl 32 -bor [uint64]$vi_patch -shl 16
        $vi_version_uint64_hex = "{0:X16}" -f $vi_version_uint64
        $versionInfoHeader = @"
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

// <auto-generated>
// DO NOT MODIFY. Generated by BuildAll.ps1 StageBaseFiles step.
// </auto-generated>

#ifndef _WINDOWSAPPSDK_VERSIONINFO_H__
#define _WINDOWSAPPSDK_VERSIONINFO_H__

#define WINDOWSAPPSDK_RELEASE_MAJOR                         ${vi_major}u
#define WINDOWSAPPSDK_RELEASE_MINOR                         ${vi_minor}u
#define WINDOWSAPPSDK_RELEASE_PATCH                         ${vi_patch}u
#define WINDOWSAPPSDK_RELEASE_MAJORMINOR                    0x${vi_majorminor_hex}u
#define WINDOWSAPPSDK_RELEASE_CHANNEL                       "${vi_channel}"
#define WINDOWSAPPSDK_RELEASE_CHANNEL_W                     L"${vi_channel}"
#define WINDOWSAPPSDK_RELEASE_VERSION_TAG                   "${vi_tag}"
#define WINDOWSAPPSDK_RELEASE_VERSION_TAG_W                 L"${vi_tag}"
#define WINDOWSAPPSDK_RELEASE_VERSION_SHORTTAG              "${vi_shorttag}"
#define WINDOWSAPPSDK_RELEASE_VERSION_SHORTTAG_W            L"${vi_shorttag}"
#define WINDOWSAPPSDK_RELEASE_FORMATTED_VERSION_TAG         "${vi_formatted_tag}"
#define WINDOWSAPPSDK_RELEASE_FORMATTED_VERSION_TAG_W       L"${vi_formatted_tag}"
#define WINDOWSAPPSDK_RELEASE_FORMATTED_VERSION_SHORTTAG    "${vi_formatted_shorttag}"
#define WINDOWSAPPSDK_RELEASE_FORMATTED_VERSION_SHORTTAG_W  L"${vi_formatted_shorttag}"

#define WINDOWSAPPSDK_RUNTIME_VERSION_UINT64                0x${vi_version_uint64_hex}ui64

#ifdef __cplusplus
#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && (_MSVC_LANG >= 201703L))
namespace Microsoft::WindowsAppSDK
{
    constexpr uint16_t Release_Major{ static_cast<uint16_t>(${vi_major}) };
    constexpr uint16_t Release_Minor{ static_cast<uint16_t>(${vi_minor}) };
    constexpr uint32_t Release_Patch{ ${vi_patch}u };
    constexpr uint32_t Release_MajorMinor{ 0x${vi_majorminor_hex}u };
    constexpr PCWSTR Release_Channel{ L"${vi_channel}" };
    constexpr PCWSTR Release_VersionTag{ L"${vi_tag}" };
    constexpr PCWSTR Release_VersionShortTag{ L"${vi_shorttag}" };
    constexpr PCWSTR Release_FormattedVersionTag{ L"${vi_formatted_tag}" };
    constexpr PCWSTR Release_FormattedVersionShortTag{ L"${vi_formatted_shorttag}" };
    constexpr uint64_t Runtime_Version_UInt64{ 0x${vi_version_uint64_hex}ui64 };
}
#endif // __cplusplus >= 201703L || _MSVC_LANG >= 201703L
#endif // __cplusplus

#endif // _WINDOWSAPPSDK_VERSIONINFO_H__
"@
        $versionInfoHeader | Out-File -Encoding UTF8 -FilePath "$BasePackagePath\include\WindowsAppSDK-VersionInfo.h"
        Write-Host "Generated WindowsAppSDK-VersionInfo.h (Major=$vi_major, Minor=$vi_minor, Patch=$vi_patch, Channel=$vi_channel)"

        # Generate WindowsAppSDK-VersionInfo.cs for the Base package (used by C# auto-initializer)
        $versionInfoCs = @"
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

// <auto-generated>
// DO NOT MODIFY. Generated by BuildAll.ps1 StageBaseFiles step.
// </auto-generated>

namespace Microsoft.WindowsAppSDK
{
    // Release information
    internal class Release
    {
        internal const ushort Major = ${vi_major};
        internal const ushort Minor = ${vi_minor};
        internal const uint MajorMinor = 0x${vi_majorminor_hex};
        internal const string Channel = "${vi_channel}";
        internal const string VersionTag = "${vi_tag}";
        internal const string VersionShortTag = "${vi_shorttag}";
        internal const string FormattedVersionTag = "${vi_formatted_tag}";
        internal const string FormattedVersionShortTag = "${vi_formatted_shorttag}";
    }

    namespace Runtime
    {
        internal class Identity
        {
            internal const string Publisher = "CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US";
            internal const string PublisherId = "8wekyb3d8bbwe";
        }

        internal class Version
        {
            internal const ushort Major = ${vi_major};
            internal const ushort Minor = ${vi_minor};
            internal const ushort Build = 0;
            internal const ushort Revision = 0;
            internal const ulong UInt64 = 0x${vi_version_uint64_hex};
            internal const string DotQuadString = "${vi_major}.${vi_minor}.0.0";
        }
    }
}
"@
        $versionInfoCs | Out-File -Encoding UTF8 -FilePath "$BasePackagePath\include\WindowsAppSDK-VersionInfo.cs"
        Write-Host "Generated WindowsAppSDK-VersionInfo.cs"

        # Stage Bootstrap binaries per-platform (from build output)
        foreach($configurationToRun in $configuration.Split(","))
        {
            foreach($platformToRun in $platform.Split(","))
            {
                $bootstrapOutput = "BuildOutput\$configurationToRun\$platformToRun\WindowsAppRuntime_BootstrapDLL"

                if(-not (test-path "$BasePackagePath\runtimes\win-$platformToRun\native"))
                {
                    new-item -path "$BasePackagePath\runtimes\win-$platformToRun\native" -itemtype "directory" -force
                }
                if(-not (test-path "$BasePackagePath\lib\win10-$platformToRun"))
                {
                    new-item -path "$BasePackagePath\lib\win10-$platformToRun" -itemtype "directory" -force
                }
                Copy-Item -path "$bootstrapOutput\Microsoft.WindowsAppRuntime.Bootstrap.dll" -destination "$BasePackagePath\runtimes\win-$platformToRun\native" -force -ErrorAction SilentlyContinue
                Copy-Item -path "$bootstrapOutput\Microsoft.WindowsAppRuntime.Bootstrap.pdb" -destination "$BasePackagePath\runtimes\win-$platformToRun\native" -force -ErrorAction SilentlyContinue
                Copy-Item -path "$bootstrapOutput\Microsoft.WindowsAppRuntime.Bootstrap.lib" -destination "$BasePackagePath\lib\win10-$platformToRun" -force -ErrorAction SilentlyContinue
            }
        }

        # Stage Bootstrap.Net.dll
        $anyCpuConfig = $configuration.Split(",")[0]
        $bootstrapNetDir = "BuildOutput\$anyCpuConfig\AnyCPU\Microsoft.WindowsAppRuntime.Bootstrap.Net"
        if(-not (test-path "$BasePackagePath\lib\net6.0-windows10.0.17763.0"))
        {
            new-item -path "$BasePackagePath\lib\net6.0-windows10.0.17763.0" -itemtype "directory" -force
        }
        Copy-Item -path "$bootstrapNetDir\Microsoft.WindowsAppRuntime.Bootstrap.Net.dll" -destination "$BasePackagePath\lib\net6.0-windows10.0.17763.0" -force -ErrorAction SilentlyContinue

        # Copy Base package files to component path
        build\Scripts\RobocopyWrapper.ps1 `
            -Source (Join-Path $BasePackagePath 'build') `
            -dest (Join-Path $BaseComponentPath 'build')

        build\Scripts\RobocopyWrapper.ps1 `
            -Source (Join-Path $BasePackagePath 'include') `
            -dest (Join-Path $BaseComponentPath 'include')

        build\Scripts\RobocopyWrapper.ps1 `
            -Source (Join-Path $BasePackagePath 'build') `
            -dest (Join-Path $BaseComponentPath 'buildTransitive')

        # Copy transport package specific props / targets
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Base.TransportPackage.targets" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Base.TransportPackage.props" -Destination "$BasePackagePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Base.TransportPackage.targets" -Destination "$BasePackagePath\build\native"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Base.TransportPackage.props" -Destination "$BasePackagePath\build\native"

        Copy-Item -Path "LICENSE" -Destination "$BasePackagePath\license.txt" -force
        Copy-Item -Path "LICENSE" -Destination "$BaseComponentPath\license.txt" -force

        # Copy runtimes and lib to component path
        foreach($platformToRun in $platform.Split(","))
        {
            if (test-path "$BasePackagePath\runtimes\win-$platformToRun")
            {
                build\Scripts\RobocopyWrapper.ps1 `
                    -Source "$BasePackagePath\runtimes\win-$platformToRun" `
                    -dest "$BaseComponentPath\runtimes\win-$platformToRun"
            }
            if (test-path "$BasePackagePath\lib\win10-$platformToRun")
            {
                build\Scripts\RobocopyWrapper.ps1 `
                    -Source "$BasePackagePath\lib\win10-$platformToRun" `
                    -dest "$BaseComponentPath\lib\win10-$platformToRun"
            }
        }
        if (test-path "$BasePackagePath\lib\net6.0-windows10.0.17763.0")
        {
            build\Scripts\RobocopyWrapper.ps1 `
                -Source "$BasePackagePath\lib\net6.0-windows10.0.17763.0" `
                -dest "$BaseComponentPath\lib\net6.0-windows10.0.17763.0"
        }
    }
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "PackNuget"))
    {
        # Remove ProjectCapability for the one in the transport package
        $propsFilePath = (Join-Path $BasePath 'build\Microsoft.WindowsAppSDK.Foundation.props')
        [xml]$wasFoundationProps = Get-Content -Encoding UTF8 -Path $propsFilePath
        foreach ($projectCapability in $wasFoundationProps.Project.ItemGroup.ProjectCapability)
        {
            if ($projectCapability.Id -eq "VersionSpecific")
            {
                $wasFoundationProps.Project.RemoveChild($projectCapability.ParentNode)
                break
            }
        }
        # Note: For some reason, the Save method does not work by default
        # with the path relative to the current working directory.
        # So we prepend the current working directory to the path.
        $propsFileSavePath = Join-Path $PWD $propsFilePath
        $wasFoundationProps.Save($propsFileSavePath)

        # Fix up ProjectCapability versions
        $FoundationBuildPaths = @(
            'build',
            'buildTransitive'
        )

        foreach ($BuildPath in $FoundationBuildPaths)
        {
            # Keep ProjectCapability and update the version for the one in the component package
            $propsFilePath = (Join-Path $ComponentBasePath "$BuildPath\Microsoft.WindowsAppSDK.Foundation.props")
            [xml]$wasFoundationProps = Get-Content -Encoding UTF8 -Path $propsFilePath
            foreach ($projectCapability in $wasFoundationProps.Project.ItemGroup.ProjectCapability)
            {
                if ($projectCapability.Id -eq "VersionSpecific")
                {
                    $projectCapability.Include = "Microsoft.WindowsAppSDK.Foundation.$ComponentPackageVersion"
                }
            }
            $wasFoundationProps.Save($propsFileSavePath)
        }

        $nuspecPath = "BuildOutput\Microsoft.WindowsAppSDK.Foundation.TransportPackage.nuspec"
        Copy-Item -Path ".\build\NuSpecs\Microsoft.WindowsAppSDK.Foundation.TransportPackage.nuspec" -Destination $nuspecPath

        # Add the version to the nuspec.
        [xml]$publicNuspec = Get-Content -Path $nuspecPath
        $publicNuspec.package.metadata.version = $PackageVersion
        Set-Content -Value $publicNuspec.OuterXml $nuspecPath

        # Make the foundation transport package.
        nuget pack $nuspecPath -BasePath $BasePath -OutputDirectory $OutputDirectory

        if ($lastexitcode -ne 0)
        {
            write-host "ERROR: nuget.exe pack $nuspecPath FAILED."
            exit 1
        }

        $nuspecPath = "BuildOutput\Microsoft.WindowsAppSDK.Foundation.nuspec"
        Copy-Item -Path ".\build\NuSpecs\Microsoft.WindowsAppSDK.Foundation.nuspec" -Destination $nuspecPath

        # Add the version to the nuspec.
        [xml]$publicNuspec = Get-Content -Path $nuspecPath
        $publicNuspec.package.metadata.version = $ComponentPackageVersion

        # Update dependency versions in the nuspec
        foreach ($dependency in $publicNuspec.package.metadata.dependencies.dependency)
        {
            $buildDependency = $versionDetailsPath.Dependencies.ProductDependencies.Dependency | Where-Object { $_.Name -eq $dependency.Id }
            if (-not($buildDependency))
            {
                write-host "ERROR: NuGet package dependency $($dependency.Id) not found."
                exit 1
            }

            $_dependencyMinVersion = $buildDependency.Version
            $_numericVersion = $_dependencyMinVersion -replace '[-+].*$', ''  # Remove suffix
            $_parsedVersion = [System.Version]$_numericVersion
            $_dependencyMaxVersion = "$($_parsedVersion.Major + 1).0.0"
            $dependency.version = "[${_dependencyMinVersion}, ${_dependencyMaxVersion})"
        }

        Set-Content -Value $publicNuspec.OuterXml $nuspecPath

        # Make the foundation transport package.
        nuget pack $nuspecPath -BasePath $ComponentBasePath -OutputDirectory $OutputDirectory

        if ($lastexitcode -ne 0)
        {
            write-host "ERROR: nuget.exe pack $nuspecPath FAILED."
            exit 1
        }
    }
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "PackBaseNuget"))
    {
        $nuspecPath = "BuildOutput\Microsoft.WindowsAppSDK.Base.TransportPackage.nuspec"
        Copy-Item -Path ".\base\build\NuSpecs\Microsoft.WindowsAppSDK.Base.TransportPackage.nuspec" -Destination $nuspecPath

        # Add the version to the nuspec.
        [xml]$publicNuspec = Get-Content -Path $nuspecPath
        $publicNuspec.package.metadata.version = $PackageVersion
        Set-Content -Value $publicNuspec.OuterXml $nuspecPath

        # Make the Base transport package.
        nuget pack $nuspecPath -BasePath $BasePackagePath -OutputDirectory $OutputDirectory

        if ($lastexitcode -ne 0)
        {
            write-host "ERROR: nuget.exe pack $nuspecPath FAILED."
            exit 1
        }

        $nuspecPath = "BuildOutput\Microsoft.WindowsAppSDK.Base.nuspec"
        Copy-Item -Path ".\base\build\NuSpecs\Microsoft.WindowsAppSDK.Base.nuspec" -Destination $nuspecPath

        # Add the version to the nuspec.
        [xml]$publicNuspec = Get-Content -Path $nuspecPath
        $publicNuspec.package.metadata.version = $ComponentPackageVersion
        Set-Content -Value $publicNuspec.OuterXml $nuspecPath

        # Make the Base component package.
        nuget pack $nuspecPath -BasePath $BaseComponentPath -OutputDirectory $OutputDirectory

        if ($lastexitcode -ne 0)
        {
            write-host "ERROR: nuget.exe pack $nuspecPath FAILED."
            exit 1
        }
    }
    $files = Get-ChildItem $OutputDirectory -File -Filter "*.nupkg"
    foreach ($file in $files)
    {
        Write-Host $file.FullName
    }
}
Catch
{
    $formatstring = "`n{0}`n`n{1}`n`n"
    $fields = $_, $_.ScriptStackTrace

    Write-Host ($formatstring -f $fields) -ForegroundColor RED
    exit 1
}
