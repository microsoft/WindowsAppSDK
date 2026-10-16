# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.IO.Compression.FileSystem
Add-Type -AssemblyName System.IO.Compression
$exportScript = Join-Path (Split-Path $PSScriptRoot -Parent) 'Export-InstallerVersionHeader.ps1'

Describe 'Installer version header staging' {
    BeforeEach {
        $testDirectory = Join-Path $TestDrive ([guid]::NewGuid().ToString('N'))
        $source = Join-Path $testDirectory 'source'
        $destination = Join-Path $testDirectory 'destination'
        New-Item -Path $source, $destination -ItemType Directory -Force | Out-Null
        $headerPath = Join-Path $destination 'WindowsAppSDK-VersionInfo.h'
        $headerBytes = [System.Text.Encoding]::UTF8.GetBytes("#define VERSION `"test`"`r`n")
        Mock Start-Sleep {}
    }

    function New-TestNugetPackage {
        param(
            [string]$Name = 'Microsoft.WindowsAppSDK.Runtime.2.6.0-test.nupkg',
            [string]$EntryName = 'include/WindowsAppSDK-VersionInfo.h',
            [byte[]]$Bytes = $headerBytes,
            [switch]$DuplicateHeader
        )

        $path = Join-Path $source $Name
        $archive = [System.IO.Compression.ZipFile]::Open($path, [System.IO.Compression.ZipArchiveMode]::Create)
        try {
            $entry = $archive.CreateEntry($EntryName)
            $stream = $entry.Open()
            try {
                $stream.Write($Bytes, 0, $Bytes.Length)
            }
            finally {
                $stream.Dispose()
            }
            if ($DuplicateHeader) {
                $null = $archive.CreateEntry($EntryName)
            }
            $null = $archive.CreateEntry('_rels/.rels')
            $null = $archive.CreateEntry('tools/MSIX/unused.msix')
        }
        finally {
            $archive.Dispose()
        }
        return $path
    }

    It 'prefers Runtime and copies exact header bytes without extracting other entries or changing the package' {
        $package = New-TestNugetPackage
        $hash = (Get-FileHash -LiteralPath $package).Hash
        New-TestNugetPackage -Name 'Microsoft.WindowsAppSDK.Packages.2.6.0-test.nupkg' -Bytes @(1, 2) | Out-Null
        New-TestNugetPackage -Name 'Microsoft.WindowsAppSDK.2.6.0-test.nupkg' -Bytes @(3, 4) | Out-Null
        [System.IO.File]::WriteAllText($headerPath, 'old header')

        & $exportScript -SourceDirectory $source -DestinationDirectory $destination

        [Convert]::ToBase64String([System.IO.File]::ReadAllBytes($headerPath)) | Should Be ([Convert]::ToBase64String($headerBytes))
        (Get-FileHash -LiteralPath $package).Hash | Should Be $hash
        @(Get-ChildItem -LiteralPath $destination -Force).Count | Should Be 1
    }

    It 'supports the legacy package <Name>' -TestCases @(
        @{ Name = 'Microsoft.WindowsAppSDK.Packages.2.6.0-test.nupkg' },
        @{ Name = 'Microsoft.WindowsAppSDK.2.6.0-test.nupkg' }
    ) {
        param($Name)
        New-TestNugetPackage -Name $Name | Out-Null

        & $exportScript -SourceDirectory $source -DestinationDirectory $destination

        [System.IO.File]::ReadAllText($headerPath) | Should Be ([System.Text.Encoding]::UTF8.GetString($headerBytes))
    }

    It 'rejects ambiguous packages instead of selecting an arbitrary version' {
        New-TestNugetPackage | Out-Null
        New-TestNugetPackage -Name 'Microsoft.WindowsAppSDK.Runtime.2.6.1-test.nupkg' | Out-Null

        { & $exportScript -SourceDirectory $source -DestinationDirectory $destination } | Should Throw 'Expected one'

        Test-Path -LiteralPath $headerPath | Should Be $false
        Assert-MockCalled Start-Sleep -Times 0 -Exactly -Scope It
    }

    It 'rejects a missing runtime package' {
        { & $exportScript -SourceDirectory $source -DestinationDirectory $destination } | Should Throw 'No WindowsAppSDK runtime package'
    }

    It 'rejects a missing, empty, or duplicate header without retrying' -TestCases @(
        @{ EntryName = 'include/Other.h'; Bytes = @(1); DuplicateHeader = $false },
        @{ EntryName = 'include/WindowsAppSDK-VersionInfo.h'; Bytes = @(); DuplicateHeader = $false },
        @{ EntryName = 'include/WindowsAppSDK-VersionInfo.h'; Bytes = @(1); DuplicateHeader = $true }
    ) {
        param($EntryName, $Bytes, $DuplicateHeader)
        New-TestNugetPackage -EntryName $EntryName -Bytes $Bytes -DuplicateHeader:$DuplicateHeader | Out-Null

        { & $exportScript -SourceDirectory $source -DestinationDirectory $destination } | Should Throw 'exactly one non-empty'

        @(Get-ChildItem -LiteralPath $destination -Force).Count | Should Be 0
        Assert-MockCalled Start-Sleep -Times 0 -Exactly -Scope It
    }

    It 'preserves the existing header and original error for a corrupt archive without retrying' {
        [System.IO.File]::WriteAllText((Join-Path $source 'Microsoft.WindowsAppSDK.Runtime.2.6.0-test.nupkg'), 'not a ZIP')
        [System.IO.File]::WriteAllText($headerPath, 'old header')

        { & $exportScript -SourceDirectory $source -DestinationDirectory $destination } | Should Throw 'Central Directory'

        [System.IO.File]::ReadAllText($headerPath) | Should Be 'old header'
        Assert-MockCalled Start-Sleep -Times 0 -Exactly -Scope It
    }

    It 'retries a transient package sharing violation and succeeds after the lock is released' {
        $package = New-TestNugetPackage
        $packageLock = [System.IO.File]::Open($package, 'Open', 'Read', 'None')
        Mock Start-Sleep ({ $packageLock.Dispose() }.GetNewClosure())
        try {
            & $exportScript -SourceDirectory $source -DestinationDirectory $destination

            [System.IO.File]::ReadAllText($headerPath) | Should Be ([System.Text.Encoding]::UTF8.GetString($headerBytes))
            Assert-MockCalled Start-Sleep -Times 1 -Exactly -Scope It
        }
        finally {
            $packageLock.Dispose()
        }
    }

    It 'fails after three locked-destination attempts without replacing the header or leaving partial files' {
        New-TestNugetPackage | Out-Null
        [System.IO.File]::WriteAllText($headerPath, 'old header')
        $lock = [System.IO.File]::Open($headerPath, 'Open', 'Read', 'None')
        try {
            { & $exportScript -SourceDirectory $source -DestinationDirectory $destination } | Should Throw 'being used'
            Assert-MockCalled Start-Sleep -Times 2 -Exactly -Scope It
        }
        finally {
            $lock.Dispose()
        }
        [System.IO.File]::ReadAllText($headerPath) | Should Be 'old header'
        @(Get-ChildItem -LiteralPath $destination -Force).Count | Should Be 1
    }
}
