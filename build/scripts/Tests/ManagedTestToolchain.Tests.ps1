# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'
$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot '..\..\..')).Path
[xml]$versions = Get-Content (Join-Path $repoRoot 'Directory.Packages.props')
$toolchain = $versions.Project.PropertyGroup | Where-Object { $_.GetAttribute('Label') -eq 'CsWinRT Toolchain' }

Describe 'Managed test toolchain' {
    It 'keeps the bootstrap SDK and pipeline install aligned with the MRT SDK' {
        $sdkVersion = $toolchain.CsWinRTDependencyDotNetCoreSdkPackageVersion
        $globalJson = Get-Content (Join-Path $repoRoot 'global.json') -Raw | ConvertFrom-Json
        $globalJson.tools.dotnet | Should Be $sdkVersion
        $setup = Get-Content (Join-Path $repoRoot 'build\AzurePipelinesTemplates\WindowsAppSDK-SetupBuildEnvironment-Steps.yml') -Raw
        $setup | Should Match ('(?m)^\s+version: ' + [regex]::Escape($sdkVersion) + '\s*$')
    }

    It 'reads the default MRT SDK version without an explicit version argument' {
        $previousAgentDirectory = $env:AGENT_BUILDDIRECTORY
        $previousSecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol
        $env:AGENT_BUILDDIRECTORY = $TestDrive
        Mock Invoke-Expression {
            "$($toolchain.CsWinRTDependencyDotNetCoreSdkPackageVersion) [C:\Program Files\dotnet\sdk]"
        }
        Mock Invoke-WebRequest {}
        try {
            & (Join-Path $repoRoot 'dev\MRTCore\build\DownloadDotNetCoreSdk.ps1')
        }
        finally {
            $env:AGENT_BUILDDIRECTORY = $previousAgentDirectory
            [System.Net.ServicePointManager]::SecurityProtocol = $previousSecurityProtocol
        }
        Assert-MockCalled Invoke-Expression -Times 2 -Exactly
    }

    It 'targets the supported test framework without changing production projections' {
        foreach ($project in @(
            'test\WindowsAppSDK.Test.NetCore\WindowsAppSDK.Test.NetCore.csproj',
            'test\WindowsAppSDK.Test.SampleTests\WindowsAppSDK.Test.SampleTests.csproj',
            'dev\MRTCore\mrt\Microsoft.Windows.ApplicationModel.Resources\CsWinRTTests\MrtCoreCsWinRTTests.csproj'
        )) {
            [xml]$xml = Get-Content (Join-Path $repoRoot $project)
            $xml.SelectSingleNode('//*[local-name()="TargetFramework"]').InnerText | Should Match '^net10\.0($|-)'
        }
        $projection = 'dev\MRTCore\mrt\Microsoft.Windows.ApplicationModel.Resources\projection\Microsoft.Windows.ApplicationModel.Resources.Projection.csproj'
        [xml]$xml = Get-Content (Join-Path $repoRoot $projection)
        $xml.SelectSingleNode('//*[local-name()="TargetFramework"]').InnerText | Should Be 'net6.0-windows10.0.17763.0'
    }

    It 'resolves a self-contained portable runtime for <Platform> in <Configuration>' -TestCases @(
        @{ Platform = 'x86'; Configuration = 'Debug'; Rid = 'win-x86' },
        @{ Platform = 'x86'; Configuration = 'Release'; Rid = 'win-x86' },
        @{ Platform = 'x64'; Configuration = 'Debug'; Rid = 'win-x64' },
        @{ Platform = 'x64'; Configuration = 'Release'; Rid = 'win-x64' },
        @{ Platform = 'arm64'; Configuration = 'Debug'; Rid = 'win-arm64' },
        @{ Platform = 'arm64'; Configuration = 'Release'; Rid = 'win-arm64' },
        @{ Platform = 'arm64ec'; Configuration = 'Release'; Rid = 'win-arm64' },
        @{ Platform = 'AnyCPU'; Configuration = 'Release'; Rid = 'win-x86' }
    ) {
        param($Platform, $Configuration, $Rid)
        foreach ($project in @(
            'test\WindowsAppSDK.Test.NetCore\WindowsAppSDK.Test.NetCore.csproj',
            'dev\MRTCore\mrt\Microsoft.Windows.ApplicationModel.Resources\CsWinRTTests\MrtCoreCsWinRTTests.csproj'
        )) {
            $output = & dotnet msbuild (Join-Path $repoRoot $project) -nologo "-p:Platform=$Platform" "-p:Configuration=$Configuration" -getProperty:RuntimeIdentifier,SelfContained,RuntimeFrameworkVersion
            $LASTEXITCODE | Should Be 0
            # Existing repository import warnings can precede the JSON result.
            $text = $output -join "`n"
            $text.IndexOf('{') | Should Not Be -1
            $result = $text.Substring($text.IndexOf('{')) | ConvertFrom-Json
            $result.Properties.RuntimeIdentifier | Should Be $Rid
            $result.Properties.SelfContained | Should Be 'true'
            $result.Properties.RuntimeFrameworkVersion | Should Be $toolchain.CsWinRTDependencyDotNetCoreRuntimePackageVersion
        }
    }

    It 'keeps the test host, runtime-pack destination and runner copy on the same profile' {
        foreach ($assembly in @(
            'test\WindowsAppSDK.Test.SampleTests\TestAssembly.cs',
            'dev\MRTCore\mrt\Microsoft.Windows.ApplicationModel.Resources\CsWinRTTests\TestAssembly.cs'
        )) {
            Get-Content (Join-Path $repoRoot $assembly) -Raw | Should Match '"CoreClrProfile", "net10"'
        }
        $mrtProject = 'dev\MRTCore\mrt\Microsoft.Windows.ApplicationModel.Resources\CsWinRTTests\MrtCoreCsWinRTTests.csproj'
        Get-Content (Join-Path $repoRoot $mrtProject) -Raw | Should Match 'DestinationFolder="\$\(OutDir\)\\net10"'
        $runner = Get-Content (Join-Path $repoRoot 'build\AzurePipelinesTemplates\WindowsAppSDK-RunTests-Steps.yml') -Raw
        $runner | Should Match 'WindowsAppSDK.Test.NetCore\\net10'
        $runner | Should Match 'WindowsAppSDK.Test.SampleTests\\net10'
        $runner | Should Not Match '\\net6'
    }
}
