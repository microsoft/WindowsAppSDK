# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.IO.Compression.FileSystem
Add-Type -AssemblyName System.IO.Compression
$extractScript = Join-Path (Split-Path $PSScriptRoot -Parent) 'ExtractMSIXFromNuget.ps1'

Describe 'Installer MSIX extraction' {
    BeforeEach {
        $testDirectory = Join-Path $TestDrive ([guid]::NewGuid().ToString('N'))
        $artifacts = Join-Path $testDirectory 'artifacts'
        $source = Join-Path $artifacts 'NugetPackages'
        $destination = Join-Path $testDirectory 'InstallerInput'
        $workingDirectory = Join-Path $testDirectory 'work'
        New-Item -Path $source, $workingDirectory -ItemType Directory -Force | Out-Null
        Mock Start-Sleep {}
    }

    function New-TestNugetPackage {
        param(
            [string]$Name = 'Microsoft.WindowsAppSDK.Runtime.2.7.0-test.nupkg',
            [hashtable]$Entries = (Get-RuntimeEntries)
        )

        $path = Join-Path $source $Name
        $archive = [System.IO.Compression.ZipFile]::Open($path, [System.IO.Compression.ZipArchiveMode]::Create)
        try {
            $null = $archive.CreateEntry('_rels/.rels')
            $null = $archive.CreateEntry('[Content_Types].xml')
            foreach ($entryName in $Entries.Keys) {
                $bytes = [System.Text.Encoding]::UTF8.GetBytes($Entries[$entryName])
                $stream = $archive.CreateEntry($entryName).Open()
                try {
                    $stream.Write($bytes, 0, $bytes.Length)
                }
                finally {
                    $stream.Dispose()
                }
            }
        }
        finally {
            $archive.Dispose()
        }
        return $path
    }

    # The Runtime package's layout: one framework, main, singleton and DDLM package per architecture.
    # Each entry's content is the installer input name it should be extracted to.
    function Get-RuntimeEntries {
        $entries = @{ 'tools/MSIX/win10-x64/Microsoft.WindowsAppRuntime.2-test.msix.sha256' = 'unused' }
        foreach ($architecture in 'x86', 'x64', 'arm64') {
            $entries["tools/MSIX/win10-$architecture/Microsoft.WindowsAppRuntime.2-test.msix"] = "framework_$architecture"
            $entries["tools/MSIX/win10-$architecture/Microsoft.WindowsAppRuntime.Main.2-test.msix"] = "main_$architecture"
            $entries["tools/MSIX/win10-$architecture/Microsoft.WindowsAppRuntime.Singleton.2-test.msix"] = "singleton_$architecture"
            $entries["tools/MSIX/win10-$architecture/Microsoft.WindowsAppRuntime.DDLM.2-test.msix"] = "ddlm_$architecture"
        }
        return $entries
    }

    function Assert-InstallerInputs([string]$Directory) {
        $expected = @(foreach ($kind in 'framework', 'main', 'singleton', 'ddlm') {
                foreach ($architecture in 'x86', 'x64', 'arm64') {
                    "${kind}_$architecture"
                }
            })
        @(Get-ChildItem -LiteralPath $Directory | Sort-Object Name | ForEach-Object { $_.Name }) -join ',' |
            Should Be (@($expected | Sort-Object | ForEach-Object { "$_.msix" }) -join ',')
        foreach ($name in $expected) {
            [System.IO.File]::ReadAllText((Join-Path $Directory "$name.msix")) | Should Be $name
        }
    }

    It 'extracts each architecture''s packages from the Runtime package without writing anything else' {
        New-TestNugetPackage -Name 'Microsoft.WindowsAppSDK.2.7.0-test.nupkg' -Entries @{ 'build/Microsoft.WindowsAppSDK.props' = '<Project />' } | Out-Null
        $runtime = New-TestNugetPackage
        $hash = (Get-FileHash -LiteralPath $runtime).Hash

        Push-Location -LiteralPath $workingDirectory
        try {
            & $extractScript -Source $artifacts -Dest $destination
        }
        finally {
            Pop-Location
        }

        Assert-InstallerInputs $destination
        (Get-FileHash -LiteralPath $runtime).Hash | Should Be $hash
        @(Get-ChildItem -LiteralPath $workingDirectory -Force).Count | Should Be 0
        Assert-MockCalled Start-Sleep -Times 0 -Exactly -Scope It
    }

    It 'extracts <Entry> as <Expected>' -TestCases @(
        @{ Entry = 'tools/MSIX/win10-x64/Microsoft.WindowsAppRuntime.1.8.msix'; Expected = 'framework_x64.msix' },
        @{ Entry = 'tools/MSIX/win10-arm64/Microsoft.WindowsAppRuntime.Main.1.8-preview1.msix'; Expected = 'main_arm64.msix' },
        @{ Entry = 'tools/MSIX/win10-x86/Microsoft.WindowsAppRuntime.Singleton.2-experimental0.appx'; Expected = 'singleton_x86.msix' },
        @{ Entry = 'tools/MSIX/win10-x64/Microsoft.WindowsAppRuntime.DDLM.1.8.msix'; Expected = 'ddlm_x64.msix' }
    ) {
        param($Entry, $Expected)
        New-TestNugetPackage -Entries @{ $Entry = 'package' } | Out-Null

        & $extractScript -Source $artifacts -Dest $destination

        @(Get-ChildItem -LiteralPath $destination | ForEach-Object { $_.Name }) -join ',' | Should Be $Expected
    }

    It 'ignores <Entry>' -TestCases @(
        @{ Entry = 'tools/MSIX/win10-x64/Microsoft.WindowsAppRuntime.Insights.Resource.2.msix' },
        @{ Entry = 'tools/Microsoft.WindowsAppRuntime.2.msix' }
    ) {
        param($Entry)
        New-TestNugetPackage -Entries @{ $Entry = 'package' } | Out-Null

        & $extractScript -Source $artifacts -Dest $destination

        @(Get-ChildItem -LiteralPath $destination).Count | Should Be 0
    }

    It 'never writes the package entries it does not need' {
        # These two entries can't both be written to disk, because the second needs 'conflict' to be a directory.
        # Expanding the whole package failed on them. In the pipeline, Expand-Archive's cleanup then failed too, with
        # PathNotFound on _rels\.rels, which hid the original error.
        $entries = Get-RuntimeEntries
        $entries['content/conflict'] = 'file'
        $entries['content/conflict/file.txt'] = 'file in a directory'
        New-TestNugetPackage -Entries $entries | Out-Null

        & $extractScript -Source $artifacts -Dest $destination

        Assert-InstallerInputs $destination
    }

    It 'replaces existing installer inputs' {
        New-TestNugetPackage | Out-Null
        New-Item -Path $destination -ItemType Directory | Out-Null
        [System.IO.File]::WriteAllText((Join-Path $destination 'framework_x64.msix'), 'old package')

        & $extractScript -Source $artifacts -Dest $destination

        Assert-InstallerInputs $destination
    }

    It 'resolves a relative destination against the PowerShell location' {
        New-TestNugetPackage | Out-Null

        Push-Location -LiteralPath $workingDirectory
        try {
            & $extractScript -Source $artifacts -Dest 'InstallerInput'
        }
        finally {
            Pop-Location
        }

        Assert-InstallerInputs (Join-Path $workingDirectory 'InstallerInput')
    }

    It 'retries a sharing violation and succeeds after the lock is released' {
        New-TestNugetPackage | Out-Null
        New-Item -Path $destination -ItemType Directory | Out-Null
        $lock = [System.IO.File]::Open((Join-Path $destination 'framework_x64.msix'), 'Create', 'ReadWrite', 'None')
        Mock Start-Sleep ({ $lock.Dispose() }.GetNewClosure())
        try {
            & $extractScript -Source $artifacts -Dest $destination

            Assert-InstallerInputs $destination
            Assert-MockCalled Start-Sleep -Times 1 -Exactly -Scope It
        }
        finally {
            $lock.Dispose()
        }
    }

    It 'fails with the original error after three attempts while the lock is held' {
        New-TestNugetPackage | Out-Null
        New-Item -Path $destination -ItemType Directory | Out-Null
        $lock = [System.IO.File]::Open((Join-Path $destination 'framework_x64.msix'), 'Create', 'ReadWrite', 'None')
        try {
            { & $extractScript -Source $artifacts -Dest $destination } | Should Throw 'being used'
            Assert-MockCalled Start-Sleep -Times 2 -Exactly -Scope It
        }
        finally {
            $lock.Dispose()
        }
    }

    It 'fails at once with the original error for a corrupt package' {
        [System.IO.File]::WriteAllText((Join-Path $source 'Microsoft.WindowsAppSDK.Runtime.2.7.0-test.nupkg'), 'not a ZIP')

        { & $extractScript -Source $artifacts -Dest $destination } | Should Throw 'Central Directory'

        Assert-MockCalled Start-Sleep -Times 0 -Exactly -Scope It
    }
}
