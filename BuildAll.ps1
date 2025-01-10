<#
This script is to build the Foundation transport package that will be used to generate the windows app sdk package.
This script is called from BuildAll.ps1 from the aggregator repo and should not be called directly.

PackageVersion: NuGet Package Version that will be used in the packing of Foundation Transport Package
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
    [string]$PackageVersion = "1.1.1.1",
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

# Make sure nuget directory exists.
if(-not (test-path ".nuget"))
{
    new-item -path ".nuget" -itemtype directory
}

# Make sure nuget is on the system
if(-not (test-path ".nuget\nuget.exe"))
{
    Invoke-WebRequest https://dist.nuget.org/win-x86-commandline/latest/nuget.exe -OutFile .nuget\nuget.exe
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
    & .\.nuget\nuget.exe restore $Target -configfile NuGet.config
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
        NugetRestore "Microsoft.WindowsAppRuntime.Bootstrap.Net" "dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj"

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
                                /p:Configuration=$configurationToRun,Platform=$platformToRun `
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
            foreach($configurationToRun in $configuration.Split(","))
            {
                foreach($platformToRun in $platform.Split(","))
                {
                    write-host "Building MrtCore.sln for configuration $configurationToRun and platform:$platformToRun"
                    & $msBuildPath /restore "$MRTSourcesDirectory\mrt\MrtCore.sln" `
                                    /p:Configuration=$configurationToRun,Platform=$platformToRun `
                                    /p:PGOBuildMode=$PGOBuildMode `
                                    /binaryLogger:"BuildOutput/binlogs/MrtCore.$platformToRun.$configurationToRun.binlog"

                    if ($lastexitcode -ne 0)
                    {
                        write-host "ERROR: msbuild.exe '$MRTSourcesDirectory\mrt\MrtCore.sln' FAILED."
                        exit 1
                    }
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
        & $msBuildPath /restore "dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj" /p:Configuration=$configurationForMrtAndAnyCPU,Platform=AnyCPU
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

        if(-not (test-path "$BasePath\build\native"))
        {
            new-item -path "$BasePath\build\native" -itemtype "directory"
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
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.targets" -Destination "$BasePath\build\native\Microsoft.WindowsAppSDK.Foundation.targets"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.props" -Destination "$BasePath\build\native\Microsoft.WindowsAppSDK.Foundation.props"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.C.props" -Destination "$BasePath\build\native"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.WinRt.props" -Destination "$BasePath\build\native"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.AutoInitializer.targets" -Destination "$BasePath\build\native"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.Bootstrap.targets" -Destination "$BasePath\build\native"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.CompatibilitySetter.targets" -Destination "$BasePath\build\native"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.DeploymentManager.targets" -Destination "$BasePath\build\native"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.UndockedRegFreeWinRT.targets" -Destination "$BasePath\build\native"

        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.props" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.AutoInitializer.CS.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.AutoInitializerCommon.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Bootstrap.CS.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.BootstrapCommon.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.CompatibilitySetter.CS.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.DeploymentManager.CS.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.DeploymentManagerCommon.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.UndockedRegFreeWinRT.CS.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.UndockedRegFreeWinRTCommon.targets" -Destination "$BasePath\build"

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

        # copy MRT IDL over.
        Copy-Item -path "$MRTSourcesDirectory\mrt\Microsoft.Windows.ApplicationModel.Resources\src\Microsoft.Windows.ApplicationModel.Resources.idl" -destination "$BasePath\include" -force

        # Copy MRT metadata files.
        Copy-Item -Path "$MRTSourcesDirectory\packaging\MrtCore.props" -Destination "$BasePath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\MrtCore.PriGen.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\MrtCore.References.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\MrtCore.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\native\MrtCore.C.props" -Destination "$BasePath\build\native"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\native\MrtCore.props" -Destination "$BasePath\build\native"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\native\MrtCore.targets" -Destination "$BasePath\build\native"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\ProjectItemsSchema.xaml" -Destination "$BasePath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\README.md" -Destination "$BasePath\build"
        Copy-Item -Path "$MRTSourcesDirectory\mrt\core\src\MRM.h" -Destination "$BasePath\include"
        Copy-Item -Path "$MRTSourcesDirectory\mrt\Microsoft.Windows.ApplicationModel.Resources\src\Microsoft.Windows.ApplicationModel.Resources.idl" -Destination "$BasePath\include"

        # If AnyCPU generates another dll it needs to be added here.
        Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\anycpu\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.dll"  -destination "$BasePath\lib\net6.0-windows10.0.17763.0"

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
    }
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "PackNuget"))
    {
        $nuspecPath = "BuildOutput\Microsoft.WindowsAppSDK.Foundation.nuspec"
        Copy-Item -Path ".\build\NuSpecs\Microsoft.WindowsAppSDK.Foundation.nuspec" -Destination $nuspecPath

        # Add the version to the nuspec.
        [xml]$publicNuspec = Get-Content -Path $nuspecPath
        $publicNuspec.package.metadata.version = $PackageVersion
        Set-Content -Value $publicNuspec.OuterXml $nuspecPath

        # Make the foundation transport package.
        & .\.nuget\nuget.exe pack $nuspecPath -BasePath $BasePath -OutputDirectory $OutputDirectory

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
