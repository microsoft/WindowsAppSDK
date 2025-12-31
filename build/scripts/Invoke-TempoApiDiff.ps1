<#
.SYNOPSIS
    Runs TempoDiff against a Windows App SDK package by comparing the supplied outputs
    (either a single .nupkg or the full dependency graph) with NuGet baselines.
.DESCRIPTION
    The script mirrors the acquisition pattern from the historical Invoke-TempoApiDiff.ps1 but
    is able to accept either a single .nupkg (default) or, when CompareAllDependencies is set,
    restore the entire dependency graph into a flat folder for TempoDiff. The package ID and
    version are read from the embedded .nuspec. TempoDiff is acquired from the internal feed,
    the latest stable and/or experimental versions are downloaded from NuGet.org, and diffs run
    in both directions. Artifacts (logs, JSON summaries, aggregate statistics) are written to the
    requested output directory.
.PARAMETER CurrentPackagePath
    Path to the .nupkg produced by the current build. Required.
.PARAMETER OutputDirectory
    Directory where TempoDiff outputs are written. Defaults to TempoDiffOutput under the current directory.
.PARAMETER WorkingDirectory
    Root directory for temporary files. Defaults to TempoDiffDownloads under the current directory.
.PARAMETER PreserveWorkingDirectory
    When set, leaves the working directory on disk after execution for debugging. Contents are still cleared at the next run.
.PARAMETER CompareToLastStable
    When true (default), compares the current package against the latest stable version available on NuGet.
.PARAMETER CompareToLastExperimental
    When true, also compares against the most recent experimental version available on NuGet (if older than the current build).
.PARAMETER CompareAllDependencies
    When true, restores the entire dependency graph for each package (meta-package comparison) before running TempoDiff.
.PARAMETER WinAppSDKRuntimePath
    Optional path to a Microsoft.WindowsAppSDK.Runtime package to satisfy dependency restores when CompareAllDependencies is enabled.
#>

