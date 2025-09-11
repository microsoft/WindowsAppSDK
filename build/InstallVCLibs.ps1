param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("x86", "x64", "arm64")]
    [string]$Platform,
    
    # Expecting BuildOutput\Release
    [Parameter(Mandatory = $true)]
    [string]$SourceDirectory
)

$ErrorActionPreference = "Stop"

Write-Host "Installing VCLibs packages for platform: $Platform" -ForegroundColor Green
Write-Host "Source directory: $SourceDirectory" -ForegroundColor Yellow

# Check if the source directory exists
if (-not (Test-Path $SourceDirectory)) {
    Write-Error "Source directory not found: $SourceDirectory"
    exit 1
}

# Search pattern for VCLibs packages
# This pattern should get both VCLibs, VCLibs Desktop and possibly UWP desktop if present
# VCLibs: Microsoft.VCLibs.{platform}.14.00.appx
# VCLibs Desktop: Microsoft.VCLibs.{platform}.14.00.Desktop.appx
$SearchPath = Join-Path $SourceDirectory "$Platform\AppxPackages\*\Dependencies\$Platform\Microsoft.VCLibs.$Platform.14.00*.appx"
$VCLibsPackages = Get-ChildItem -Path $SearchPath -ErrorAction SilentlyContinue

Write-Host "Found: $($VCLibsPackages.Count) VCLibs packages" -ForegroundColor White

# Track installed packages to avoid duplicates
# We want to install each unique package only once
$InstalledPackages = @{}

foreach ($Package in $VCLibsPackages) {
    $PackageName = $Package.Name
    
    if ($InstalledPackages.ContainsKey($PackageName)) {
        continue
    }
    
    try {
        Write-Host "Installing: $PackageName" -ForegroundColor White
        Add-AppxPackage -Path $Package.FullName -ForceApplicationShutdown
        
        $InstalledPackages[$PackageName] = $Package.FullName
        $TotalInstalled++
        Write-Host "  -> Success" -ForegroundColor Green
    }
    catch {
        Write-Error "Failed to install $PackageName`: $($_.Exception.Message)"
    }
}

Write-Host "Completed successfully!" -ForegroundColor Green