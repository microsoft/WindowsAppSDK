[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [String]$PackagesRoot,

    [Parameter(Mandatory = $true)]
    [string]$ProjectReunionPackageVersion
)

# We need to know the versions of Microsoft.ProjectReunion.WinUI and Microsoft.ProjectReunion.Foundation that the current version of
# Microsoft.ProjectReunion depends on.
# In the ideal world, this would not be necessary as a project would just reference Microsoft.ProjectReunion and everything would just work.
# However, vcxproj does not support PackageReference and so a Reunion app must reference all three of these packages.

# The Pipeline calls this script, and this script sets the Pipeline variables via the "##vso[task.setvariable]" command.

[xml]$nuspecXml = Get-Content "$PackagesRoot\microsoft.projectreunion\$ProjectReunionPackageVersion\microsoft.projectreunion.nuspec"
$deps = $nuspecXml.package.metadata.dependencies.dependency
foreach($dep in $deps)
{
    $ver = $dep.version
    if($ver.Contains(",") -or $ver.Contains("*"))
    {
        Write-Error "Expected Microsoft.ProjectReunion to depend on specific versions of dependencies and not a range."
        Write-Error "Dependency $($dep.id) has version $ver"
        return
    }
    
    $removeFromVerString = @("[", "]", "(", ")")
    foreach($toRemove in $removeFromVerString)
    {
        $ver = $ver.Replace($toRemove, "")
    }
    if($dep.id -eq "Microsoft.ProjectReunion.WinUI")
    {
        Write-Host "ProjectReunionWinUIPackageVersion = $ver"
        Write-Host "##vso[task.setvariable variable=ProjectReunionWinUIPackageVersion;]$ver"
    }
    if($dep.id -eq "Microsoft.ProjectReunion.Foundation")
    {
        Write-Host "ProjectReunionFoundationPackageVersion = $ver"
        Write-Host "##vso[task.setvariable variable=ProjectReunionFoundationPackageVersion;]$ver"
    }
}