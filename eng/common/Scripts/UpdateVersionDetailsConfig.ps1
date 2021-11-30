[CmdLetBinding()]
Param(
    [string]$dependencyName,
    [string]$dependencyVersion
)

$VersionDetailsPath = "..\..\Version.Details.xml"
[xml]$VersionDetails = Get-Content -Encoding utf8 -Path $VersionDetailsPath


$dependency = $buildConfig.Dependencies.ProductDependencies.Dependency | where {$_.name -eq "$dependencyName"}
$dependency.version = $dependencyVersion

$VersionDetails.Save($VersionDetailsPath)
Write-Host "Saved versions back to $VersionDetailsPath"
