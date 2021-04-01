[CmdLetBinding()]
Param(
    [string]$BuildOutputDir,
    [string]$PublishDir,
    [string]$NugetDir,
    [string]$Platform,
    [string]$Configuration,
    [switch]$PublishAppxFiles=$false
)

$FullBuildOutput = "$($BuildOutputDir)\$($Configuration)\$($Platform)"
$FullPublishDir = "$($PublishDir)\$($Configuration)\$($Platform)"

if (!(Test-Path $FullPublishDir)) { mkdir $FullPublishDir }


function PublishFile {
    Param($source, $destinationDir, [switch]$IfExists = $false)

    if ((-not $IfExists) -or (Test-Path $source))
    {
        Write-Host "Copy from '$source' to '$destinationDir'"
        if (-not (Test-Path $destinationDir))
        {
            $ignore = New-Item -ItemType Directory $destinationDir
        }
        Copy-Item -Recurse -Force $source $destinationDir
    }
    else
    {
        Write-Host "Not copying '$source' to $destinationDir because it did not exist"
    }
}

PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.dll $FullPublishDir\Microsoft.ProjectReunion\
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.lib $FullPublishDir\Microsoft.ProjectReunion\
#PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.pri $FullPublishDir\Microsoft.ProjectReunion\
#UNDONE - xaml vcxproj re-runs an mdmerge into the sdk node, we are skipping this for now and leaving the winmd in its normal outdir
#PublishFile -IfExists $FullBuildOutput\projectreunion_dll\sdk\Microsoft.ProjectReunion.winmd $FullPublishDir\Microsoft.ProjectReunion\sdk\
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ApplicationModel.Activation.winmd $FullPublishDir\Microsoft.ProjectReunion\
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ApplicationModel.DynamicDependency.winmd $FullPublishDir\Microsoft.ProjectReunion\
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\MsixDynamicDependency.h $FullPublishDir\Microsoft.ProjectReunion\
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\wil_msixdynamicdependency.h $FullPublishDir\Microsoft.ProjectReunion\
#
PublishFile -IfExists $FullBuildOutput\projectreunion_bootstrapdll\Microsoft.ProjectReunion.Bootstrap.dll $FullPublishDir\Microsoft.ProjectReunion.Bootstrap\
PublishFile -IfExists $FullBuildOutput\projectreunion_bootstrapdll\Microsoft.ProjectReunion.Bootstrap.lib $FullPublishDir\Microsoft.ProjectReunion.Bootstrap\
PublishFile -IfExists $FullBuildOutput\projectreunion_bootstrapdll\MddBootstrap.h $FullPublishDir\Microsoft.ProjectReunion.Bootstrap\

#PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Generic.xaml $FullPublishDir\Microsoft.ProjectReunion\
#PublishFile -IfExists $FullBuildOutput\Microsoft.ProjectReunion.Design\Microsoft.ProjectReunion.Design.dll $FullPublishDir\Microsoft.ProjectReunion.Design\
#PublishFile -IfExists $BuildOutputDir\$Configuration\AnyCPU\Microsoft.ProjectReunion.FrameworkPackagePRI\Microsoft.ProjectReunion.pri $FullPublishDir\Microsoft.ProjectReunion.FrameworkPackagePRI\

#UNDONE - PGO etc. later PR
# pgosweep and vcruntime are required to run pgo instrumented test run. They are placed from the
# cx test app instead of releasetest.dll since these are architecture specific and the ReleaseTest assembly is AnyCPU.
#PublishFile -IfExists $FullBuildOutput\NugetPackageTestAppCX\pgosweep.exe $FullPublishDir\Test\
#PublishFile -IfExists $FullBuildOutput\NugetPackageTestAppCX\vcruntime140.dll $FullPublishDir\Test\

PublishFile -IfExists $FullBuildOutput\FrameworkPackage\*.* $FullPublishDir\FrameworkPackage

if($PublishAppxFiles)
{
    $AppxPackagesDir = "$FullPublishDir\AppxPackages"

#    PublishFile -IfExists $FullBuildOutput\MUXControlsTestApp.TAEF\AppPackages\MUXControlsTestApp_Test\ $AppxPackagesDir
#    PublishFile -IfExists $FullBuildOutput\IXMPTestApp.TAEF\AppPackages\IXMPTestApp_Test\ $AppxPackagesDir
#    PublishFile -IfExists $FullBuildOutput\MUXControlsTestAppWPFPackage\AppPackages\MUXControlsTestAppWPFPackage_Test\ $AppxPackagesDir

#    PublishFile -IfExists $FullBuildOutput\NugetPackageTestApp\AppPackages\NugetPackageTestApp_Test\ $AppxPackagesDir
#    PublishFile -IfExists $FullBuildOutput\NugetPackageTestAppCX\AppPackages\NugetPackageTestAppCX_Test\ $AppxPackagesDir
#    PublishFile -IfExists $FullBuildOutput\AppThatUsesMUXIndirectly\AppPackages\AppThatUsesMUXIndirectly_Test\ $AppxPackagesDir
}

# Publish pdbs:
$symbolsOutputDir = "$($FullPublishDir)\Symbols\"
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.pdb $symbolsOutputDir
PublishFile -IfExists $FullBuildOutput\projectreunion_bootstrapdll\Microsoft.ProjectReunion.Bootstrap.pdb $symbolsOutputDir

# Copy files to Full Nuget package
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.pdb $NugetDir\runtimes\win10-$Platform\native\
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.lib $NugetDir\lib\win10-$Platform
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ApplicationModel.Activation.winmd $NugetDir\lib\uap10.0
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ApplicationModel.DynamicDependency.winmd $NugetDir\lib\uap10.0
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\MsixDynamicDependency.h $NugetDir\inc\uap10.0
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\wil_msixdynamicdependency.h $NugetDir\inc\uap10.0
#
PublishFile -IfExists $FullBuildOutput\projectreunion_bootstrapdll\Microsoft.ProjectReunion.Bootstrap.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile -IfExists $FullBuildOutput\projectreunion_bootstrapdll\Microsoft.ProjectReunion.Bootstrap.pdb $NugetDir\runtimes\win10-$Platform\native\
PublishFile -IfExists $FullBuildOutput\projectreunion_bootstrapdll\Microsoft.ProjectReunion.Bootstrap.lib $NugetDir\lib\win10-$Platform
PublishFile -IfExists $FullBuildOutput\projectreunion_bootstrapdll\MddBootstrap.h $NugetDir\inc\win10-$Platform
