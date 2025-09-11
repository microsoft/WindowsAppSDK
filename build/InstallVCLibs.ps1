param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("x86", "x64", "arm64")]
    [string]$Platform,
    
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
$SearchPath = Join-Path $SourceDirectory "$Platform\AppxPackages\*\Dependencies\$Platform\Microsoft.VCLibs.$Platform.14.00*.appx"
Write-Host "Searching for: $SearchPath" -ForegroundColor Cyan

# Find all VCLibs packages
$VCLibsPackages = Get-ChildItem -Path $SearchPath -ErrorAction SilentlyContinue

if ($VCLibsPackages.Count -eq 0) {
    Write-Warning "No VCLibs packages found for platform $Platform in $SourceDirectory"
    exit 1
}

Write-Host "Found $($VCLibsPackages.Count) VCLibs packages" -ForegroundColor Green

# Track installed packages to avoid duplicates
$InstalledPackages = @{}
$TotalInstalled = 0
$TotalSkipped = 0

foreach ($Package in $VCLibsPackages) {
    $PackageName = $Package.Name
    
    # Check if we've already processed this package name
    if ($InstalledPackages.ContainsKey($PackageName)) {
        Write-Host "Skipping duplicate: $PackageName" -ForegroundColor Yellow
        $TotalSkipped++
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
        # Handle already installed packages
        if ($_.Exception.Message -like "*already installed*" -or 
            $_.Exception.Message -like "*already exists*" -or
            $_.Exception.HResult -eq -2147024816) {
            Write-Host "  -> Already installed" -ForegroundColor Yellow
            $InstalledPackages[$PackageName] = $Package.FullName
            $TotalSkipped++
        }
        else {
            Write-Error "Failed to install $PackageName`: $($_.Exception.Message)"
            throw
        }
    }
}

# Summary
Write-Host ""
Write-Host "=== Summary ===" -ForegroundColor Cyan
Write-Host "Found: $($VCLibsPackages.Count) packages" -ForegroundColor White
Write-Host "Installed: $TotalInstalled packages" -ForegroundColor Green
Write-Host "Skipped: $TotalSkipped packages" -ForegroundColor Yellow
Write-Host "Completed successfully!" -ForegroundColor Green