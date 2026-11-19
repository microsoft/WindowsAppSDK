# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

[CmdletBinding()]
param()

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

$resourceCompiler = Get-Command rc.exe -ErrorAction Stop
$linker = Get-Command link.exe -ErrorAction Stop
$repoRoot = [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$template = Get-Content -LiteralPath (Join-Path $repoRoot 'build\AzurePipelinesTemplates\WindowsAppSDK-BuildInstaller-Steps.yml') -Raw
$generation = $template.IndexOf('name: GenerateInstallerVersionInfo', [System.StringComparison]::Ordinal)
$build = $template.IndexOf("displayName: 'Build Windows App Runtime Install'", [System.StringComparison]::Ordinal)
if ($generation -lt 0 -or $build -lt $generation)
{
    throw 'The installer pipeline must generate version resources before compiling the installer.'
}
$mapsBinaryVersion = $template.Substring($generation, $build - $generation) -match '(?m)^\s+WindowsAppSDKBinaryVersion:\s*\$\(WindowsAppSDKBinaryVersion\)\s*$'

$testRoot = Join-Path ([System.IO.Path]::GetTempPath()) ('InstallerVersionInfo-' + [guid]::NewGuid().ToString('N'))
$originalBinaryVersion = $env:WindowsAppSDKBinaryVersion
try
{
    $versionDirectory = Join-Path $testRoot 'build\VersionInfo'
    [System.IO.Directory]::CreateDirectory($versionDirectory) | Out-Null
    Copy-Item -LiteralPath (Join-Path $PSScriptRoot 'GenerateVersionInfo.ps1') -Destination $versionDirectory
    Copy-Item -LiteralPath (Join-Path $repoRoot 'installer\dev\WindowsAppRuntimeInstall.rc') -Destination $testRoot
    foreach ($header in @('resource.h', 'windowsappruntime_definitions.h'))
    {
        [System.IO.File]::WriteAllText((Join-Path $testRoot $header), '')
    }
    [System.IO.File]::WriteAllLines((Join-Path $testRoot 'WindowsAppSDK-VersionInfo.h'), @(
        '#define WINDOWSAPPSDK_RELEASE_MAJOR 2',
        '#define WINDOWSAPPSDK_RELEASE_MINOR 7'
    ))

    foreach ($version in @('102.7.3.41', '102.7.3.0', '65535.65535.65535.65535', ''))
    {
        $env:WINDOWSAPPSDKBINARYVERSION = if ($version) { $version } else { $null }
        if (-not $version -and $mapsBinaryVersion)
        {
            # Azure Pipelines leaves an explicit mapping's undefined macro unexpanded.
            $env:WindowsAppSDKBinaryVersion = '$(WindowsAppSDKBinaryVersion)'
        }
        & (Join-Path $versionDirectory 'GenerateVersionInfo.ps1') -ProductMajor 2 -ProductMinor 7
        $resource = Join-Path $testRoot 'Installer.res'
        $binary = Join-Path $testRoot 'Installer.exe'
        & $resourceCompiler.Source /nologo /i $testRoot /fo $resource (Join-Path $testRoot 'WindowsAppRuntimeInstall.rc')
        if ($LASTEXITCODE -ne 0)
        {
            throw 'Installer resource compilation failed.'
        }
        & $linker.Source /nologo /dll /noentry /machine:x64 "/out:$binary" $resource
        if ($LASTEXITCODE -ne 0)
        {
            throw 'Installer resource linking failed.'
        }

        $info = [System.Diagnostics.FileVersionInfo]::GetVersionInfo($binary)
        $actual = @(
            (@($info.FileMajorPart, $info.FileMinorPart, $info.FileBuildPart, $info.FilePrivatePart) -join '.'),
            $info.FileVersion,
            (@($info.ProductMajorPart, $info.ProductMinorPart, $info.ProductBuildPart, $info.ProductPrivatePart) -join '.'),
            $info.ProductVersion
        )
        $expected = if ($version) { @($version, $version, $version, $version) } else { @('2.7.0.0', '2.7', '2.7.0.0', '2.7') }
        for ($index = 0; $index -lt $expected.Count; $index++)
        {
            if ($actual[$index] -cne $expected[$index])
            {
                throw "Installer version field $index is '$($actual[$index])'; expected '$($expected[$index])'."
            }
        }
        $assemblyInfo = Get-Content -LiteralPath (Join-Path $versionDirectory 'AssemblyInfo.cs') -Raw
        if (-not $assemblyInfo.Contains('[assembly: AssemblyVersion("2.7")]'))
        {
            throw 'Generating native installer versions changed the managed assembly identity.'
        }
        Write-Output "PASS: installer fixed/string versions for '$version'."
    }

    foreach ($version in @('102.7.3', '102.7.3.65536', '$(WindowsAppSDKBinaryVersion)'))
    {
        $env:WINDOWSAPPSDKBINARYVERSION = $version
        $rejection = $null
        try
        {
            & (Join-Path $versionDirectory 'GenerateVersionInfo.ps1') -ProductMajor 2 -ProductMinor 7
        }
        catch
        {
            $rejection = $_.Exception.Message
        }
        if (-not $rejection -or $rejection -notmatch 'WindowsAppSDKBinaryVersion')
        {
            throw "Invalid binary version '$version' was not rejected by version validation."
        }
        Write-Output "PASS: rejected invalid binary version '$version'."
    }
}
finally
{
    $env:WindowsAppSDKBinaryVersion = $originalBinaryVersion
    if (Test-Path -LiteralPath $testRoot)
    {
        Remove-Item -LiteralPath $testRoot -Recurse -Force
    }
}

Write-Output 'Installer version-info tests passed.'
return 0
