param (
  [string]$SourceDir = '',
  $ContentsList = @(),
  $Exclude = @(),
  $Include = @(),
  [string]$TargetDir = ''
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

foreach ($Contents in $ContentsList)
{
    $ContentsPath = (Join-Path $SourceDir $Contents)

    if (Test-Path ($ContentsPath) -PathType Leaf)
    {
        $targetFile = (Join-Path $TargetDir $Contents)
        [void](New-Item -ItemType File -Path $targetFile -Force)
        Copy-Item $ContentsPath -destination $targetFile
        echo ('Copying '+$ContentsPath+' to '+$targetFile)
    }
    else
    {
        # Get-ChildItem only goes down one directory when doing recurse with a wildcard in the path.
        # To compensate, grab all nested directories, then compare to desired paths
        $directories = Get-ChildItem ($SourceDir) -Directory -Recurse | ? {$_.FullName -like ($ContentsPath)} | % {$_.FullName}

        foreach ($directory in $directories)
        {
            $files = Get-ChildItem ($directory) -File -Recurse -Exclude $Exclude -Include $Include
            foreach ($file in $files)
            {
                $targetFile = (Join-Path $TargetDir ($file.FullName.SubString($SourceDir.Length)))
                [void](New-Item -ItemType File -Path $targetFile -Force)
                Copy-Item $file.FullName -destination $targetFile
                echo ('Copying '+$file.FullName+' to '+$targetFile)
            }
        }
    }
}