param(
    [Parameter(Mandatory = $true)]
    [string]$CurrentPackagePath,

    [string]$OutputDirectory = 'TempoDiffOutput',

    [string]$WorkingDirectory = 'TempoDiffDownloads',

    [switch]$PreserveWorkingDirectory,

    [bool]$CompareToLastStable = $true,

    [bool]$CompareToLastExperimental = $false,

    [bool]$CompareAllDependencies = $false,

    [string]$WinAppSDKRuntimePath
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

if (-not (Get-Command nuget -ErrorAction SilentlyContinue)) {
    throw 'nuget.exe must be available on PATH before running this script.'
}

if (-not $CompareToLastStable -and -not $CompareToLastExperimental) {
    throw 'At least one of CompareToLastStable or CompareToLastExperimental must be true.'
}

$script:NuGetFeedUrl = 'https://api.nuget.org/v3/index.json'
$script:InternalFeedUrl = 'https://pkgs.dev.azure.com/microsoft/ProjectReunion/_packaging/Project.Reunion.nuget.internal/nuget/v3/index.json'
$script:TempoPackageId = 'Microsoft.Internal.TempoDiff'

$script:NuGetSupportsDownload = $null
function Test-NuGetSupportsDownload {
    if ($null -ne $script:NuGetSupportsDownload) {
        return $script:NuGetSupportsDownload
    }

    try {
        & nuget help download | Out-Null
        $script:NuGetSupportsDownload = ($LASTEXITCODE -eq 0)
    } catch {
        $script:NuGetSupportsDownload = $false
    }

    return $script:NuGetSupportsDownload
}

function Get-AvailablePackageVersions {
    param(
        [string]$PackageId
    )

    if ([string]::IsNullOrWhiteSpace($PackageId)) {
        throw 'Get-AvailablePackageVersions requires a package ID.'
    }

    $pattern = [System.Text.RegularExpressions.Regex]::Escape($PackageId)
    $set = New-Object System.Collections.Generic.HashSet[string] ([System.StringComparer]::OrdinalIgnoreCase)

    foreach ($includePrerelease in @($false, $true)) {
        $nugetArgs = @('list', $PackageId, '-AllVersions', '-NonInteractive')
        if ($includePrerelease) {
            $nugetArgs += '-Prerelease'
        }
        if (-not [string]::IsNullOrWhiteSpace($script:NuGetFeedUrl)) {
            $nugetArgs += @('-Source', $script:NuGetFeedUrl)
        }

        $output = & nuget @nugetArgs 2>&1
        if ($LASTEXITCODE -ne 0) {
            throw "nuget list failed for $PackageId (exit code $LASTEXITCODE)."
        }

        foreach ($line in $output) {
            if ([string]::IsNullOrWhiteSpace($line)) { continue }
            if ($line -match "${pattern}\s+(.+)$") {
                $versionText = $Matches[1].Trim()
                if (-not [string]::IsNullOrWhiteSpace($versionText)) {
                    [void]$set.Add($versionText)
                }
            }
        }
    }

    return @($set | ForEach-Object { $_ })
}

function Resolve-StableBaselineVersion {
    param(
        [string[]]$AvailableVersions,
        [string]$CurrentVersionText
    )

    if (-not $AvailableVersions -or $AvailableVersions.Count -eq 0) {
        return $null
    }

    $stable = @($AvailableVersions | Where-Object { $_ -and ($_ -notmatch '(?i)experimental') })
    if (-not $stable -or $stable.Count -eq 0) {
        return $null
    }

    $currentComparable = $null
    if (-not [string]::IsNullOrWhiteSpace($CurrentVersionText)) {
        $core = ($CurrentVersionText -split '[-+]')[0]
        try {
            $currentComparable = [version]$core
        } catch {
            $currentComparable = $null
        }
    }

    $parsed = @()
    foreach ($candidate in $stable) {
        $core = ($candidate -split '[-+]')[0]
        try {
            $parsed += [pscustomobject]@{ Text = $candidate; Comparable = [version]$core }
        } catch {
        }
    }

    if ($parsed.Count -eq 0) {
        return $null
    }

    if ($currentComparable) {
        $older = $parsed | Where-Object { $_.Comparable -lt $currentComparable } | Sort-Object Comparable -Descending | Select-Object -First 1
        if ($older) {
            return $older.Text
        }
    }

    $latest = $parsed | Sort-Object Comparable -Descending | Select-Object -First 1
    return $latest.Text
}

function Resolve-ExperimentalBaselineVersion {
    param(
        [string[]]$AvailableVersions,
        [string]$CurrentVersionText
    )

    if (-not $AvailableVersions -or $AvailableVersions.Count -eq 0) {
        return $null
    }

    $experimental = @($AvailableVersions | Where-Object { $_ -and ($_ -match '(?i)experimental') })
    if (-not $experimental -or $experimental.Count -eq 0) {
        return $null
    }

    $currentComparable = $null
    if (-not [string]::IsNullOrWhiteSpace($CurrentVersionText)) {
        $core = ($CurrentVersionText -split '[-+]')[0]
        try {
            $currentComparable = [version]$core
        } catch {
            $currentComparable = $null
        }
    }

    $parsed = @()
    foreach ($candidate in $experimental) {
        $core = ($candidate -split '[-+]')[0]
        try {
            $parsed += [pscustomobject]@{ Text = $candidate; Comparable = [version]$core }
        } catch {
        }
    }

    if ($parsed.Count -eq 0) {
        return $null
    }

    if ($currentComparable) {
        $older = $parsed | Where-Object { $_.Comparable -lt $currentComparable } | Sort-Object Comparable -Descending | Select-Object -First 1
        if ($older) {
            return $older.Text
        }
    }

    $latest = $parsed | Sort-Object Comparable -Descending | Select-Object -First 1
    return $latest.Text
}

function Resolve-BaselineVersionList {
    param(
        [bool]$IncludeStable,
        [bool]$IncludeExperimental,
        [string]$CurrentVersionText,
        [string[]]$AvailableVersions
    )

    $results = New-Object System.Collections.Generic.List[object]

    if ($IncludeStable) {
        $stable = Resolve-StableBaselineVersion -AvailableVersions $AvailableVersions -CurrentVersionText $CurrentVersionText
        if ($stable) {
            $results.Add([pscustomobject]@{ Version = $stable; Description = 'vs latest stable'; Kind = 'Stable' })
        } else {
            throw 'CompareToLastStable was requested, but no stable baseline version could be resolved from the feed.'
        }
    }

    if ($IncludeExperimental) {
        $experimental = Resolve-ExperimentalBaselineVersion -AvailableVersions $AvailableVersions -CurrentVersionText $CurrentVersionText
        if ($experimental) {
            $existing = $results | Where-Object { $_.Version -eq $experimental }
            if (-not $existing) {
                $results.Add([pscustomobject]@{ Version = $experimental; Description = 'vs experimental'; Kind = 'Experimental' })
            }
        } else {
            throw 'CompareToLastExperimental was requested, but no experimental baseline version could be resolved from the feed.'
        }
    }

    return @($results.ToArray())
}

Add-Type -AssemblyName System.IO.Compression.FileSystem

$scriptStart = Get-Date
$workingRoot = $WorkingDirectory
$usingDefaultWorkingRoot = -not $PSBoundParameters.ContainsKey('WorkingDirectory')
$resolvedOutput = $OutputDirectory
$usingDefaultOutput = -not $PSBoundParameters.ContainsKey('OutputDirectory')

function ConvertTo-SafeFileNameSegment {
    param([string]$Text)

    if ([string]::IsNullOrEmpty($Text)) {
        return 'unknown'
    }

    $sanitized = [System.Text.RegularExpressions.Regex]::Replace($Text, '[^A-Za-z0-9._-]', '_')
    if ([string]::IsNullOrWhiteSpace($sanitized)) {
        return 'segment'
    }

    return $sanitized
}

function Join-PathSafe {
    param(
        [Parameter(Mandatory = $true)][string]$Path,
        [Parameter(Mandatory = $true)][string[]]$ChildPath
    )

    $current = $Path
    foreach ($child in $ChildPath) {
        if ([string]::IsNullOrWhiteSpace($child)) { continue }
        $current = [System.IO.Path]::Combine($current, $child)
    }

    return $current
}

function New-CleanDirectory {
    param(
        [Parameter(Mandatory = $true)][string]$Path,
        [switch]$Force
    )

    if (Test-Path -LiteralPath $Path) {
        if ($Force) {
            Remove-Item -LiteralPath $Path -Recurse -Force
        } else {
            return
        }
    }

    [System.IO.Directory]::CreateDirectory($Path) | Out-Null
}

function Restore-PackageWithDependencies {
    param(
        [Parameter(Mandatory = $true)][string]$PackageId,
        [Parameter(Mandatory = $true)][string]$PackageVersion,
        [Parameter(Mandatory = $true)][string]$PackagesRoot,
        [Parameter(Mandatory = $true)][string]$FlatDirectory,
        [string]$LocalFeedDirectory,
        [object[]]$LocalPackageSpecs
    )

    if ([string]::IsNullOrWhiteSpace($PackageId)) {
        throw 'Restore-PackageWithDependencies requires a package ID.'
    }
    if ([string]::IsNullOrWhiteSpace($PackageVersion)) {
        throw 'Restore-PackageWithDependencies requires a package version.'
    }

    New-CleanDirectory -Path $PackagesRoot -Force
    New-CleanDirectory -Path $FlatDirectory -Force

    $sources = New-Object System.Collections.Generic.List[string]

    if ($LocalPackageSpecs -and $LocalPackageSpecs.Count -gt 0) {
        if ([string]::IsNullOrWhiteSpace($LocalFeedDirectory)) {
            $LocalFeedDirectory = Join-Path $PackagesRoot 'LocalFeed'
        }
        New-CleanDirectory -Path $LocalFeedDirectory -Force

        $published = New-Object System.Collections.Generic.HashSet[string] ([System.StringComparer]::OrdinalIgnoreCase)
        foreach ($spec in $LocalPackageSpecs) {
            if (-not $spec) { continue }
            $path = $spec.Path
            $id = $spec.Id
            $version = $spec.Version
            if ([string]::IsNullOrWhiteSpace($path) -or -not (Test-Path -LiteralPath $path)) { continue }
            if ([string]::IsNullOrWhiteSpace($id) -or [string]::IsNullOrWhiteSpace($version)) { continue }

            $key = "$($id.ToLowerInvariant())|$($version.ToLowerInvariant())"
            if ($published.Contains($key)) { continue }
            [void]$published.Add($key)

            $fileName = '{0}.{1}.nupkg' -f $id, $version
            $destination = Join-Path $LocalFeedDirectory $fileName
            Copy-Item -LiteralPath $path -Destination $destination -Force
        }

        if ((Get-ChildItem -Path $LocalFeedDirectory -Filter '*.nupkg' -ErrorAction SilentlyContinue)) {
            $sources.Add($LocalFeedDirectory)
        }
    }

    if (-not [string]::IsNullOrWhiteSpace($script:NuGetFeedUrl)) {
        $sources.Add($script:NuGetFeedUrl)
    }
    if (-not [string]::IsNullOrWhiteSpace($script:InternalFeedUrl)) {
        if (-not ($sources -contains $script:InternalFeedUrl)) {
            $sources.Add($script:InternalFeedUrl)
        }
    }

    $nugetArgs = @('install', $PackageId, '-Version', $PackageVersion, '-DependencyVersion', 'Highest', '-DirectDownload', '-NonInteractive', '-OutputDirectory', $PackagesRoot)
    if ($sources.Count -gt 0) {
        $nugetArgs += @('-Source', ($sources -join ';'))
    }

    & nuget @nugetArgs | Out-Null
    if ($LASTEXITCODE -ne 0) {
        throw "nuget install failed for $PackageId $PackageVersion (exit code $LASTEXITCODE)."
    }

    $packages = Get-ChildItem -Path $PackagesRoot -Filter '*.nupkg' -Recurse -ErrorAction SilentlyContinue
    if (-not $packages -or $packages.Count -eq 0) {
        throw "No packages were restored for $PackageId $PackageVersion under '$PackagesRoot'."
    }

    foreach ($pkg in $packages) {
        $destination = Join-Path $FlatDirectory $pkg.Name
        Copy-Item -LiteralPath $pkg.FullName -Destination $destination -Force
    }

    return [pscustomobject]@{
        Root = $PackagesRoot
        Flat = $FlatDirectory
        LocalFeed = $LocalFeedDirectory
    }
}

function Read-TempoResultStats {
    param([string]$TextPath)

    $defaultStats = [pscustomobject]@{
        Total            = 0
        Experimental     = 0
        NonExperimental  = 0
    }

    if ([string]::IsNullOrWhiteSpace($TextPath) -or -not (Test-Path -LiteralPath $TextPath)) {
        return $defaultStats
    }

    $patternFull = [regex]'Found\s+(?<total>\d+)\s+result items\..*Experimental:\s+(?<exp>\d+),\s+Non-experimental:\s+(?<non>\d+)'
    $patternTotalOnly = [regex]'Found\s+(?<total>\d+)\s+result items'

    try {
        $lines = @(Get-Content -LiteralPath $TextPath)
    } catch {
        return $defaultStats
    }

    if (-not $lines) {
        return $defaultStats
    }

    $totalOnlyValue = $null

    for ($i = $lines.Count - 1; $i -ge 0; $i--) {
        $line = $lines[$i]
        if ($patternFull.IsMatch($line)) {
            $match = $patternFull.Match($line)
            return [pscustomobject]@{
                Total           = [int]$match.Groups['total'].Value
                Experimental    = [int]$match.Groups['exp'].Value
                NonExperimental = [int]$match.Groups['non'].Value
            }
        }

        if ($null -eq $totalOnlyValue -and $patternTotalOnly.IsMatch($line)) {
            $totalOnlyValue = [int]$patternTotalOnly.Match($line).Groups['total'].Value
        }
    }

    if ($null -ne $totalOnlyValue) {
        return [pscustomobject]@{
            Total           = $totalOnlyValue
            Experimental    = 0
            NonExperimental = 0
        }
    }

    return $defaultStats
}

function Acquire-TempoDiff {
    param(
        [string]$DestinationRoot
    )

    if ([string]::IsNullOrWhiteSpace($DestinationRoot)) {
        throw 'Acquire-TempoDiff requires a destination root.'
    }

    $packageId = $script:TempoPackageId
    $feedUrl = $script:InternalFeedUrl

    New-CleanDirectory -Path $DestinationRoot -Force

    $nugetArgs = @('install', $packageId, '-Prerelease', '-NonInteractive', '-OutputDirectory', $DestinationRoot)
    if (-not [string]::IsNullOrWhiteSpace($feedUrl)) {
        $nugetArgs += @('-Source', $feedUrl)
    }

    & nuget @nugetArgs | Out-Null
    if ($LASTEXITCODE -ne 0) {
        throw "nuget install failed for $packageId (exit code $LASTEXITCODE)."
    }

    $packageFolder = Get-ChildItem -Path $DestinationRoot -Directory -Filter "$packageId*" | Sort-Object LastWriteTime -Descending | Select-Object -First 1
    if (-not $packageFolder) {
        throw "Failed to locate downloaded TempoDiff package under '$DestinationRoot'."
    }

    $binary = Get-ChildItem -Path $packageFolder.FullName -Filter 'TempoDiff.exe' -Recurse -ErrorAction SilentlyContinue | Select-Object -First 1
    $isDll = $false
    if (-not $binary) {
        $binary = Get-ChildItem -Path $packageFolder.FullName -Filter 'TempoDiff.dll' -Recurse -ErrorAction SilentlyContinue | Select-Object -First 1
        $isDll = $true
    }

    if (-not $binary) {
        throw "TempoDiff binary was not found in package '$($packageFolder.FullName)'."
    }

    $version = $packageFolder.Name
    $expectedPrefix = "$packageId."
    if ($packageFolder.Name.StartsWith($expectedPrefix, [System.StringComparison]::OrdinalIgnoreCase)) {
        $version = $packageFolder.Name.Substring($expectedPrefix.Length)
    }

    return [pscustomobject]@{
        Version = $version
        Path    = $binary.FullName
        IsDll   = $isDll
        Root    = $packageFolder.FullName
    }
}

function Invoke-TempoDiff {
    param(
        [string]$TempoBinary,
        [bool]$IsDll,
        [string]$BaselineFlat,
        [string]$CurrentFlat,
        [string]$OutputDirectory,
        [string]$ComparisonLabel
    )

    if (-not (Test-Path -LiteralPath $TempoBinary)) {
        throw "TempoDiff binary was not found at '$TempoBinary'."
    }
    if (-not (Test-Path -LiteralPath $BaselineFlat)) {
        throw "Baseline package directory '$BaselineFlat' does not exist."
    }
    if (-not (Test-Path -LiteralPath $CurrentFlat)) {
        throw "Current package directory '$CurrentFlat' does not exist."
    }

    if (-not (Test-Path -LiteralPath $OutputDirectory)) {
        New-CleanDirectory -Path $OutputDirectory
    }

    $label = if ([string]::IsNullOrWhiteSpace($ComparisonLabel)) { 'TempoDiff' } else { $ComparisonLabel }
    $safeLabel = ConvertTo-SafeFileNameSegment -Text $label

    $additionLogName = '{0}_Addition.log' -f $safeLabel
    $additionTextName = '{0}_Addition.txt' -f $safeLabel
    $deletionLogName = '{0}_Deletion.log' -f $safeLabel
    $deletionTextName = '{0}_Deletion.txt' -f $safeLabel

    $removeTargets = @(
        (Join-PathSafe -Path $OutputDirectory -ChildPath $additionLogName)
        (Join-PathSafe -Path $OutputDirectory -ChildPath $additionTextName)
        (Join-PathSafe -Path $OutputDirectory -ChildPath $deletionLogName)
        (Join-PathSafe -Path $OutputDirectory -ChildPath $deletionTextName)
        (Join-PathSafe -Path $OutputDirectory -ChildPath 'TempoDiff.json')
    )

    foreach ($target in $removeTargets) {
        if (Test-Path -LiteralPath $target) {
            Remove-Item -LiteralPath $target -Force -ErrorAction SilentlyContinue
        }
    }

    $useDotnet = $IsDll -or $TempoBinary.ToLowerInvariant().EndsWith('.dll')

    function Invoke-TempoDiffRun {
        param(
            [string]$Left,
            [string]$Right,
            [string]$LogPath,
            [string]$OutPath,
            [string]$Scenario,
            [bool]$UseDotnet,
            [string]$Executable
        )

        Write-Host "Running TempoDiff ($Scenario)"
        if ($UseDotnet) {
            $processOutput = & dotnet $Executable $Left $Right 2>&1
        } else {
            $processOutput = & $Executable $Left $Right 2>&1
        }
        $exitCode = $LASTEXITCODE

        $outputLines = @()
        if ($processOutput) {
            $outputLines = @($processOutput | ForEach-Object { $_.ToString() })
            $outputLines | ForEach-Object { Write-Host $_ }
        }

        $encoding = [System.Text.Encoding]::UTF8
        $logLines = @("Scenario: $Scenario", "Left: $Left", "Right: $Right", "ExitCode: $exitCode") + $outputLines
        [System.IO.File]::WriteAllLines($LogPath, $logLines, $encoding)
        [System.IO.File]::WriteAllLines($OutPath, $outputLines, $encoding)

        if ($exitCode -ne 0) {
            Write-Host "TempoDiff ($Scenario) completed with exit code $exitCode."
        }

        $jsonPath = $null
        $jsonCandidate = Join-Path (Split-Path $OutPath -Parent) 'TempoDiff.json'
        if (Test-Path -LiteralPath $jsonCandidate) {
            $jsonTarget = [System.IO.Path]::ChangeExtension($OutPath, '.json')
            Copy-Item -LiteralPath $jsonCandidate -Destination $jsonTarget -Force
            Remove-Item -LiteralPath $jsonCandidate -Force
            Write-Host "Structured diff JSON saved to $jsonTarget"
            $jsonPath = $jsonTarget
        }

        return [pscustomobject]@{
            ExitCode = $exitCode
            LogPath = $LogPath
            TextPath = $OutPath
            JsonPath = $jsonPath
        }
    }

    $additionLog = Join-PathSafe -Path $OutputDirectory -ChildPath $additionLogName
    $additionOut = Join-PathSafe -Path $OutputDirectory -ChildPath $additionTextName
    $deletionLog = Join-PathSafe -Path $OutputDirectory -ChildPath $deletionLogName
    $deletionOut = Join-PathSafe -Path $OutputDirectory -ChildPath $deletionTextName

    $additionResult = Invoke-TempoDiffRun -Left $BaselineFlat -Right $CurrentFlat -LogPath $additionLog -OutPath $additionOut -Scenario "baseline→current ($label)" -UseDotnet $useDotnet -Executable $TempoBinary
    $deletionResult = Invoke-TempoDiffRun -Left $CurrentFlat -Right $BaselineFlat -LogPath $deletionLog -OutPath $deletionOut -Scenario "current→baseline ($label)" -UseDotnet $useDotnet -Executable $TempoBinary

    return [pscustomobject]@{
        ComparisonLabel   = $label
        SafeLabel         = $safeLabel
        OutputDirectory   = $OutputDirectory
        AdditionExitCode  = $additionResult.ExitCode
        DeletionExitCode  = $deletionResult.ExitCode
        AdditionLogPath   = $additionResult.LogPath
        AdditionTextPath  = $additionResult.TextPath
        AdditionJsonPath  = $additionResult.JsonPath
        DeletionLogPath   = $deletionResult.LogPath
        DeletionTextPath  = $deletionResult.TextPath
        DeletionJsonPath  = $deletionResult.JsonPath
    }
}

function Write-ArtifactSummary {
    param(
        [string]$OutputDirectory,
        [string[]]$BaselineVersions,
        [string]$CurrentVersion,
        [string]$TempoDiffVersion,
        [datetime]$StartTime,
        [object[]]$ComparisonResults,
        [string]$PackageName,
        [string]$CurrentPackageName
    )

    $encoding = [System.Text.Encoding]::UTF8
    $summaryPath = Join-Path $OutputDirectory 'ApiChanges.txt'
    $markdownPath = Join-Path $OutputDirectory 'ApiChanges.md'

    foreach ($legacyName in @('README.txt', 'README.md')) {
        $legacyPath = Join-Path $OutputDirectory $legacyName
        if (Test-Path -LiteralPath $legacyPath) {
            Remove-Item -LiteralPath $legacyPath -Force -ErrorAction SilentlyContinue
        }
    }

    $endTime = Get-Date
    $duration = $endTime - $StartTime
    $baselineText = if ($BaselineVersions -and $BaselineVersions.Count -gt 0) { $BaselineVersions -join ', ' } else { '(none)' }

    $textLines = New-Object System.Collections.Generic.List[string]
    $textLines.Add('TempoDiff API comparison results')
    $textLines.Add('')
    $textLines.Add("Package under comparison: $PackageName")
    $textLines.Add("Current version: $CurrentVersion ($CurrentPackageName)")
    $textLines.Add("Baseline version(s): $baselineText")
    $textLines.Add("TempoDiff package: $TempoDiffVersion")
    $textLines.Add("Execution start: $StartTime")
    $textLines.Add("Execution end:   $endTime")
    $textLines.Add("Duration:        $($duration.ToString())")
    $textLines.Add('')

    if ($ComparisonResults -and $ComparisonResults.Count -gt 0) {
        $textLines.Add('Comparisons:')
        foreach ($comparison in $ComparisonResults) {
            $textLines.Add("- $($comparison.ComparisonLabel)")
            $textLines.Add("  Baseline version: $($comparison.BaselineVersion)")
            if ($comparison.BaselineDescription) {
                $textLines.Add("  Baseline description: $($comparison.BaselineDescription)")
            }
            if ($comparison.BaselinePackageName) {
                $textLines.Add("  Baseline package: $($comparison.BaselinePackageName)")
            }
            $textLines.Add("  Addition exit code: $($comparison.AdditionExitCode)")
            $textLines.Add("  Deletion exit code: $($comparison.DeletionExitCode)")
        }
    } else {
        $textLines.Add('No comparisons were executed.')
    }

    $textLines.Add('')
    $textLines.Add('Files:')
    $files = Get-ChildItem -Path $OutputDirectory | Sort-Object Name
    if ($files) {
        foreach ($file in $files) {
            if ($file.Name -in @('ApiChanges.txt', 'ApiChanges.md')) { continue }
            $textLines.Add("- $($file.Name)")
        }
    } else {
        $textLines.Add('- (No output files generated.)')
    }

    [System.IO.File]::WriteAllLines($summaryPath, $textLines.ToArray(), $encoding)

    $markdownLines = New-Object System.Collections.Generic.List[string]
    $markdownLines.Add('# Summary')
    $markdownLines.Add('')
    $markdownLines.Add("* **Package under comparison:** $PackageName")
    $markdownLines.Add("* **Current version:** $CurrentVersion ($CurrentPackageName)")
    $markdownLines.Add("* **Baseline version(s):** $baselineText")
    $markdownLines.Add("* **TempoDiff package:** $TempoDiffVersion")
    $markdownLines.Add("* **Execution start:** $StartTime")
    $markdownLines.Add("* **Execution end:** $endTime")
    $markdownLines.Add("* **Duration:** $($duration.ToString())")
    $markdownLines.Add('')

    if ($ComparisonResults -and $ComparisonResults.Count -gt 0) {
        $markdownLines.Add('# Comparisons')
        $markdownLines.Add('')
        foreach ($comparison in $ComparisonResults) {
            $headingText = $comparison.ComparisonLabel
            if ($comparison.BaselineDescription -and -not [string]::IsNullOrWhiteSpace($comparison.BaselineDescription)) {
                $headingText = $comparison.BaselineDescription
            }
            if ($comparison.BaselineVersion -and -not [string]::IsNullOrWhiteSpace($comparison.BaselineVersion)) {
                $headingText = "$headingText - $($comparison.BaselineVersion)"
            }

            $markdownLines.Add("## $headingText")
            $markdownLines.Add('')
            $markdownLines.Add("* **Baseline version:** $($comparison.BaselineVersion)")
            if ($comparison.BaselineDescription) {
                $markdownLines.Add("* **Baseline description:** $($comparison.BaselineDescription)")
            }
            if ($comparison.BaselinePackageName) {
                $markdownLines.Add("* **Baseline package:** $($comparison.BaselinePackageName)")
            }
            $markdownLines.Add("* **Addition exit code:** $($comparison.AdditionExitCode)")
            $markdownLines.Add("* **Deletion exit code:** $($comparison.DeletionExitCode)")
            $markdownLines.Add('')

            $markdownLines.Add('### Addition output')
            $markdownLines.Add('```')
            if ($comparison.AdditionTextPath -and (Test-Path -LiteralPath $comparison.AdditionTextPath)) {
                $markdownLines.Add([System.IO.File]::ReadAllText($comparison.AdditionTextPath))
            } else {
                $markdownLines.Add('(No addition output captured)')
            }
            $markdownLines.Add('```')
            $markdownLines.Add('')

            $markdownLines.Add('### Deletion output')
            $markdownLines.Add('```')
            if ($comparison.DeletionTextPath -and (Test-Path -LiteralPath $comparison.DeletionTextPath)) {
                $markdownLines.Add([System.IO.File]::ReadAllText($comparison.DeletionTextPath))
            } else {
                $markdownLines.Add('(No deletion output captured)')
            }
            $markdownLines.Add('```')
            $markdownLines.Add('')
        }
    } else {
        $markdownLines.Add('No TempoDiff comparisons were executed.')
        $markdownLines.Add('')
    }

    [System.IO.File]::WriteAllLines($markdownPath, $markdownLines.ToArray(), $encoding)

    return [pscustomobject]@{
        TextPath     = $summaryPath
        MarkdownPath = $markdownPath
    }
}

function Get-PackageMetadata {
    param([string]$PackagePath)

    if (-not (Test-Path -LiteralPath $PackagePath)) {
        throw "Package '$PackagePath' was not found."
    }

    $fullPath = (Resolve-Path -LiteralPath $PackagePath).Path

    $archive = [System.IO.Compression.ZipFile]::OpenRead($fullPath)
    try {
        $nuspec = $archive.Entries | Where-Object { $_.FullName -like '*.nuspec' } | Select-Object -First 1
        if ($nuspec) {
            $reader = New-Object System.IO.StreamReader($nuspec.Open(), [System.Text.Encoding]::UTF8)
            try {
                $content = $reader.ReadToEnd()
            } finally {
                $reader.Dispose()
            }

            if ($content) {
                [xml]$xml = $content
                $id = $xml.package.metadata.id
                $version = $xml.package.metadata.version
                if (-not [string]::IsNullOrWhiteSpace($id) -and -not [string]::IsNullOrWhiteSpace($version)) {
                    return [pscustomobject]@{
                        Id       = $id.Trim()
                        Version  = $version.Trim()
                        FullPath = $fullPath
                    }
                }
            }
        }
    } finally {
        $archive.Dispose()
    }

    $fileName = [System.IO.Path]::GetFileNameWithoutExtension($fullPath)
    $match = [System.Text.RegularExpressions.Regex]::Match($fileName, '^(?<id>.+?)\.(?<ver>\d[0-9A-Za-z\.-]*)$')
    if ($match.Success) {
        return [pscustomobject]@{
            Id       = $match.Groups['id'].Value
            Version  = $match.Groups['ver'].Value
            FullPath = $fullPath
        }
    }

    throw "Unable to determine package ID and version from '$fullPath'."
}

function Download-NuGetPackage {
    param(
        [string]$PackageId,
        [string]$Version,
        [string]$Destination
    )

    New-CleanDirectory -Path $Destination -Force

    $useDownload = Test-NuGetSupportsDownload

    if ($useDownload) {
        $nugetArgs = @('download', $PackageId, '-Version', $Version, '-NonInteractive', '-OutputDirectory', $Destination)
            if (-not [string]::IsNullOrWhiteSpace($script:NuGetFeedUrl)) {
                $nugetArgs += @('-Source', $script:NuGetFeedUrl)
        }

        & nuget @nugetArgs | Out-Null
        if ($LASTEXITCODE -ne 0) {
            throw "nuget download failed for $PackageId $Version (exit code $LASTEXITCODE)."
        }
    } else {
        Write-Host 'nuget download command not available; falling back to install.'
        $nugetArgs = @('install', $PackageId, '-Version', $Version, '-NonInteractive', '-OutputDirectory', $Destination, '-DirectDownload')
            if (-not [string]::IsNullOrWhiteSpace($script:NuGetFeedUrl)) {
                $nugetArgs += @('-Source', $script:NuGetFeedUrl)
        }

        & nuget @nugetArgs | Out-Null
        if ($LASTEXITCODE -ne 0) {
            throw "nuget install failed for $PackageId $Version (exit code $LASTEXITCODE)."
        }
    }

    $package = Get-ChildItem -Path $Destination -Recurse -Filter "$PackageId.$Version*.nupkg" -File -ErrorAction SilentlyContinue | Sort-Object FullName | Select-Object -First 1
    if (-not $package) {
        throw "Unable to locate downloaded package $PackageId.$Version under '$Destination'."
    }

    return $package.FullName
}

try {
    $currentMetadata = Get-PackageMetadata -PackagePath $CurrentPackagePath
    $packageId = $currentMetadata.Id
    $currentVersion = $currentMetadata.Version

    if ([string]::IsNullOrWhiteSpace($packageId) -or [string]::IsNullOrWhiteSpace($currentVersion)) {
        throw 'Failed to determine package ID or version from the current package.'
    }

    Write-Host "Current package: $packageId $currentVersion"

    if ([string]::IsNullOrWhiteSpace($resolvedOutput)) {
        $usingDefaultOutput = $true
        $resolvedOutput = 'TempoDiffOutput'
    }

    try {
        $resolvedOutput = [System.IO.Path]::GetFullPath($resolvedOutput)
    } catch {
    }

    if (-not (Test-Path -LiteralPath $resolvedOutput)) {
        New-CleanDirectory -Path $resolvedOutput
    } elseif ($usingDefaultOutput) {
        New-CleanDirectory -Path $resolvedOutput -Force
    }

    if ([string]::IsNullOrWhiteSpace($workingRoot)) {
        $usingDefaultWorkingRoot = $true
        $workingRoot = Join-Path ([System.IO.Path]::GetTempPath()) ("TempoDiffWork_" + [guid]::NewGuid().ToString('N'))
    } else {
        try {
            $workingRoot = [System.IO.Path]::GetFullPath($workingRoot)
        } catch {
        }
    }

    if (-not (Test-Path -LiteralPath $workingRoot)) {
        New-CleanDirectory -Path $workingRoot
    } elseif ($usingDefaultWorkingRoot) {
        New-CleanDirectory -Path $workingRoot -Force
    } else {
        Write-Host "Using existing working directory '$workingRoot'."
    }

    $tempoRoot = Join-Path $workingRoot 'TempoDiff'

    $tempoInfo = Acquire-TempoDiff -DestinationRoot $tempoRoot
    Write-Host "TempoDiff acquired (version $($tempoInfo.Version)) at $($tempoInfo.Path)"

    $availableVersions = @((Get-AvailablePackageVersions -PackageId $packageId))
    if (-not $availableVersions -or $availableVersions.Count -eq 0) {
        throw "No versions of $packageId were enumerated from $script:NuGetFeedUrl."
    }

    $baselineVersions = @((Resolve-BaselineVersionList -IncludeStable $CompareToLastStable -IncludeExperimental $CompareToLastExperimental -CurrentVersionText $currentVersion -AvailableVersions $availableVersions))
    if (-not $baselineVersions -or $baselineVersions.Count -eq 0) {
        throw 'Failed to resolve any baseline versions for comparison.'
    }
    $baselineVersionTexts = @($baselineVersions | ForEach-Object { $_.Version })
    Write-Host "Resolved baseline version(s): $($baselineVersionTexts -join ', ')"

    $runtimePackageSpec = $null
    if ($WinAppSDKRuntimePath) {
        try {
            $runtimeMetadata = Get-PackageMetadata -PackagePath $WinAppSDKRuntimePath
            $runtimePackageSpec = [pscustomobject]@{
                Path    = $runtimeMetadata.FullPath
                Id      = $runtimeMetadata.Id
                Version = $runtimeMetadata.Version
            }
        } catch {
            throw "Failed to read WinAppSDKRuntimePath package metadata: $($_.Exception.Message)"
        }
    }

    $currentFlat = $null
    $currentPackageDisplay = $null
    $currentLocalSpecs = @()
    $currentLocalSpecs += [pscustomobject]@{
        Path    = $currentMetadata.FullPath
        Id      = $currentMetadata.Id
        Version = $currentMetadata.Version
    }
    if ($runtimePackageSpec) {
        $currentLocalSpecs += $runtimePackageSpec
    }

    if ($CompareAllDependencies) {
        $currentPackagesRoot = Join-Path $workingRoot 'CurrentPackages'
        $currentFlat = Join-Path $workingRoot 'CurrentPackagesFlat'
        $currentLocalFeed = Join-Path $workingRoot 'CurrentLocalFeed'
        Restore-PackageWithDependencies -PackageId $packageId -PackageVersion $currentVersion -PackagesRoot $currentPackagesRoot -FlatDirectory $currentFlat -LocalFeedDirectory $currentLocalFeed -LocalPackageSpecs $currentLocalSpecs | Out-Null
        $currentPackageDisplay = "$packageId $currentVersion (dependencies)"
    } else {
        $currentFlat = Join-Path $workingRoot 'Current'
        New-CleanDirectory -Path $currentFlat -Force
        $currentCopy = Join-Path $currentFlat (Split-Path -Leaf $currentMetadata.FullPath)
        Copy-Item -LiteralPath $currentMetadata.FullPath -Destination $currentCopy -Force
        $currentPackageDisplay = Split-Path -Leaf $currentMetadata.FullPath
    }

    $comparisonResults = @()
    for ($index = 0; $index -lt $baselineVersions.Count; $index++) {
        $baselineInfo = $baselineVersions[$index]
        $baselineVersion = $baselineInfo.Version
        $baselineDescription = $baselineInfo.Description
        $sequence = '{0:D2}' -f ($index + 1)
        $safeSegment = ConvertTo-SafeFileNameSegment -Text $baselineVersion
        $baselineFlatDir = $null
        $baselinePackageName = $null

        if ($CompareAllDependencies) {
            $baselinePackagesRoot = Join-Path $workingRoot ([string]::Format('BaselinePackages_{0}_{1}', $sequence, $safeSegment))
            $baselineFlatDir = Join-Path $workingRoot ([string]::Format('BaselinePackagesFlat_{0}_{1}', $sequence, $safeSegment))
            $baselineLocalFeed = $null
            $localSpecs = @()
            if ($runtimePackageSpec) {
                $localSpecs += $runtimePackageSpec
            }
            if ($localSpecs.Count -gt 0) {
                $baselineLocalFeed = Join-Path $workingRoot ([string]::Format('BaselineLocalFeed_{0}_{1}', $sequence, $safeSegment))
            }

            Restore-PackageWithDependencies -PackageId $packageId -PackageVersion $baselineVersion -PackagesRoot $baselinePackagesRoot -FlatDirectory $baselineFlatDir -LocalFeedDirectory $baselineLocalFeed -LocalPackageSpecs $localSpecs | Out-Null
            $baselinePackageName = 'Multiple packages'
        } else {
            $baselineFlatDir = Join-Path $workingRoot ([string]::Format('Baseline_{0}_{1}', $sequence, $safeSegment))
            $baselineDownloadRoot = Join-Path $workingRoot ([string]::Format('BaselineDownload_{0}', $sequence))

            $baselinePackagePath = Download-NuGetPackage -PackageId $packageId -Version $baselineVersion -Destination $baselineDownloadRoot
            New-CleanDirectory -Path $baselineFlatDir -Force
            $baselinePackageName = Split-Path -Leaf $baselinePackagePath
            Copy-Item -LiteralPath $baselinePackagePath -Destination (Join-Path $baselineFlatDir $baselinePackageName) -Force
        }

        $comparisonLabel = "$packageId $currentVersion vs $baselineVersion"
        $comparisonResult = Invoke-TempoDiff -TempoBinary $tempoInfo.Path -IsDll $tempoInfo.IsDll -BaselineFlat $baselineFlatDir -CurrentFlat $currentFlat -OutputDirectory $resolvedOutput -ComparisonLabel $comparisonLabel
        $comparisonResult | Add-Member -NotePropertyName BaselineVersion -NotePropertyValue $baselineVersion -Force
        $comparisonResult | Add-Member -NotePropertyName BaselineDescription -NotePropertyValue $baselineDescription -Force
        if ($baselinePackageName) {
            $comparisonResult | Add-Member -NotePropertyName BaselinePackageName -NotePropertyValue $baselinePackageName -Force
        }
        $comparisonResult | Add-Member -NotePropertyName AdditionStats -NotePropertyValue (Read-TempoResultStats -TextPath $comparisonResult.AdditionTextPath) -Force
        $comparisonResult | Add-Member -NotePropertyName DeletionStats -NotePropertyValue (Read-TempoResultStats -TextPath $comparisonResult.DeletionTextPath) -Force
        $comparisonResults += $comparisonResult
    }

    if (-not $currentPackageDisplay) {
        $currentPackageDisplay = "$packageId $currentVersion"
    }

    $summary = Write-ArtifactSummary -OutputDirectory $resolvedOutput -BaselineVersions $baselineVersionTexts -CurrentVersion $currentVersion -TempoDiffVersion $tempoInfo.Version -StartTime $scriptStart -ComparisonResults $comparisonResults -PackageName $packageId -CurrentPackageName $currentPackageDisplay

    $apiStatsEntries = @()
    foreach ($comparison in $comparisonResults) {
        $additionStats = $comparison.AdditionStats
        $deletionStats = $comparison.DeletionStats
        $apiStatsEntries += [pscustomobject]@{
            BaselineVersion             = $comparison.BaselineVersion
            BaselineDescription         = $comparison.BaselineDescription
            AddedAPITotal               = $additionStats.Total
            AddedAPI_Experimental       = $additionStats.Experimental
            AddedAPI_NonExperimental    = $additionStats.NonExperimental
            RemovedAPITotal             = $deletionStats.Total
            RemovedAPI_Experimental     = $deletionStats.Experimental
            RemovedAPI_NonExperimental  = $deletionStats.NonExperimental
        }
    }

    $apiStatsPath = Join-Path $resolvedOutput 'TempoDiffApiSummary.json'
    $apiStatsJson = $apiStatsEntries | ConvertTo-Json -Depth 3
    [System.IO.File]::WriteAllText($apiStatsPath, $apiStatsJson, [System.Text.Encoding]::UTF8)

    if ($env:TF_BUILD -eq 'True') {
        $baselineListText = $baselineVersionTexts -join ', '
        Write-Host "##vso[task.setvariable variable=ResolvedBaselineApiVersion]$baselineListText"
        Write-Host "##vso[task.setvariable variable=TempoDiffPackageVersion]$($tempoInfo.Version)"
        if ($summary.MarkdownPath -and (Test-Path -LiteralPath $summary.MarkdownPath)) {
            Write-Host "##vso[task.setvariable variable=TempoDiffSummaryMarkdownPath]$($summary.MarkdownPath)"
        }
        if (Test-Path -LiteralPath $apiStatsPath) {
            Write-Host "##vso[task.setvariable variable=TempoDiffApiSummaryPath]$apiStatsPath"
        }
    }

    Write-Host ''
    Write-Host 'TempoDiff execution completed.'
    Write-Host " Baseline version(s): $($baselineVersionTexts -join ', ')"
    Write-Host " Current version:   $currentVersion"
    Write-Host " Package:           $packageId"
    Write-Host " TempoDiff:         v$($tempoInfo.Version)"
    Write-Host " Output folder:     $resolvedOutput"
    Write-Host " Summary:           $($summary.TextPath)"
    if (Test-Path -LiteralPath $apiStatsPath) {
        Write-Host " API stats JSON:    $apiStatsPath"
    }

    $nonZeroComparisons = @($comparisonResults | Where-Object { $_.AdditionExitCode -ne 0 -or $_.DeletionExitCode -ne 0 })
    if ($nonZeroComparisons -and $nonZeroComparisons.Count -gt 0) {
        $labels = $nonZeroComparisons | ForEach-Object { $_.ComparisonLabel }
        Write-Warning "TempoDiff returned non-zero exit codes for: $($labels -join ', '). Review the generated logs for details."
    }

} catch {
    Write-Error $_.Exception.Message
    Write-Error $_.ScriptStackTrace
    exit 1
} finally {
    if ($PreserveWorkingDirectory) {
        if (Test-Path -LiteralPath $workingRoot) {
            Write-Host "Working directory preserved at '$workingRoot'."
        }
    } elseif ($usingDefaultWorkingRoot -and (Test-Path -LiteralPath $workingRoot)) {
        try {
            Remove-Item -LiteralPath $workingRoot -Recurse -Force -ErrorAction SilentlyContinue
        } catch {
        }
    }
}
