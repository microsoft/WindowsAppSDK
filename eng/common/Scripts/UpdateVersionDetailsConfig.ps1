[CmdLetBinding()]
Param(
    [string]$dependencyName,
    [string]$dependencyVersion
)

Write-Host $dependencyName
Write-Host $dependencyVersion

# Get the root of the repo.
$scriptFullPath =  (split-path -parent $MyInvocation.MyCommand.Definition)
$engPath = (split-path -parent (split-path -parent $scriptFullPath))

Function CheckFile($filename)
{
    if(-not (Test-Path $filename))
    {
        write-host "File not found: $filename"
        exit 1
    }
}

$configFilename = "$engPath\Version.Details.xml"
CheckFile $configFilename

# Load the build.config, update the requested version entry, then write it back out
$xmldoc = [System.Xml.XmlDocument](Get-Content $configFilename)
Write-Host $xmldoc

$node = $xmldoc.Dependencies.ProductDependencies.Dependency | ?{$_.Name -eq $dependencyName}
$node.Version = $dependencyVersion
$xmldoc.Save($configFilename)

Write-Host "Updated $configFilename"
