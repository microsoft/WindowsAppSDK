
# Uninstall any installed Project Reunion packages (and any apps that depend on them)
# If there is a Project Reunion in the test payload, install it.

function Uninstall-FrameworkPackageAndAllDependants {
    Param([string]$frameworkPackageNamePattern)

    # Find all apps that depend on the Framework Package
    $allApps = Get-AppxPackage
    $appsToRemove = @()
    foreach($app in $allApps)
    {
        foreach($dep in $app.Dependencies)
        {
            if($dep.Name.Contains($frameworkPackageNamePattern))
            {
                $appsToRemove += $app
            }
        }
    }

    # Remove the apps:
    foreach($app in $appsToRemove)
    {
        Write-Host "Remove: $($app.Name)"
        Remove-AppxPackage $app
    }

    # Remove the Framework Packages:
    foreach($app in (Get-AppxPackage -Name *$frameworkPackageNamePattern*))
    {
        Write-Host "Remove: $($app.Name)"
        Remove-AppxPackage $app
    }
}

# Uninstall any previous version of Reunion
Uninstall-FrameworkPackageAndAllDependants "Microsoft.ProjectReunion"

# Install current version (if present)
$reunionPackages = Get-ChildItem "Microsoft.ProjectReunion.*.msix"
foreach($package in $reunionPackages)
{
    Write-Host "Creating .cer file from '$package'"
    [System.IO.File]::WriteAllBytes("Microsoft.ProjectReunion.cer", (Get-AuthenticodeSignature $package).SignerCertificate.Export([System.Security.Cryptography.X509Certificates.X509ContentType]::Cert))
    Write-Host "Adding Microsoft.ProjectReunion.cer to TrustedPeople"
    certutil -addstore TrustedPeople Microsoft.ProjectReunion.cer
    Write-Host "Installing $package"
    Add-AppxPackage $package 
}