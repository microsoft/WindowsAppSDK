# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#+
.SYNOPSIS
Validates the WinUI 3 dotnet new template pack end-to-end.

.DESCRIPTION
Builds (or consumes) the template NuGet package, reinstalls it locally, and
scaffolds every WinUI 3 project and item template. Each generated project is
built, and app templates are optionally launched via dotnet run using the
recommended WinAppSDK self-contained properties.

.PARAMETER PackagePath
Path to an existing Microsoft.WindowsAppSDK.WinUI.CSharp.Templates .nupkg. When
omitted, the script runs dotnet pack to create a package under -PackOutputDirectory.

.PARAMETER Configuration
MSBuild configuration used for dotnet pack (default: Release).

.PARAMETER PackOutputDirectory
Directory (relative to the repo root or absolute) where dotnet pack should emit
the .nupkg (default: localpackages).

.PARAMETER Platforms
One or more MSBuild Platform values to validate for each template (default: x64).

.PARAMETER SkipAppLaunch
Skips launching the generated WinUI apps at the end of the run. Builds still
occur.

.PARAMETER RunTimeoutSeconds
If greater than zero, any WinUI apps launched at the end of the run are
automatically closed after the specified number of seconds. A value of 0 keeps
them open until you close each window manually (default).

.PARAMETER KeepWorkingDirectory
Preserves the temporary scaffolding directory instead of deleting it.

.EXAMPLE
PS> ./Test-DotnetNewTemplates.ps1

Builds the template pack, installs it, scaffolds every template, and runs app
templates for x64.

.EXAMPLE
PS> ./Test-DotnetNewTemplates.ps1 -PackagePath C:/tmp/Templates.nupkg -Platforms x64,arm64 -SkipAppLaunch

