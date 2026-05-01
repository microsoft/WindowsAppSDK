# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Produces the AbiWinRT projection headers for a public Windows App SDK
    release and stages them on a fresh orphan release branch.

.DESCRIPTION
    Given the umbrella Microsoft.WindowsAppSDK nuget version (e.g. 2.0.1),
    this script:

    * Discovers the per-component nuget versions from the metapackage's
      .nuspec dependencies.
    * Downloads each component nuget package and the AbiWinRT tool.
    * Runs abi.exe over each component's WinMD to produce projection
      headers, copying any include payload alongside.
    * Re-generates inc/README.md so its component-version list reflects
      this release.
    * Creates an orphan branch named "release/<Version>" containing only
      the inc/ tree (README, this script, and the freshly produced abi/
      headers). The script does NOT push the branch; the operator pushes
      manually after reviewing.

    The orphan-branch model keeps consuming apps' clones small: the
    branch carries only what those apps need (projection headers, the
    README, and this script), with no other repo history.

.PARAMETER Version
    The umbrella Microsoft.WindowsAppSDK nuget version, e.g. "2.0.1".
    Used both to look up the package and to name the resulting orphan
    branch ("release/<Version>").

.PARAMETER WorkingDirectory
    Scratch directory for nuget package downloads and intermediate
    output. Defaults to "$env:TEMP\wasdk_inc_<Version>". Must be
    outside the repository working tree.

.PARAMETER NoCommit
    Generate inc/ contents in the working directory but skip all git
    operations. Useful for local iteration / testing.

.PARAMETER Force
    Allow overwriting an existing local "release/<Version>" branch.

.PARAMETER KeepWorkingDirectory
    Do not delete the scratch directory on completion.

.EXAMPLE
    pwsh ./inc/make_projection.ps1 -Version 2.0.1

.EXAMPLE
    pwsh ./inc/make_projection.ps1 -Version 1.8.251106002 -NoCommit

.NOTES
    Run from a clone of the WindowsAppSDK repository. The script will
    create the orphan branch from the currently checked-out branch
    (which is unaffected by the operation).
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [ValidatePattern('^\d+\.\d+\.\d+([.-].+)?$')]
    [string] $Version,

    [string] $WorkingDirectory,

    [switch] $NoCommit,

    [switch] $Force,

    [switch] $KeepWorkingDirectory,

    [switch] $SkipTest
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

# ----------------------------------------------------------------------
# Component table.
#
# Output-folder names mirror the layout used by the historical release
# branches (interactiveexperiences / foundation / winai / winml /
# runtime). New components default to lowercase short names.
#
# ExtraReferences lists package IDs whose WinMDs should be passed to
# abi.exe via additional -reference arguments (in addition to "sdk").
# ----------------------------------------------------------------------
$script:ComponentMap = [ordered] @{
    # Each entry maps a metapackage dependency ID to:
    #   OutputDir       - subdirectory under inc/abi/ to write into
    #   CrossRefs       - other component package IDs whose WinMDs must
    #                     be passed to abi.exe via -reference for this
    #                     component to resolve cross-namespace types
    #   ExternalRefs    - external (non-WindowsAppSDK) package IDs from
    #                     $script:ExternalReferencePackages whose
    #                     WinMDs must also be referenced
    #   AuxiliaryPackages - additional nuget packages whose winmd / include
    #                     payload should be projected/copied into THIS
    #                     component's OutputDir. Used when projection
    #                     content for a component lives in a separate
    #                     transitive package (e.g. WindowsAppSDK 2.0+
    #                     moved the ML projection into the standalone
    #                     Microsoft.Windows.AI.MachineLearning package).
    #                     Each entry: @{ Id = '<package-id>' [; Version = '<ver>'] }.
    #                     If Version is omitted, latest is installed.
    'Microsoft.WindowsAppSDK.Base'                   = @{ OutputDir = 'base' }
    'Microsoft.WindowsAppSDK.InteractiveExperiences' = @{ OutputDir = 'interactiveexperiences' }
    'Microsoft.WindowsAppSDK.Foundation'             = @{ OutputDir = 'foundation'
                                                          CrossRefs    = @('Microsoft.WindowsAppSDK.InteractiveExperiences')
                                                          ExternalRefs = @('Microsoft.Web.WebView2') }
    'Microsoft.WindowsAppSDK.WinUI'                  = @{ OutputDir = 'winui'
                                                          CrossRefs    = @('Microsoft.WindowsAppSDK.InteractiveExperiences','Microsoft.WindowsAppSDK.Foundation')
                                                          ExternalRefs = @('Microsoft.Web.WebView2') }
    'Microsoft.WindowsAppSDK.DWrite'                 = @{ OutputDir = 'dwrite' }
    'Microsoft.WindowsAppSDK.Widgets'                = @{ OutputDir = 'widgets' }
    'Microsoft.WindowsAppSDK.AI'                     = @{ OutputDir = 'winai' }
    'Microsoft.WindowsAppSDK.ML'                     = @{ OutputDir = 'winml'
                                                          AuxiliaryPackages = @(
                                                              @{ Id = 'Microsoft.Windows.AI.MachineLearning' }
                                                          ) }
    'Microsoft.WindowsAppSDK.Runtime'                = @{ OutputDir = 'runtime' }
}

