[CmdLetBinding()]
Param(
    [string]$BuildOutputDir,
    [string]$BinaryDir,
    [string]$NugetDir,
    [string]$Platform,
    [string]$Configuration,
    [switch]$PublishAppxFiles=$false
)

$FullBuildOutput = "$($BuildOutputDir)\$($Configuration)\$($Platform)"
$FullBinaryDir = "$($BinaryDir)\$($Configuration)\$($Platform)"

if (!(Test-Path $FullBinaryDir)) { mkdir $FullBinaryDir }


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

PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.dll $FullBinaryDir\Microsoft.ProjectReunion\
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.lib $FullBinaryDir\Microsoft.ProjectReunion\
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\SampleFlatC.h $FullBinaryDir\Microsoft.ProjectReunion\
#PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.pri $FullBinaryDir\Microsoft.ProjectReunion\
#UNDONE - xaml vcxproj re-runs an mdmerge into the sdk node, we are skipping this for now and leaving the winmd in its normal outdir
#PublishFile -IfExists $FullBuildOutput\projectreunion_dll\sdk\Microsoft.ProjectReunion.winmd $FullBinaryDir\Microsoft.ProjectReunion\sdk\
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.winmd $FullBinaryDir\Microsoft.ProjectReunion\

#PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Generic.xaml $FullBinaryDir\Microsoft.ProjectReunion\
#PublishFile -IfExists $FullBuildOutput\Microsoft.ProjectReunion.Design\Microsoft.ProjectReunion.Design.dll $FullBinaryDir\Microsoft.ProjectReunion.Design\
#PublishFile -IfExists $BuildOutputDir\$Configuration\AnyCPU\Microsoft.ProjectReunion.FrameworkPackagePRI\Microsoft.ProjectReunion.pri $FullBinaryDir\Microsoft.ProjectReunion.FrameworkPackagePRI\

#UNDONE - PGO etc. later PR
# pgosweep and vcruntime are required to run pgo instrumented test run. They are placed from the
# cx test app instead of releasetest.dll since these are architecture specific and the ReleaseTest assembly is AnyCPU.
#PublishFile -IfExists $FullBuildOutput\NugetPackageTestAppCX\pgosweep.exe $FullBinaryDir\Test\
#PublishFile -IfExists $FullBuildOutput\NugetPackageTestAppCX\vcruntime140.dll $FullBinaryDir\Test\

PublishFile -IfExists $FullBuildOutput\FrameworkPackage\*.* $FullBinaryDir\FrameworkPackage

if($PublishAppxFiles)
{
    $AppxPackagesDir = "$FullBinaryDir\AppxPackages"

#    PublishFile -IfExists $FullBuildOutput\MUXControlsTestApp.TAEF\AppPackages\MUXControlsTestApp_Test\ $AppxPackagesDir
#    PublishFile -IfExists $FullBuildOutput\IXMPTestApp.TAEF\AppPackages\IXMPTestApp_Test\ $AppxPackagesDir
#    PublishFile -IfExists $FullBuildOutput\MUXControlsTestAppWPFPackage\AppPackages\MUXControlsTestAppWPFPackage_Test\ $AppxPackagesDir

#    PublishFile -IfExists $FullBuildOutput\NugetPackageTestApp\AppPackages\NugetPackageTestApp_Test\ $AppxPackagesDir
#    PublishFile -IfExists $FullBuildOutput\NugetPackageTestAppCX\AppPackages\NugetPackageTestAppCX_Test\ $AppxPackagesDir
#    PublishFile -IfExists $FullBuildOutput\AppThatUsesMUXIndirectly\AppPackages\AppThatUsesMUXIndirectly_Test\ $AppxPackagesDir
}

# Publish pdbs:
$symbolsOutputDir = "$($FullBinaryDir)\Symbols\"
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.pdb $symbolsOutputDir

PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.dll $NugetDir\runtimes\win10-$Platform\native\
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Symbols\Microsoft.ProjectReunion.pdb $NugetDir\runtimes\win10-$Platform\native\
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.lib $NugetDir\lib\win10-$Platform\
PublishFile -IfExists $FullBuildOutput\projectreunion_dll\Microsoft.ProjectReunion.winmd $NugetDir\lib\uap10.0\ 