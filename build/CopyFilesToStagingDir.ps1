[CmdLetBinding()]
Param(
    [string]$BuildOutputDir,
    [string]$PublishDir,
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
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\SampleFlatC.h $FullPublishDir\Microsoft.ProjectReunion\
#PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.pri $FullPublishDir\Microsoft.ProjectReunion\
#UNDONE - xaml vcxproj re-runs an mdmerge into the sdk node, we are skipping this for now and leaving the winmd in its normal outdir
#PublishFile -IfExists $FullBuildOutput\projectreunion_dll\sdk\Microsoft.ProjectReunion.winmd $FullPublishDir\Microsoft.ProjectReunion\sdk\
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.winmd $FullPublishDir\Microsoft.ProjectReunion\

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
PublishFile -IfExists $FullBuildOutput\Microsoft.ProjectReunion\Microsoft.ProjectReunion.pdb $symbolsOutputDir
#PublishFile -IfExists $FullBuildOutput\IXMPTestApp.TAEF\IXMPTestApp.pdb $symbolsOutputDir
#PublishFile -IfExists $FullBuildOutput\MUXTestUtilities\MUXTestUtilities.pdb $symbolsOutputDir
#PublishFile -IfExists $FullBuildOutput\MUXControls.Test\MUXControls.Test.pdb $symbolsOutputDir
#PublishFile -IfExists $FullBuildOutput\MUXControlsTestApp.TAEF\MUXControlsTestApp.pdb $symbolsOutputDir
#PublishFile -IfExists $FullBuildOutput\MUXControlsTestAppForIslands\MUXControlsTestAppForIslands.pdb $symbolsOutputDir
#PublishFile -IfExists $FullBuildOutput\MUXControlsTestAppWPF\MUXControlsTestAppWPF.pdb $symbolsOutputDir
#PublishFile -IfExists $FullBuildOutput\TestAppCX\TestAppCX.pdb $symbolsOutputDir
PublishFile -IfExists $FullBuildOutput\NugetPackageTestApp\NugetPackageTestApp.pdb $symbolsOutputDir
#PublishFile -IfExists $FullBuildOutput\AppThatUsesMUXIndirectly\AppThatUsesMUXIndirectly.pdb $symbolsOutputDir
#PublishFile -IfExists $FullBuildOutput\NugetPackageTestAppCX\NugetPackageTestAppCX.pdb $symbolsOutputDir