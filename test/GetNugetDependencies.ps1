param(
    [Parameter(Mandatory = $true)]
    [string]$PackageName,
    
    [string]$Source = "https://microsoft.pkgs.visualstudio.com/ProjectReunion/_packaging/Project.Reunion.nuget.internal/nuget/v3/index.json",
    [string]$TempFolder = (Join-Path $env:TEMP "NuGetDeps"),
    [string]$OutputVariableName = "dependencyList"
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

# Clean start
if (Test-Path $TempFolder) {
    Remove-Item $TempFolder -Recurse -Force -ErrorAction SilentlyContinue
}
New-Item -Path $TempFolder -ItemType Directory -Force | Out-Null

$allDependencies = @{}  # Use hashtable to track unique dependencies
$processed = @{}        # Track processed packages

Write-Host "=== NuGet Dependency Discovery ===" -ForegroundColor Green
Write-Host "Source: $Source" -ForegroundColor Yellow
Write-Host "Temp Folder: $TempFolder" -ForegroundColor Yellow

function Extract-DependenciesFromPackage {
    param(
        [string]$PackageName
    )
    
    Write-Host "`nProcessing: $PackageName" -ForegroundColor Cyan
    
    # Build download arguments with unique output directory to avoid conflicts
    $packageTempDir = Join-Path $TempFolder "pkg_$PackageName"
    $downloadArgs = @("install", $PackageName, "-Source", $Source, "-OutputDirectory", $packageTempDir, "-ExcludeVersion", "-NonInteractive", "-DependencyVersion", "Ignore", "-PreRelease")

    try {
        $result = & nuget.exe @downloadArgs 2>&1
        if ($LASTEXITCODE -ne 0) {
            Write-Warning "  Failed to download $PackageName"
            Write-Host "  Error details: $result" -ForegroundColor Red
            return @()
        }
        
        # Find and extract nupkg
        $packagePath = Join-Path $packageTempDir $PackageName
        $nupkgFile = Get-ChildItem -Path $packagePath -Filter "*.nupkg" | Select-Object -First 1
        
        if (-not $nupkgFile) {
            Write-Warning "  No nupkg found for $PackageName"
            return @()
        }
        
        # Extract nupkg to find nuspec
        $extractPath = Join-Path $TempFolder "extract_$PackageName"
        if (Test-Path $extractPath) {
            Remove-Item $extractPath -Recurse -Force -ErrorAction SilentlyContinue
        }
        New-Item -Path $extractPath -ItemType Directory -Force | Out-Null
        
        Add-Type -AssemblyName System.IO.Compression.FileSystem
        [System.IO.Compression.ZipFile]::ExtractToDirectory($nupkgFile.FullName, $extractPath)
        
        # Find and parse nuspec
        $nuspecFile = Get-ChildItem -Path $extractPath -Filter "*.nuspec" | Select-Object -First 1
        if (-not $nuspecFile) {
            Write-Host "  No dependencies found (no nuspec)" -ForegroundColor Gray
            return @()
        }
        
        [xml]$nuspec = Get-Content $nuspecFile.FullName -Encoding UTF8
        
        # Extract dependencies
        $dependencies = @()
        $ns = $nuspec.DocumentElement.NamespaceURI
        
        if ($ns) {
            $nsManager = New-Object System.Xml.XmlNamespaceManager($nuspec.NameTable)
            $nsManager.AddNamespace("n", $ns)
            $depNodes = $nuspec.SelectNodes("//n:dependency", $nsManager)
        } else {
            $depNodes = $nuspec.SelectNodes("//dependency")
        }
        
        foreach ($dep in $depNodes) {
            $depId = $dep.GetAttribute("id")
            if ($depId -and $depId -ne $PackageName) {
                $dependencies += $depId
            }
        }
        
        if ($dependencies.Count -gt 0) {
            Write-Host "  Dependencies: $($dependencies -join ', ')" -ForegroundColor Gray
        } else {
            Write-Host "  No dependencies found" -ForegroundColor Gray
        }
        
        return $dependencies
    }
    catch {
        throw "Error processing $PackageName`: $($_.Exception.Message)"
    }
}

function Process-PackageRecursively {
    param(
        [string]$PackageName,
        [int]$Depth = 0
    )
    
    # Avoid infinite recursion
    if ($Depth -gt 10) {
        Write-Warning "Maximum depth reached for $PackageName"
        return
    }
    
    # Skip if already processed
    if ($processed.ContainsKey($PackageName)) {
        return
    }
    
    $processed[$PackageName] = $true
    
    # Get dependencies for this package
    $dependencies = Extract-DependenciesFromPackage -PackageName $PackageName

    # Add dependencies to global list and process recursively
    foreach ($dep in $dependencies) {
        if (-not $allDependencies.ContainsKey($dep)) {
            $allDependencies[$dep] = $true
        }
        
        Process-PackageRecursively -PackageName $dep -Depth ($Depth + 1)
    }
}

# Start processing
Process-PackageRecursively -PackageName $PackageName

# Display results
Write-Host "`n=== RESULTS ===" -ForegroundColor Green
Write-Host "Total dependencies found: $($allDependencies.Count)" -ForegroundColor Yellow

if ($allDependencies.Count -gt 0) {
    Write-Host "`nAll Dependencies:" -ForegroundColor Cyan
    $allDependencies.Keys | Sort-Object | ForEach-Object {
        Write-Host "  $_" -ForegroundColor White
    }
    
    Write-Host "`nDependency Names (semicolon-separated string):" -ForegroundColor Cyan
    $dependenciesString = $allDependencies.Keys -join ';'
    Write-Host "##vso[task.setvariable variable=$OutputVariableName;isOutput=true]$dependenciesString"
    Write-Host "##vso[task.setvariable variable=$OutputVariableName;]$dependenciesString"
}