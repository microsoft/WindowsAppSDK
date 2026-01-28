# Extracts MSIX packages from any .nupkg found in the Source directory to the Dest directory.
# Looks specifically for certain named MSIX packages and renames them for consistently finding them as installer inputs.

param
(
    [String]$Source,
    [String]$Dest
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

function Remove-ItemIfExists ($Item)
{
    if (Test-Path $Item)
    {
        Write-Host("Removing: " + $Item)
        Remove-Item $Item -Recurse -Force
    }
}

# Temp locations required
$tempExtractDirectory = 'temparchiveextract'
$tempArchive = 'temparchive.zip'
function Remove-TempArtifacts()
{
    Remove-ItemIfExists($tempExtractDirectory)
    Remove-ItemIfExists($tempArchive)
}

# Create Destination if not already existing.
if (!(Test-Path $Dest -PathType Container))
{
    New-Item -Path $Dest -ItemType Directory | Out-Null
}

function Extract-MSIXFromNuget ($NugetPath)
{
    Write-Host "Extracting packages from $NugetPath"
    Remove-TempArtifacts

    # Expand-Archive only works on files with a .zip extension, regardless of whether it is a zip archive.
    Copy-Item -Path $NugetPath -Destination $tempArchive
    Expand-Archive -Path $tempArchive -DestinationPath $tempExtractDirectory -Force

    # Process the archive and extract out and rename relevant files.
    foreach ($filename in Get-ChildItem -Name $tempExtractDirectory -Recurse)
    {
        Write-Host $filename
        # For each item, see if we want to extract this item to a different filename.
        $DestFilename = $false

        # Basic MSIX filename pattern:
        #
        #      NamePrefix.Release[-VersionTag].msix
        #
        # where
        #  * NamePrefix = Microsoft.WindowsAppRuntime[.subname] (e.g. Microsoft.WindowsAppRuntime or Microsoft.WindowsAppRuntime.Main)
        #  * Release    = Major.Minor release (e.g. 1.0)
        #  * VersionTag = Channel# (e.g. Experimental1 or Preview2)
        #  * .msix      = MSIX packages are always named *.msix

        # Find the base Frameworks
        if ($filename -match '^.*(x86|x64|arm64)\\Microsoft\.WindowsAppRuntime[-.](\d+\.\d+)(-[a-z]+[0-9]*)?(\.appx|\.msix)$')
        {
            $DestFilename = 'framework_' + $Matches[1] + '.msix'
        }

        # Find Main
        if ($filename -match '^.*(x86|x64|arm64)\\Microsoft\.WindowsAppRuntime\.Main([-.](\d+\.\d+))?(-[a-z]+[0-9]*)?(\.appx|\.msix)$')
        {
            $DestFilename = 'main_' + $Matches[1] + '.msix'
        }

        # Find Singleton
        if ($filename -match '^.*(x86|x64|arm64)\\Microsoft\.WindowsAppRuntime\.Singleton([-.](\d+\.\d+))(-[a-z]+[0-9]*)?(\.appx|\.msix)$')
        {
            $DestFilename = 'singleton_' + $Matches[1] + '.msix'
        }

        # Find DDLM
        if ($filename -match '^.*(x86|x64|arm64)\\Microsoft\.WindowsAppRuntime\.DDLM([-.](\d+\.\d+))?(-[a-z]+[0-9]*)?(\.appx|\.msix)$')
        {
            $DestFilename = 'ddlm_' + $Matches[1] + '.msix'
        }

        # Find ML Framework (x64 and arm64 only - no x86 ML package)
        if ($filename -match '^.*(x64|arm64)\\Microsoft\.WindowsAppRuntime\.ML([-.](\d+\.\d+))(-[a-z]+[0-9]*)?(\.appx|\.msix)$')
        {
            $DestFilename = 'ml_framework_' + $Matches[1] + '.msix'
        }

        # If this item has a new destination name then do the extract and rename.
        if ($DestFilename)
        {
            $Destination = Join-Path $Dest -ChildPath $DestFilename
            $SourceFile = Join-Path $tempExtractDirectory -ChildPath $filename
            Copy-Item -Path $SourceFile -Destination $Destination -Force
            Write-Host "Extracted file to:" $Destination
        }
    }
}

foreach($item in Get-ChildItem $Source -Recurse | Select FullName)
{
    if ($item.FullName -match '.*(\.nupkg)$')
    {
        Extract-MSIXFromNuget ($item.FullName)
    }
}

Remove-TempArtifacts