Installs the provided package and validates builds for both x64 and arm64
without launching the apps.
#>
[CmdletBinding()]
param(
    [Parameter()]
    [string]$PackagePath,

    [Parameter()]
    [string]$Configuration = 'Release',

    [Parameter()]
    [string]$PackOutputDirectory = 'localpackages',

    [Parameter()]
    [string[]]$Platforms = @('x64'),

    [Parameter()]
    [switch]$SkipAppLaunch,

    [Parameter()]
    [int]$RunTimeoutSeconds = 0,

    [Parameter()]
    [switch]$KeepWorkingDirectory
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

$script:exitCode = 0
$results = New-Object System.Collections.Generic.List[object]
$appExecutables = New-Object System.Collections.Generic.List[object]
$dotnetPath = (Get-Command dotnet -ErrorAction Stop).Source
$workingRoot = $null
$originalNugetPackages = $env:NUGET_PACKAGES

function Write-Step {
    param([string]$Message)
    Write-Host "`n>> $Message" -ForegroundColor Cyan
}

function Add-Result {
    param(
        [string]$Template,
        [string]$Platform,
        [string]$Step,
        [string]$Status,
        [string]$Path
    )

    $results.Add([pscustomobject]@{
            Template = $Template
            Platform = $Platform
            Step     = $Step
            Status   = $Status
            Path     = $Path
        }) | Out-Null
}

function Invoke-DotnetCommand {
    param(
        [string[]]$Arguments,
        [string]$WorkingDirectory,
        [string]$Description,
        [switch]$CaptureOutput
    )

    $display = "dotnet {0}" -f ($Arguments -join ' ')
    Write-Step "$display ($Description)"

    Push-Location -Path $WorkingDirectory
    try {
        # Temporarily allow stderr from native commands to avoid treating
        # non-fatal messages (e.g. dotnet template update checks) as
        # terminating errors. Real failures are caught via $LASTEXITCODE.
        $savedEAP = $ErrorActionPreference
        $ErrorActionPreference = 'Continue'
        if ($CaptureOutput.IsPresent) {
            $output = & $dotnetPath @Arguments 2>&1
        }
        else {
            & $dotnetPath @Arguments 2>&1 | ForEach-Object { Write-Host $_ }
        }
        $exitCode = $LASTEXITCODE
    }
    finally {
        $ErrorActionPreference = $savedEAP
        Pop-Location
    }

    if ($exitCode -ne 0) {
        throw "dotnet $Description failed with exit code $exitCode"
    }

    if ($CaptureOutput.IsPresent) {
        return $output
    }
}

function Get-TemplatePackagePath {
    param(
        [string]$PackagePathOverride,
        [string]$ProjectPath,
        [string]$Configuration,
        [string]$PackOutputDirectory,
        [string]$RepoRoot
    )

    if ($PackagePathOverride) {
        if (-not (Test-Path -Path $PackagePathOverride -PathType Leaf)) {
            throw "PackagePath '$PackagePathOverride' does not exist."
        }
        return (Resolve-Path -Path $PackagePathOverride).Path
    }

    $packOutput = if ([System.IO.Path]::IsPathRooted($PackOutputDirectory)) {
        $PackOutputDirectory
    }
    else {
        Join-Path -Path $RepoRoot -ChildPath $PackOutputDirectory
    }

    if (-not (Test-Path -Path $packOutput)) {
        Write-Step "Creating pack output directory '$packOutput'"
        New-Item -ItemType Directory -Path $packOutput -Force | Out-Null
    }

    Invoke-DotnetCommand -Arguments @('pack', $ProjectPath, '-c', $Configuration, '-o', $packOutput) -WorkingDirectory $RepoRoot -Description "pack template project"

    $package = Get-ChildItem -Path $packOutput -Filter 'Microsoft.WindowsAppSDK*.nupkg' | Sort-Object LastWriteTime -Descending | Select-Object -First 1
    if (-not $package) {
        throw "No template package was produced in '$packOutput'."
    }
    return $package.FullName
}

function Remove-TemplatePackIfPresent {
    param([string]$RepoRoot)

    try {
        Invoke-DotnetCommand -Arguments @('new', 'uninstall', 'Microsoft.WindowsAppSDK.WinUI.CSharp.Templates') -WorkingDirectory $RepoRoot -Description 'uninstall existing template pack'
    }
    catch {
        Write-Step 'Template pack uninstall reported no installed instances; continuing.'
    }
}

function Install-TemplatePack {
    param(
        [string]$RepoRoot,
        [string]$PackageToInstall
    )

    Remove-StaleTemplateEnginePackage -PackagePath $PackageToInstall
    Invoke-DotnetCommand -Arguments @('new', 'install', $PackageToInstall) -WorkingDirectory $RepoRoot -Description 'install template pack'
}

function Remove-StaleTemplateEnginePackage {
    param([string]$PackagePath)

    $packageFileName = [System.IO.Path]::GetFileName($PackagePath)
    $templateEngineDir = Join-Path -Path $env:USERPROFILE -ChildPath '.templateengine\packages'
    if (-not (Test-Path -Path $templateEngineDir -PathType Container)) {
        return
    }

    $cachedPackage = Join-Path -Path $templateEngineDir -ChildPath $packageFileName
    if (Test-Path -Path $cachedPackage -PathType Leaf) {
        Write-Step "Removing cached template package '$cachedPackage'"
        Remove-Item -Path $cachedPackage -Force
    }
}

function Get-AppExecutablePath {
    param(
        [string]$ProjectPath,
        [string]$ProjectName
    )

    $binFolder = Join-Path -Path $ProjectPath -ChildPath 'bin'
    if (-not (Test-Path -Path $binFolder -PathType Container)) {
        return $null
    }

    $exe = Get-ChildItem -Path $binFolder -Filter "$ProjectName.exe" -Recurse -ErrorAction SilentlyContinue | Sort-Object LastWriteTime -Descending | Select-Object -First 1
    if ($exe) {
        return $exe.FullName
    }
    return $null
}

function Launch-AppExecutables {
    param([int]$TimeoutSeconds)

    if ($appExecutables.Count -eq 0) {
        Write-Step 'No WinUI executables were recorded for launch.'
        return
    }

    Write-Step 'Launching WinUI apps for manual validation...'
    foreach ($entry in $appExecutables) {
        Write-Host "Launching $($entry.Template) ($($entry.Platform)) -> $($entry.Path)" -ForegroundColor Yellow
        try {
            $process = Start-Process -FilePath $entry.Path -PassThru -WindowStyle Normal
            if ($TimeoutSeconds -gt 0) {
                $exited = $process.WaitForExit($TimeoutSeconds * 1000)
                if (-not $exited) {
                    Write-Warning "App '$($entry.Path)' is still running after $TimeoutSeconds seconds; terminating process."
                    $process.Kill()
                }
                elseif ($process.ExitCode -ne 0) {
                    Write-Warning "App '$($entry.Path)' exited with code $($process.ExitCode)."
                }
            }
        }
        catch {
            Write-Warning "Failed to start '$($entry.Path)': $_"
        }
    }

    if ($TimeoutSeconds -le 0) {
        Write-Host "`nAll WinUI apps are running. Manually validate them and close each window when finished." -ForegroundColor Cyan
    }
}

function New-ProjectFromTemplate {
    param(
        [string]$TemplateShortName,
        [string]$ProjectName,
        [string]$OutputPath,
        [string]$WorkingDirectory
    )

    if (-not (Test-Path -Path $OutputPath)) {
        New-Item -ItemType Directory -Path $OutputPath -Force | Out-Null
    }

    Invoke-DotnetCommand -Arguments @('new', $TemplateShortName, '-n', $ProjectName, '-o', $OutputPath, '--force', '--no-update-check') -WorkingDirectory $WorkingDirectory -Description "create $TemplateShortName template"
}

function Test-WinUiProjectTemplate {
    param(
        [string]$TemplateShortName,
        [ValidateSet('App', 'Library', 'Test')]
        [string]$Kind,
        [string]$Platform,
        [string]$WorkingRoot
    )

    $projectName = '{0}_{1}_{2}' -f $TemplateShortName, $Platform, ([Guid]::NewGuid().ToString('N').Substring(0, 8))
    $projectPath = Join-Path -Path $WorkingRoot -ChildPath $projectName
    New-ProjectFromTemplate -TemplateShortName $TemplateShortName -ProjectName $projectName -OutputPath $projectPath -WorkingDirectory $WorkingRoot
    Add-Result -Template $TemplateShortName -Platform $Platform -Step 'create' -Status 'Succeeded' -Path $projectPath

    $projectFile = Join-Path -Path $projectPath -ChildPath "$projectName.csproj"

    switch ($Kind) {
        'App' {
            Invoke-DotnetCommand -Arguments @('build', $projectFile, '-p:Configuration=Debug', "-p:Platform=$Platform", '-p:WindowsPackageType=None') -WorkingDirectory $projectPath -Description 'build app template'
            Add-Result -Template $TemplateShortName -Platform $Platform -Step 'build' -Status 'Succeeded' -Path $projectFile

            $exePath = Get-AppExecutablePath -ProjectPath $projectPath -ProjectName $projectName
            if ($exePath) {
                $appExecutables.Add([pscustomobject]@{
                        Template = $TemplateShortName
                        Platform = $Platform
                        Path     = $exePath
                    }) | Out-Null
            }
            else {
                Write-Warning "Unable to locate executable for template '$TemplateShortName' at '$projectPath'."
            }
        }
        'Library' {
            Invoke-DotnetCommand -Arguments @('build', $projectFile, '-c', 'Debug') -WorkingDirectory $projectPath -Description 'build library template'
            Add-Result -Template $TemplateShortName -Platform 'AnyCPU' -Step 'build' -Status 'Succeeded' -Path $projectFile
        }
        'Test' {
            Invoke-DotnetCommand -Arguments @('test', $projectFile, '-p:Configuration=Debug', "-p:Platform=$Platform") -WorkingDirectory $projectPath -Description 'test packaged test template'
            Add-Result -Template $TemplateShortName -Platform $Platform -Step 'test' -Status 'Succeeded' -Path $projectFile
        }
    }
}

function Test-ItemTemplates {
    param(
        [string]$WorkingRoot,
        [string]$Platform
    )

    $hostName = 'ItemHost_{0}' -f ([Guid]::NewGuid().ToString('N').Substring(0, 8))
    $hostPath = Join-Path -Path $WorkingRoot -ChildPath $hostName
    New-ProjectFromTemplate -TemplateShortName 'winui' -ProjectName $hostName -OutputPath $hostPath -WorkingDirectory $WorkingRoot
    Add-Result -Template 'winui (item host)' -Platform $Platform -Step 'create' -Status 'Succeeded' -Path $hostPath

    $projectFile = Join-Path -Path $hostPath -ChildPath "$hostName.csproj"
    $itemTemplates = @(
        @{ ShortName = 'winui-page'; Name = 'SettingsPage' },
        @{ ShortName = 'winui-window'; Name = 'SecondaryWindow' },
        @{ ShortName = 'winui-usercontrol'; Name = 'ProfileCard' },
        @{ ShortName = 'winui-templatedcontrol'; Name = 'DashboardControl' },
        @{ ShortName = 'winui-resourcedictionary'; Name = 'Colors' },
        @{ ShortName = 'winui-resw'; Name = 'Strings' },
        @{ ShortName = 'winui-dialog'; Name = 'ConfirmationDialog' }
    )

    foreach ($item in $itemTemplates) {
        $args = @('new', $item.ShortName, '-n', $item.Name, '--project', $projectFile, '--force', '--no-update-check')
        Invoke-DotnetCommand -Arguments $args -WorkingDirectory $hostPath -Description "create item template $($item.ShortName)"
        Add-Result -Template $item.ShortName -Platform $Platform -Step 'add item' -Status 'Succeeded' -Path $projectFile
    }

    Invoke-DotnetCommand -Arguments @('build', $projectFile, '-p:Configuration=Debug', "-p:Platform=$Platform", '-p:WindowsPackageType=None') -WorkingDirectory $hostPath -Description 'build item host'
    Add-Result -Template 'winui (item host)' -Platform $Platform -Step 'build' -Status 'Succeeded' -Path $projectFile
}

function Assert-CsprojPackageVersion {
    param(
        [string]$CsprojPath,
        [string]$PackageName,
        [string]$ExpectedVersion
    )

    [xml]$csproj = Get-Content -Path $CsprojPath
    $ref = $csproj.SelectNodes('//PackageReference') |
        Where-Object { $_.Include -eq $PackageName }
    if (-not $ref) {
        throw "PackageReference '$PackageName' not found in '$CsprojPath'"
    }
    if ($ref.Version -ne $ExpectedVersion) {
        throw "PackageReference '$PackageName' has Version='$($ref.Version)' but expected '$ExpectedVersion' in '$CsprojPath'"
    }
}

try {
    $repoRoot = (Resolve-Path -Path (Join-Path -Path $PSScriptRoot -ChildPath '..\..\..')).Path
    $templateProject = Join-Path -Path $repoRoot -ChildPath 'dev\Templates\Dotnet\WinAppSdk.CSharp.DotnetNewTemplates.csproj'
    $tempBase = Join-Path -Path ([System.IO.Path]::GetTempPath()) -ChildPath 'DotnetNewTemplateValidation'
    $workingRoot = Join-Path -Path $tempBase -ChildPath ([Guid]::NewGuid().ToString('N'))

    if (Test-Path -Path $workingRoot) {
        Remove-Item -Path $workingRoot -Recurse -Force
    }
    New-Item -ItemType Directory -Path $workingRoot -Force | Out-Null

    $nugetFallback = Join-Path -Path $workingRoot -ChildPath '.nuget'
    New-Item -ItemType Directory -Path $nugetFallback -Force | Out-Null
    $env:NUGET_PACKAGES = $nugetFallback

    # Disable the MSBuild server to avoid lingering processes on CI agents.
    $env:DOTNET_CLI_DO_NOT_USE_MSBUILD_SERVER = 'true'

    # Generate a NuGet.config so scaffolded projects resolve packages from
    # internal feeds only. The repo's NuGet.config has relative local-source
    # paths (tools/nuget, localpackages) that don't exist under the temp
    # directory, and nuget.org is blocked by OneBranch network isolation.
    # We extract only the remote (https) feeds from the repo config.
    $repoNugetConfig = Join-Path -Path $repoRoot -ChildPath 'NuGet.config'
    $workNugetConfig = Join-Path -Path $workingRoot -ChildPath 'NuGet.config'
    if (Test-Path -Path $repoNugetConfig -PathType Leaf) {
        [xml]$srcConfig = Get-Content -Path $repoNugetConfig
        $remoteSources = $srcConfig.configuration.packageSources.add |
            Where-Object { $_.value -match '^https?://' }

        if (-not $remoteSources) {
            throw "No remote (https) NuGet sources found in $repoNugetConfig."
        }

        $configLines = @(
            '<?xml version="1.0" encoding="utf-8"?>'
            '<configuration>'
            '  <packageSources>'
            '    <clear />'
        )
        foreach ($src in $remoteSources) {
            $configLines += '    <add key="{0}" value="{1}" />' -f $src.key, $src.value
        }
        $configLines += @(
            '  </packageSources>'
            '  <disabledPackageSources>'
            '    <clear />'
            '  </disabledPackageSources>'
            '  <fallbackPackageFolders>'
            '    <clear />'
            '  </fallbackPackageFolders>'
            '</configuration>'
        )
        $configLines | Set-Content -Path $workNugetConfig -Encoding UTF8
        Write-Step "Generated NuGet.config with remote feeds in working directory"
    }

    $packageToInstall = Get-TemplatePackagePath -PackagePathOverride $PackagePath -ProjectPath $templateProject -Configuration $Configuration -PackOutputDirectory $PackOutputDirectory -RepoRoot $repoRoot
    Write-Step "Using template package '$packageToInstall'"

    Remove-TemplatePackIfPresent -RepoRoot $repoRoot
    Install-TemplatePack -RepoRoot $repoRoot -PackageToInstall $packageToInstall

    $projectTemplates = @(
        @{ ShortName = 'winui'; Kind = 'App' },
        @{ ShortName = 'winui-navview'; Kind = 'App' },
        @{ ShortName = 'winui-tabview'; Kind = 'App' },
        @{ ShortName = 'winui-mvvm'; Kind = 'App' },
        @{ ShortName = 'winui-lib'; Kind = 'Library' },
        # winui-unittest is a self-hosted packaged test runner: tests run
        # from inside UnitTestApp.OnLaunched (which sets DispatcherQueue and
        # acquires package identity) via UnitTestClient.Run(), not via
        # `dotnet test`. Validate it as an App so we still confirm the
        # template builds cleanly.
        @{ ShortName = 'winui-unittest'; Kind = 'App' }
    )

    foreach ($template in $projectTemplates) {
        foreach ($platform in $Platforms) {
            Test-WinUiProjectTemplate -TemplateShortName $template.ShortName -Kind $template.Kind -Platform $platform -WorkingRoot $workingRoot
        }
    }

    Test-ItemTemplates -WorkingRoot $workingRoot -Platform $Platforms[0]

    # ─── Version parameter test scenarios ───
    Write-Step 'Running version parameter test scenarios...'

    # Scenario 1: Default (no version passed) — verify Version="*"
    $defaultPath = Join-Path -Path $workingRoot -ChildPath 'VersionDefault'
    New-ProjectFromTemplate -TemplateShortName 'winui' -ProjectName 'VersionDefault' -OutputPath $defaultPath -WorkingDirectory $workingRoot
    $defaultCsproj = Join-Path -Path $defaultPath -ChildPath 'VersionDefault.csproj'
    Assert-CsprojPackageVersion -CsprojPath $defaultCsproj -PackageName 'Microsoft.WindowsAppSDK' -ExpectedVersion '*'
    Assert-CsprojPackageVersion -CsprojPath $defaultCsproj -PackageName 'Microsoft.Windows.SDK.BuildTools' -ExpectedVersion '*'
    Assert-CsprojPackageVersion -CsprojPath $defaultCsproj -PackageName 'Microsoft.Windows.SDK.BuildTools.WinApp' -ExpectedVersion '*'
    Add-Result -Template 'winui' -Platform 'N/A' -Step 'default version content' -Status 'Succeeded' -Path $defaultPath

    # Scenario 2: Pinned WindowsAppSDK version only
    $pinnedPath = Join-Path -Path $workingRoot -ChildPath 'VersionPinned'
    Invoke-DotnetCommand -Arguments @('new', 'winui', '-n', 'VersionPinned', '-o', $pinnedPath, '--wasdk-version', '1.7.250127002', '--force', '--no-update-check') -WorkingDirectory $workingRoot -Description 'create winui with pinned WASDK version'
    $pinnedCsproj = Join-Path -Path $pinnedPath -ChildPath 'VersionPinned.csproj'
    Assert-CsprojPackageVersion -CsprojPath $pinnedCsproj -PackageName 'Microsoft.WindowsAppSDK' -ExpectedVersion '1.7.250127002'
    Assert-CsprojPackageVersion -CsprojPath $pinnedCsproj -PackageName 'Microsoft.Windows.SDK.BuildTools' -ExpectedVersion '*'
    Assert-CsprojPackageVersion -CsprojPath $pinnedCsproj -PackageName 'Microsoft.Windows.SDK.BuildTools.WinApp' -ExpectedVersion '*'
    Add-Result -Template 'winui' -Platform 'N/A' -Step 'pinned version content' -Status 'Succeeded' -Path $pinnedPath

    # Scenario 3: All versions pinned
    $allPinnedPath = Join-Path -Path $workingRoot -ChildPath 'VersionAllPinned'
    Invoke-DotnetCommand -Arguments @('new', 'winui', '-n', 'VersionAllPinned', '-o', $allPinnedPath, '--wasdk-version', '1.7.250127002', '--build-tools-version', '10.0.26100.1742', '--winapp-version', '0.3.1', '--force', '--no-update-check') -WorkingDirectory $workingRoot -Description 'create winui with all versions pinned'
    $allPinnedCsproj = Join-Path -Path $allPinnedPath -ChildPath 'VersionAllPinned.csproj'
    Assert-CsprojPackageVersion -CsprojPath $allPinnedCsproj -PackageName 'Microsoft.WindowsAppSDK' -ExpectedVersion '1.7.250127002'
    Assert-CsprojPackageVersion -CsprojPath $allPinnedCsproj -PackageName 'Microsoft.Windows.SDK.BuildTools' -ExpectedVersion '10.0.26100.1742'
    Assert-CsprojPackageVersion -CsprojPath $allPinnedCsproj -PackageName 'Microsoft.Windows.SDK.BuildTools.WinApp' -ExpectedVersion '0.3.1'
    Add-Result -Template 'winui' -Platform 'N/A' -Step 'all pinned version content' -Status 'Succeeded' -Path $allPinnedPath

    # Scenario 4: Pre-release version string
    $preReleasePath = Join-Path -Path $workingRoot -ChildPath 'VersionPreRelease'
    Invoke-DotnetCommand -Arguments @('new', 'winui', '-n', 'VersionPreRelease', '-o', $preReleasePath, '--wasdk-version', '1.8.0-preview1', '--force', '--no-update-check') -WorkingDirectory $workingRoot -Description 'create winui with pre-release version'
    $preReleaseCsproj = Join-Path -Path $preReleasePath -ChildPath 'VersionPreRelease.csproj'
    Assert-CsprojPackageVersion -CsprojPath $preReleaseCsproj -PackageName 'Microsoft.WindowsAppSDK' -ExpectedVersion '1.8.0-preview1'
    Add-Result -Template 'winui' -Platform 'N/A' -Step 'pre-release version content' -Status 'Succeeded' -Path $preReleasePath

    # Scenario 5: Invalid version — scaffold succeeds but NuGet restore fails
    Write-Step 'Testing invalid version handling...'
    $invalidPath = Join-Path -Path $workingRoot -ChildPath 'VersionInvalid'
    Invoke-DotnetCommand -Arguments @('new', 'winui', '-n', 'VersionInvalid', '-o', $invalidPath, '--wasdk-version', 'not-a-version', '--force', '--no-update-check') -WorkingDirectory $workingRoot -Description 'create winui with invalid version'
    $invalidCsproj = Join-Path -Path $invalidPath -ChildPath 'VersionInvalid.csproj'
    Assert-CsprojPackageVersion -CsprojPath $invalidCsproj -PackageName 'Microsoft.WindowsAppSDK' -ExpectedVersion 'not-a-version'
    # Build should fail because NuGet can't parse an invalid version string
    $invalidBuildFailed = $false
    try {
        Invoke-DotnetCommand -Arguments @('build', $invalidCsproj, '-p:Configuration=Debug', '-p:Platform=x64', '-p:WindowsPackageType=None') -WorkingDirectory $invalidPath -Description 'build with invalid version (should fail)'
    }
    catch {
        $invalidBuildFailed = $true
    }
    if (-not $invalidBuildFailed) {
        throw "Expected build to fail for invalid WASDK version 'not-a-version'"
    }
    Add-Result -Template 'winui' -Platform 'N/A' -Step 'invalid version: scaffold OK, build fails' -Status 'Succeeded' -Path $invalidPath

    # Scenario 6: Valid version format but nonexistent package
    $nonexistentPath = Join-Path -Path $workingRoot -ChildPath 'VersionNonexistent'
    Invoke-DotnetCommand -Arguments @('new', 'winui', '-n', 'VersionNonexistent', '-o', $nonexistentPath, '--wasdk-version', '99.99.99', '--force', '--no-update-check') -WorkingDirectory $workingRoot -Description 'create winui with nonexistent version'
    $nonexistentCsproj = Join-Path -Path $nonexistentPath -ChildPath 'VersionNonexistent.csproj'
    Assert-CsprojPackageVersion -CsprojPath $nonexistentCsproj -PackageName 'Microsoft.WindowsAppSDK' -ExpectedVersion '99.99.99'
    # Build should fail because NuGet can't find this package version
    $buildFailed = $false
    try {
        Invoke-DotnetCommand -Arguments @('build', $nonexistentCsproj, '-p:Configuration=Debug', '-p:Platform=x64', '-p:WindowsPackageType=None') -WorkingDirectory $nonexistentPath -Description 'build with nonexistent version (should fail)'
    }
    catch {
        $buildFailed = $true
    }
    if (-not $buildFailed) {
        throw "Expected build to fail for nonexistent WASDK version 99.99.99"
    }
    Add-Result -Template 'winui' -Platform 'N/A' -Step 'nonexistent version: scaffold OK, build fails' -Status 'Succeeded' -Path $nonexistentPath

    Write-Step 'Version parameter test scenarios completed.'

    if ($appExecutables.Count -gt 0) {
        if ($SkipAppLaunch.IsPresent) {
            Write-Step 'SkipAppLaunch specified; WinUI apps were not started automatically.'
        }
        else {
            Launch-AppExecutables -TimeoutSeconds $RunTimeoutSeconds
        }
    }

    Write-Step 'All templates validated successfully.'
}
catch {
    $script:exitCode = 1
    Write-Error $_
}
finally {
    if ($null -ne $originalNugetPackages) {
        $env:NUGET_PACKAGES = $originalNugetPackages
    }
    else {
        Remove-Item Env:NUGET_PACKAGES -ErrorAction SilentlyContinue
    }

    Remove-Item Env:DOTNET_CLI_DO_NOT_USE_MSBUILD_SERVER -ErrorAction SilentlyContinue

    if (-not $KeepWorkingDirectory.IsPresent -and (Test-Path -Path $workingRoot)) {
        Write-Step "Cleaning up '$workingRoot'"
        Remove-Item -Path $workingRoot -Recurse -Force -ErrorAction SilentlyContinue
    }
    elseif ($KeepWorkingDirectory.IsPresent -and $workingRoot) {
        Write-Step "Preserving working directory at '$workingRoot'"
    }

    if ($results.Count -gt 0) {
        Write-Host "`nTemplate Validation Summary" -ForegroundColor Green
        $results | Format-Table Template, Platform, Step, Status, Path -AutoSize | Out-String | Write-Host
    }
}

exit $script:exitCode