# External (non-WindowsAppSDK) nuget packages whose WinMDs may be needed
# to resolve cross-namespace types referenced from the SDK winmds.
# Components opt in via the ExternalRefs entry in $ComponentMap above.
# Add new entries here if a future release introduces a new external
# dependency that abi.exe can't resolve.
$script:ExternalReferencePackages = @(
    @{ Id = 'Microsoft.Web.WebView2' }
)

# ----------------------------------------------------------------------
# Helpers
# ----------------------------------------------------------------------

function Write-Step {
    param([string] $Message)
    Write-Host ""
    Write-Host "==> $Message" -ForegroundColor Cyan
}

function Invoke-Native {
    param(
        [Parameter(Mandatory = $true)] [string] $File,
        [Parameter(ValueFromRemainingArguments = $true)] [string[]] $Arguments
    )
    & $File @Arguments
    if ($LASTEXITCODE -ne 0) {
        throw "Command failed (exit $LASTEXITCODE): $File $($Arguments -join ' ')"
    }
}

function Get-RepoRoot {
    $root = (& git rev-parse --show-toplevel) 2>$null
    if ($LASTEXITCODE -ne 0 -or -not $root) {
        throw "Not inside a git repository."
    }
    return (Resolve-Path $root).Path
}

function Test-PathInsideRepo {
    param([string] $Path, [string] $RepoRoot)
    $full = [System.IO.Path]::GetFullPath($Path).TrimEnd('\','/')
    $root = $RepoRoot.TrimEnd('\','/')
    return $full.StartsWith($root, [System.StringComparison]::OrdinalIgnoreCase)
}

function Resolve-Tool {
    param([string] $Name)
    $cmd = Get-Command $Name -ErrorAction SilentlyContinue
    if (-not $cmd) { throw "Required tool '$Name' was not found on PATH." }
    return $cmd.Source
}

function Install-NugetPackage {
    param(
        [string] $Id,
        [string] $PkgVersion,
        [string] $OutputDirectory,
        [string] $NugetExe
    )
    Write-Host "  - $Id $PkgVersion"
    Invoke-Native $NugetExe install $Id `
        -Version $PkgVersion `
        -OutputDirectory $OutputDirectory `
        -PackageSaveMode nuspec `
        -DependencyVersion Ignore `
        -Verbosity quiet | Out-Null
}

function Get-MetapackageDependencies {
    param([string] $PackagesDir, [string] $UmbrellaVersion)

    $nuspec = Join-Path $PackagesDir "Microsoft.WindowsAppSDK.$UmbrellaVersion\Microsoft.WindowsAppSDK.nuspec"
    if (-not (Test-Path $nuspec)) {
        throw "Metapackage nuspec not found at $nuspec"
    }

    [xml] $xml = Get-Content -LiteralPath $nuspec -Raw
    $ns = New-Object System.Xml.XmlNamespaceManager($xml.NameTable)
    $ns.AddNamespace('n', $xml.DocumentElement.NamespaceURI)

    $deps = @()
    foreach ($node in $xml.SelectNodes('//n:dependency', $ns)) {
        $id = $node.GetAttribute('id')
        $ver = $node.GetAttribute('version').Trim('[',']','(',')')
        # version could be a range like "1.8.0, 2.0.0"; for our pinned
        # metapackage these are exact-match brackets so a single value.
        if ($ver -match ',') {
            $ver = ($ver -split ',')[0].Trim()
        }
        $deps += [pscustomobject]@{ Id = $id; Version = $ver }
    }
    return $deps
}

function Find-Winmds {
    param([string] $PackageRoot)
    if (-not (Test-Path $PackageRoot)) { return @() }
    return @(Get-ChildItem -Recurse -LiteralPath (Join-Path $PackageRoot 'metadata') -Filter '*.winmd' -ErrorAction SilentlyContinue)
}

function Find-IncludeRoot {
    param([string] $PackageRoot)
    $inc = Join-Path $PackageRoot 'include'
    if (Test-Path $inc) { return $inc }
    return $null
}

function Find-PackageRoot {
    param([string] $PackagesDir, [string] $Id)
    # nuget installs to "<PackagesDir>\<Id>.<Version>". Find the (single)
    # versioned directory matching the requested package id.
    $candidates = @(Get-ChildItem -Directory -LiteralPath $PackagesDir -ErrorAction SilentlyContinue |
        Where-Object { $_.Name -match "^$([regex]::Escape($Id))\.\d" })
    if ($candidates.Count -eq 0) { return $null }
    if ($candidates.Count -gt 1) {
        # Prefer the highest-named one.
        $candidates = @($candidates | Sort-Object Name -Descending)
    }
    return $candidates[0].FullName
}

function Generate-ProjectionForComponent {
    param(
        [pscustomobject] $Component,
        [string] $PackagesDir,
        [string] $StagingIncDir,
        [string] $AbiExe,
        [hashtable] $WinmdsById,
        [hashtable] $ExternalWinmdsById
    )

    $info = $script:ComponentMap[$Component.Id]
    if (-not $info) {
        Write-Warning "  - $($Component.Id): no entry in ComponentMap; skipping"
        return
    }

    # Build the list of source package roots for this component:
    # the direct metapackage dependency, plus any AuxiliaryPackages
    # declared for it.
    $pkgRoots = @()
    $pkgRoots += [pscustomobject]@{
        Id   = $Component.Id
        Root = (Join-Path $PackagesDir "$($Component.Id).$($Component.Version)")
    }
    if ($info.Contains('AuxiliaryPackages')) {
        foreach ($aux in $info.AuxiliaryPackages) {
            $auxRoot = Find-PackageRoot -PackagesDir $PackagesDir -Id $aux.Id
            if (-not $auxRoot) {
                throw "AuxiliaryPackage '$($aux.Id)' was not installed (required by '$($Component.Id)')."
            }
            $pkgRoots += [pscustomobject]@{ Id = $aux.Id; Root = $auxRoot }
        }
    }

    $allWinmds = @()
    $includeRoots = @()
    foreach ($pr in $pkgRoots) {
        if (-not (Test-Path $pr.Root)) {
            throw "Package directory missing: $($pr.Root)"
        }
        $allWinmds += @(Find-Winmds -PackageRoot $pr.Root)
        $inc = Find-IncludeRoot -PackageRoot $pr.Root
        if ($inc) { $includeRoots += [pscustomobject]@{ Id = $pr.Id; Path = $inc } }
    }

    if ($allWinmds.Count -eq 0 -and $includeRoots.Count -eq 0) {
        Write-Host "  - $($Component.Id): no winmd or include payload; skipping"
        return
    }

    $outDir = Join-Path $StagingIncDir "abi\$($info.OutputDir)"
    New-Item -ItemType Directory -Force -Path $outDir | Out-Null

    if ($allWinmds.Count -gt 0) {
        $abiArgs = @(
            '-output', $outDir
            '-lowercase-include-guard'
            '-ns-prefix', 'always'
            '-input'
        )
        $abiArgs += $allWinmds.FullName
        $abiArgs += @('-reference', 'sdk')

        if ($info.Contains('CrossRefs')) {
            foreach ($refId in $info.CrossRefs) {
                if (-not $WinmdsById.Contains($refId)) {
                    throw "CrossRefs winmd for '$refId' not found (required by '$($Component.Id)')."
                }
                $abiArgs += $WinmdsById[$refId]
            }
        }

        if ($info.Contains('ExternalRefs')) {
            foreach ($extId in $info.ExternalRefs) {
                if (-not $ExternalWinmdsById.Contains($extId)) {
                    throw "ExternalRefs winmd for '$extId' not found (required by '$($Component.Id)')."
                }
                $abiArgs += $ExternalWinmdsById[$extId]
            }
        }

        $sourceDescription = ($pkgRoots | Where-Object { @(Find-Winmds -PackageRoot $_.Root).Count -gt 0 } | ForEach-Object Id) -join ', '
        Write-Host "  - $($Component.Id): projecting $($allWinmds.Count) winmd(s) from [$sourceDescription] -> $($info.OutputDir)\"
        Invoke-Native $AbiExe @abiArgs
    }

    foreach ($ir in $includeRoots) {
        Write-Host "  - $($Component.Id): copying include payload from $($ir.Id)"
        Copy-Item -Path (Join-Path $ir.Path '*') -Destination $outDir -Recurse -Force
    }

    # Scrub any accidentally-shipped Windows.* headers (these come from
    # include payloads and would over-shadow the platform SDK).
    Get-ChildItem -Recurse -LiteralPath $outDir -Filter 'Windows.*' -File -ErrorAction SilentlyContinue |
        Remove-Item -Force -ErrorAction SilentlyContinue
}

function Update-Readme {
    param(
        [string] $ReadmePath,
        [string] $UmbrellaVersion,
        [pscustomobject[]] $Components
    )

    $beginMarker = '<!-- BEGIN AUTO-GENERATED COMPONENT LIST -->'
    $endMarker   = '<!-- END AUTO-GENERATED COMPONENT LIST -->'

    $sb = New-Object System.Text.StringBuilder
    [void] $sb.AppendLine($beginMarker)
    [void] $sb.AppendLine("Current projection packages, for [Microsoft.WindowsAppSDK v$UmbrellaVersion](https://www.nuget.org/packages/Microsoft.WindowsAppSDK/$UmbrellaVersion):")
    [void] $sb.AppendLine("")
    foreach ($c in $Components) {
        if ($script:ComponentMap.Contains($c.Id)) {
            [void] $sb.AppendLine("* [$($c.Id) v$($c.Version)](https://www.nuget.org/packages/$($c.Id)/$($c.Version))")
        }
    }
    [void] $sb.AppendLine($endMarker)

    $content = Get-Content -LiteralPath $ReadmePath -Raw
    $pattern = "(?s)$([regex]::Escape($beginMarker)).*?$([regex]::Escape($endMarker))"
    if ($content -notmatch $pattern) {
        Write-Warning "README does not contain auto-generated component-list markers; leaving as-is."
        return
    }
    $replacement = $sb.ToString().TrimEnd()
    $content = [regex]::Replace($content, $pattern, { param($m) $replacement })
    Set-Content -LiteralPath $ReadmePath -Value $content -NoNewline
}

function Generate-ReferenceProjectionCpp {
    param(
        [string] $StagingIncDir,
        [string] $OutputCppPath,
        [string] $UmbrellaVersion
    )

    $abiRoot = Join-Path $StagingIncDir 'abi'
    if (-not (Test-Path $abiRoot)) {
        Write-Warning "No abi/ tree under $StagingIncDir; skipping reference_projection.cpp"
        return
    }

    # Include every .h file under inc/abi/ EXCEPT for the categorically-
    # unbuildable subsets:
    #   * <comp>/winrt/*  - C++/WinRT projections that need cppwinrt's
    #                       generated base headers.
    #   * winml/winml/*   - onnxruntime headers that depend on the
    #                       onnxruntime build tree (not shipped here).
    #   * Microsoft.UI.Designer.Interop.h - templated stub that contains
    #                       unprocessed $DUAL_NAMESPACE$ tokens.
    $headers = @(Get-ChildItem -File -Recurse $abiRoot -Filter '*.h' |
        Where-Object {
            $rel  = $_.FullName.Substring($abiRoot.Length + 1)
            $segs = $rel -split '[\\/]'
            ($segs -notcontains 'winrt') -and `
            -not ($segs.Count -ge 2 -and $segs[0] -eq 'winml' -and $segs[1] -eq 'winml') -and `
            -not ($_.Name -eq 'Microsoft.UI.Designer.Interop.h')
        } |
        ForEach-Object { ($_.FullName.Substring($abiRoot.Length + 1)) -replace '\\','/' } |
        Sort-Object)

    $sb = New-Object System.Text.StringBuilder
    [void] $sb.AppendLine('// Copyright (c) Microsoft Corporation.')
    [void] $sb.AppendLine('// Licensed under the MIT License.')
    [void] $sb.AppendLine('')
    [void] $sb.AppendLine("// AUTO-GENERATED by make_projection.ps1 for Microsoft.WindowsAppSDK $UmbrellaVersion.")
    [void] $sb.AppendLine('//')
    [void] $sb.AppendLine('// Smoke test that exercises every projection header under inc/abi/.')
    [void] $sb.AppendLine('// The following categories are excluded:')
    [void] $sb.AppendLine('//   * any winrt/ subdir (C++/WinRT projections - need a separately-')
    [void] $sb.AppendLine('//     generated cppwinrt include tree).')
    [void] $sb.AppendLine('//   * inc/abi/winml/winml/ (onnxruntime headers - require the')
    [void] $sb.AppendLine('//     onnxruntime source/build tree which is not shipped here).')
    [void] $sb.AppendLine('//   * Microsoft.UI.Designer.Interop.h (uses unprocessed $DUAL_NAMESPACE$')
    [void] $sb.AppendLine('//     placeholder tokens; not directly compilable).')
    [void] $sb.AppendLine('')
    [void] $sb.AppendLine('#define WIN32_LEAN_AND_MEAN')
    [void] $sb.AppendLine('#define NOMINMAX')
    [void] $sb.AppendLine('#include <windows.h>')
    [void] $sb.AppendLine('#include <inspectable.h>')
    [void] $sb.AppendLine('#include <hstring.h>')
    [void] $sb.AppendLine('#include <restrictederrorinfo.h>')
    [void] $sb.AppendLine('#include <eventtoken.h>')
    [void] $sb.AppendLine('')
    foreach ($h in $headers) {
        [void] $sb.AppendLine("#include `"../abi/$h`"")
    }
    [void] $sb.AppendLine('')
    [void] $sb.AppendLine('int main() { return 0; }')

    Set-Content -LiteralPath $OutputCppPath -Value $sb.ToString() -NoNewline
    Write-Host "  - inc/test/reference_projection.cpp: $($headers.Count) #include(s)"
}

function Invoke-ProjectionSmokeTest {
    param([string] $TestScriptPath)

    if (-not (Test-Path $TestScriptPath)) {
        Write-Warning "Smoke test script not found at $TestScriptPath; skipping test."
        return
    }

    Write-Step "Running projection smoke test (inc/test/test.ps1)"
    Write-Host "  $TestScriptPath"
    Write-Host ""
    & pwsh -NoProfile -ExecutionPolicy Bypass -File $TestScriptPath
    if ($LASTEXITCODE -ne 0) {
        throw "Projection smoke test failed (exit $LASTEXITCODE). Re-run with -SkipTest to bypass."
    }
}

# ----------------------------------------------------------------------
# Main
# ----------------------------------------------------------------------

$repoRoot = Get-RepoRoot

if (-not $WorkingDirectory) {
    $WorkingDirectory = Join-Path $env:TEMP "wasdk_inc_$Version"
}
$WorkingDirectory = [System.IO.Path]::GetFullPath($WorkingDirectory)

if (Test-PathInsideRepo -Path $WorkingDirectory -RepoRoot $repoRoot) {
    throw "WorkingDirectory '$WorkingDirectory' must be outside the repository ($repoRoot)."
}

$nugetExe = Resolve-Tool 'nuget'
$gitExe   = Resolve-Tool 'git'

$incDir       = Join-Path $repoRoot 'inc'
$readmePath   = Join-Path $incDir   'README.md'
$scriptPath   = Join-Path $incDir   'make_projection.ps1'
$testDir      = Join-Path $incDir   'test'
$testScript   = Join-Path $testDir  'test.ps1'
$testIgnore   = Join-Path $testDir  '.gitignore'

if (-not (Test-Path $readmePath))   { throw "Source README not found: $readmePath" }
if (-not (Test-Path $scriptPath))   { throw "Source script not found: $scriptPath" }
if (-not (Test-Path $testScript))   { throw "Source test script not found: $testScript" }

# Capture script + readme + test content NOW, before we touch the working tree.
$savedReadme     = Get-Content -Raw -LiteralPath $readmePath
$savedScript     = Get-Content -Raw -LiteralPath $scriptPath
$savedTestScript = Get-Content -Raw -LiteralPath $testScript
$savedTestIgnore = if (Test-Path $testIgnore) { Get-Content -Raw -LiteralPath $testIgnore } else { ".packages/`n" }

if (-not $NoCommit) {
    $dirty = & $gitExe -C $repoRoot status --porcelain
    if ($dirty) {
        throw "Working tree is not clean. Commit or stash changes before running."
    }
    $existing = & $gitExe -C $repoRoot rev-parse --verify --quiet "refs/heads/release/$Version" 2>$null
    if ($existing -and -not $Force) {
        throw "Local branch 'release/$Version' already exists. Use -Force to replace it."
    }
}

$startBranch = (& $gitExe -C $repoRoot rev-parse --abbrev-ref HEAD).Trim()
Write-Step "Starting branch: $startBranch"
Write-Step "Working directory: $WorkingDirectory"

if (Test-Path $WorkingDirectory) {
    Remove-Item -Recurse -Force $WorkingDirectory
}
New-Item -ItemType Directory -Force -Path $WorkingDirectory | Out-Null

$packagesDir = Join-Path $WorkingDirectory 'packages'
$stagingDir  = Join-Path $WorkingDirectory 'staging'
$stagingIncDir = Join-Path $stagingDir 'inc'

New-Item -ItemType Directory -Force -Path $packagesDir | Out-Null
New-Item -ItemType Directory -Force -Path $stagingIncDir | Out-Null

try {
    Write-Step "Acquiring AbiWinRT tooling"
    Invoke-Native $nugetExe install Microsoft.Windows.AbiWinRT `
        -OutputDirectory $packagesDir -Verbosity quiet | Out-Null
    $abiExe = (Get-ChildItem -Recurse $packagesDir -Filter 'abi.exe' | Select-Object -First 1).FullName
    if (-not $abiExe) { throw "abi.exe not found after install." }
    Write-Host "  abi.exe: $abiExe"

    Write-Step "Acquiring metapackage Microsoft.WindowsAppSDK $Version"
    Install-NugetPackage -Id 'Microsoft.WindowsAppSDK' -PkgVersion $Version `
        -OutputDirectory $packagesDir -NugetExe $nugetExe

    $components = Get-MetapackageDependencies -PackagesDir $packagesDir -UmbrellaVersion $Version
    Write-Step "Discovered $($components.Count) component(s):"
    $components | ForEach-Object { Write-Host "  - $($_.Id) $($_.Version)" }

    Write-Step "Downloading component packages"
    foreach ($c in $components) {
        Install-NugetPackage -Id $c.Id -PkgVersion $c.Version `
            -OutputDirectory $packagesDir -NugetExe $nugetExe
    }

    Write-Step "Installing component AuxiliaryPackages"
    foreach ($id in $script:ComponentMap.Keys) {
        $info = $script:ComponentMap[$id]
        if (-not $info.Contains('AuxiliaryPackages')) { continue }
        foreach ($aux in $info.AuxiliaryPackages) {
            if ($aux.Contains('Version') -and $aux.Version) {
                Write-Host "  - $($aux.Id) $($aux.Version)  (auxiliary for $id)"
                Install-NugetPackage -Id $aux.Id -PkgVersion $aux.Version `
                    -OutputDirectory $packagesDir -NugetExe $nugetExe
            } else {
                Write-Host "  - $($aux.Id) (latest)  (auxiliary for $id)"
                Invoke-Native $nugetExe install $aux.Id `
                    -OutputDirectory $packagesDir `
                    -PackageSaveMode nuspec `
                    -DependencyVersion Ignore `
                    -Verbosity quiet | Out-Null
            }
        }
    }

    Write-Step "Acquiring external reference packages"
    $externalWinmdsById = @{}
    foreach ($ext in $script:ExternalReferencePackages) {
        Write-Host "  - $($ext.Id) (latest)"
        Invoke-Native $nugetExe install $ext.Id `
            -OutputDirectory $packagesDir `
            -PackageSaveMode nuspec `
            -DependencyVersion Ignore `
            -Verbosity quiet | Out-Null
        $extWinmds = @(Get-ChildItem -Recurse -LiteralPath $packagesDir -Filter '*.winmd' -ErrorAction SilentlyContinue |
            Where-Object { $_.FullName -like "*\$($ext.Id).*" -and $_.FullName -notlike '*\tools\*' })
        if ($extWinmds.Count -eq 0) {
            Write-Warning "    no winmd found in $($ext.Id)"
        } else {
            $externalWinmdsById[$ext.Id] = @($extWinmds.FullName)
            $extWinmds | ForEach-Object { Write-Host "    $($_.Name)" }
        }
    }

    # Build a lookup of package-ID -> array of winmd paths.
    $winmdsById = @{}
    foreach ($c in $components) {
        $pkgRoot = Join-Path $packagesDir "$($c.Id).$($c.Version)"
        $w = @(Find-Winmds -PackageRoot $pkgRoot)
        if ($w.Count -gt 0) { $winmdsById[$c.Id] = @($w.FullName) }
    }

    Write-Step "Generating projection headers in staging area"
    foreach ($c in $components) {
        try {
            Generate-ProjectionForComponent `
                -Component $c `
                -PackagesDir $packagesDir `
                -StagingIncDir $stagingIncDir `
                -AbiExe $abiExe `
                -WinmdsById $winmdsById `
                -ExternalWinmdsById $externalWinmdsById
        } catch {
            Write-Host ""
            Write-Host "FAILED for component $($c.Id):" -ForegroundColor Red
            Write-Host "  $($_.Exception.Message)" -ForegroundColor Red
            Write-Host $_.ScriptStackTrace
            throw
        }
    }

    # Lay down the README and script in staging so that the orphan
    # branch carries them too.
    Set-Content -LiteralPath (Join-Path $stagingIncDir 'README.md')           -Value $savedReadme -NoNewline
    Set-Content -LiteralPath (Join-Path $stagingIncDir 'make_projection.ps1') -Value $savedScript -NoNewline

    # Refresh the README's auto-generated component-version section.
    Update-Readme -ReadmePath (Join-Path $stagingIncDir 'README.md') `
                  -UmbrellaVersion $Version `
                  -Components $components

    # Lay down the test harness: test.ps1 + .gitignore are carried
    # forward verbatim, while reference_projection.cpp is regenerated
    # from the staged inc/abi/ tree on each run.
    $stagingTestDir = Join-Path $stagingIncDir 'test'
    New-Item -ItemType Directory -Force -Path $stagingTestDir | Out-Null
    Set-Content -LiteralPath (Join-Path $stagingTestDir 'test.ps1')    -Value $savedTestScript -NoNewline
    Set-Content -LiteralPath (Join-Path $stagingTestDir '.gitignore')  -Value $savedTestIgnore -NoNewline
    Generate-ReferenceProjectionCpp `
        -StagingIncDir  $stagingIncDir `
        -OutputCppPath  (Join-Path $stagingTestDir 'reference_projection.cpp') `
        -UmbrellaVersion $Version

    Write-Step "Staging area produced at: $stagingIncDir"
    Get-ChildItem -Recurse $stagingIncDir | Measure-Object | ForEach-Object {
        Write-Host "  $($_.Count) item(s) total"
    }

    if ($NoCommit) {
        Write-Step "NoCommit: skipping git operations. Inspect the staging area above."
        if (-not $SkipTest) {
            Invoke-ProjectionSmokeTest -TestScriptPath (Join-Path $stagingIncDir 'test\test.ps1')
        }
        return
    }

    # ------------------------------------------------------------------
    # Git: create orphan branch and commit the staging contents.
    # ------------------------------------------------------------------
    Write-Step "Creating orphan branch release/$Version"
    if ($Force -and $existing) {
        Invoke-Native $gitExe -C $repoRoot branch -D "release/$Version"
    }
    Invoke-Native $gitExe -C $repoRoot checkout --orphan "release/$Version"

    # Wipe the index and the working tree, but keep .git intact.
    Invoke-Native $gitExe -C $repoRoot rm -rf --quiet . | Out-Null
    Invoke-Native $gitExe -C $repoRoot clean -fdx --exclude=.git | Out-Null

    Write-Step "Copying staged inc/ into repository"
    New-Item -ItemType Directory -Force -Path $incDir | Out-Null
    Copy-Item -Path (Join-Path $stagingIncDir '*') -Destination $incDir -Recurse -Force

    # Stamp copyright headers if the repo's helper still happens to be
    # accessible (it won't be, on a fresh orphan -- so this is best-
    # effort and silently skipped).
    $verifier = Join-Path $repoRoot 'tools\VerifyCopyrightHeaders.cmd'
    if (Test-Path $verifier) {
        Write-Host "  Running VerifyCopyrightHeaders.cmd -fix"
        & $verifier -fix | Out-Null
    }

    Invoke-Native $gitExe -C $repoRoot add inc/
    Invoke-Native $gitExe -C $repoRoot commit -m "AbiWinRT projection headers for Microsoft.WindowsAppSDK $Version"

    if (-not $SkipTest) {
        Invoke-ProjectionSmokeTest -TestScriptPath (Join-Path $incDir 'test\test.ps1')
    }

    Write-Step "Done."
    Write-Host ""
    Write-Host "Local branch 'release/$Version' is ready." -ForegroundColor Green
    Write-Host "Review the commit, then push when ready:" -ForegroundColor Green
    Write-Host "    git push origin release/$Version" -ForegroundColor Green
    Write-Host ""
    Write-Host "To return to your previous branch: git checkout $startBranch"
}
finally {
    if (-not $KeepWorkingDirectory) {
        if (Test-Path $WorkingDirectory) {
            Remove-Item -Recurse -Force $WorkingDirectory -ErrorAction SilentlyContinue
        }
    } else {
        Write-Host "Working directory preserved at $WorkingDirectory"
    }
}
