param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("x86", "x64", "arm64")]
    [string]$Platform,
    
    [Parameter(Mandatory = $true)]
    [string]$SourceDirectory
)

$ErrorActionPreference = "Stop"

Write-Host "Installing VCLibs packages for platform: $Platform" -ForegroundColor Green

# Search pattern for VCLibs packages
$SearchPath = Join-Path $SourceDirectory "*\AppxPackages\*\Dependencies\$Platform\Microsoft.VCLibs.*.$Platform.14.00*.appx"
Write-Host "Searching for: $SearchPath" -ForegroundColor Cyan

# Find all VCLibs packages
$VCLibsPackages = Get-ChildItem -Path $SearchPath -ErrorAction SilentlyContinue

Write-Host "Found $($VCLibsPackages.Count) VCLibs packages" -ForegroundColor Green

# Track installed packages to avoid duplicates
$InstalledPackages = @{}

foreach ($Package in $VCLibsPackages) {
    $PackageName = $Package.Name
    
    # Check if we've already processed this package name
    if ($InstalledPackages.ContainsKey($PackageName)) {
        Write-Host "Skipping duplicate: $PackageName" -ForegroundColor Yellow
        continue
    }
    
    try {
        Write-Host "Installing: $PackageName" -ForegroundColor White
        Add-AppxPackage -Path $Package.FullName -ForceApplicationShutdown
        
        $InstalledPackages[$PackageName] = $Package.FullName
        Write-Host "  -> Success" -ForegroundColor Green
    }
    catch {
        # Handle already installed packages
        if ($_.Exception.Message -like "*already installed*" -or 
            $_.Exception.Message -like "*already exists*" -or
            $_.Exception.HResult -eq -2147024816) {
            Write-Host "  -> Already installed" -ForegroundColor Yellow
            $InstalledPackages[$PackageName] = $Package.FullName
        }
        else {
            Write-Error "Failed to install $PackageName`: $($_.Exception.Message)"
            throw
        }
    }
}

Write-Host "Completed successfully!" -ForegroundColor Green