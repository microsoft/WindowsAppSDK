param(
    [switch]$DevMode = $true
)

# Define the manifest files to update
$manifestFiles = @(
    "Extension\Cpp\Dev17\Standalone\source.extension.vsixmanifest",
    "Extension\Cs\Dev17\Standalone\source.extension.vsixmanifest"
)

$backupFile = ".manifest-backup.json"

# DevMode OFF: Restore to previous state
if (-not $DevMode) {
    Write-Host "Setting DevMode OFF - Restoring manifest files to previous state..." -ForegroundColor Green
    
    if (-not (Test-Path $backupFile)) {
        Write-Host "Error: Backup file not found. Cannot restore." -ForegroundColor Red
        Write-Host "Run the script with -DevMode first to create a backup." -ForegroundColor Yellow
        exit 1
    }
    
    # Read backup data
    $backup = Get-Content $backupFile | ConvertFrom-Json
    
    foreach ($manifestFile in $manifestFiles) {
        if (Test-Path $manifestFile) {
            Write-Host "`nRestoring: $manifestFile" -ForegroundColor Cyan
            
            # Find backup entry for this file
            $backupEntry = $backup | Where-Object { $_.File -eq $manifestFile }
            
            if ($null -eq $backupEntry) {
                Write-Host "  Warning: No backup found for this file" -ForegroundColor Yellow
                continue
            }
            
            # Read the manifest file
            [xml]$manifest = Get-Content $manifestFile
            $identity = $manifest.PackageManifest.Metadata.Identity
            
            # Restore version
            $currentVersion = $identity.Version
            $identity.Version = $backupEntry.Version
            Write-Host "  Version: $currentVersion -> $($backupEntry.Version)" -ForegroundColor Yellow
            
            # Restore preview state
            if ($backupEntry.HadPreview) {
                $identity.SetAttribute("Preview", $backupEntry.PreviewValue)
                Write-Host "  Preview: restored to $($backupEntry.PreviewValue)" -ForegroundColor Yellow
            } else {
                if ($null -ne $identity.Preview) {
                    $identity.RemoveAttribute("Preview")
                    Write-Host "  Preview: removed (was not present in backup)" -ForegroundColor Yellow
                }
            }
            
            # Save the manifest file
            $manifest.Save((Resolve-Path $manifestFile).Path)
            Write-Host "  Restored successfully!" -ForegroundColor Green
        } else {
            Write-Host "`nWarning: File not found: $manifestFile" -ForegroundColor Red
        }
    }
    
    Write-Host "`nAll manifest files restored successfully!" -ForegroundColor Green
    Write-Host "DevMode is now OFF" -ForegroundColor Cyan
    exit 0
}

# DevMode ON: Save current state and update to dev version
$Version = Get-Date -Format "yyyy.MM.dd"

Write-Host "Setting DevMode ON" -ForegroundColor Green
Write-Host "Updating manifest versions to: $Version" -ForegroundColor Green
Write-Host "Setting Preview to: true" -ForegroundColor Green

# Create backup of current state
$backupData = @()

foreach ($manifestFile in $manifestFiles) {
    if (Test-Path $manifestFile) {
        [xml]$manifest = Get-Content $manifestFile
        $identity = $manifest.PackageManifest.Metadata.Identity
        
        $backupEntry = @{
            File = $manifestFile
            Version = $identity.Version
            HadPreview = ($null -ne $identity.Preview)
            PreviewValue = if ($null -ne $identity.Preview) { $identity.Preview } else { "" }
        }
        
        $backupData += $backupEntry
    }
}

# Save backup to file
$backupData | ConvertTo-Json | Set-Content $backupFile
Write-Host "Backup saved to: $backupFile" -ForegroundColor Cyan

# Now update the manifest files
foreach ($manifestFile in $manifestFiles) {
    if (Test-Path $manifestFile) {
        Write-Host "`nProcessing: $manifestFile" -ForegroundColor Cyan
        
        # Read the manifest file
        [xml]$manifest = Get-Content $manifestFile
        
        # Update the version in the Identity element
        $identity = $manifest.PackageManifest.Metadata.Identity
        $currentVersion = $identity.Version
        $identity.Version = $Version
        
        Write-Host "  Version: $currentVersion -> $Version" -ForegroundColor Yellow
        
        # Add or update Preview attribute to true
        if ($null -eq $identity.Preview) {
            Write-Host "  Adding Preview attribute: true" -ForegroundColor Yellow
            $identity.SetAttribute("Preview", "true")
        } else {
            $oldPreview = $identity.Preview
            $identity.Preview = "true"
            Write-Host "  Preview: $oldPreview -> true" -ForegroundColor Yellow
        }
        
        # Save the manifest file
        $manifest.Save((Resolve-Path $manifestFile).Path)
        Write-Host "  Updated successfully!" -ForegroundColor Green
    } else {
        Write-Host "`nWarning: File not found: $manifestFile" -ForegroundColor Red
    }
}

Write-Host "`nAll manifest files updated successfully!" -ForegroundColor Green
Write-Host "DevMode is now ON" -ForegroundColor Cyan
Write-Host "To disable DevMode and restore previous values, run: .\SetDevMode.ps1 -DevMode:`$false" -ForegroundColor Cyan
