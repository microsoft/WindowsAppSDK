# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
Validates classic C# VSIX item templates and the standalone CLI template pack.

.DESCRIPTION
Checks that VSIX items use classic templates with explicit XAML build actions,
that CLI-only placeholders cannot leak into their output (#6968), and that the
standalone CLI pack retains its JSON-based item templates.

.PARAMETER VsixPath
Path to a built C# VSIX (LocalDev, Standalone, or Component).

.PARAMETER CliTemplatePackagePath
Path to the standalone, unfiltered template NuGet package.

.EXAMPLE
.\Test-ItemTemplates.ps1 -VsixPath .\CSharp.vsix -CliTemplatePackagePath .\Templates.nupkg
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [string]$VsixPath,

    [Parameter(Mandatory)]
    [string]$CliTemplatePackagePath
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.IO.Compression.FileSystem

function Read-ZipText {
    param(
        [System.IO.Compression.ZipArchive]$Archive,
        [string]$EntryPath
    )

    $entry = $Archive.GetEntry($EntryPath.Replace('\', '/'))
    if ($null -eq $entry) {
        throw "Missing archive entry: $EntryPath"
    }

    $reader = [System.IO.StreamReader]::new($entry.Open())
    try {
        return $reader.ReadToEnd()
    }
    finally {
        $reader.Dispose()
    }
}

$vsix = [System.IO.Compression.ZipFile]::OpenRead((Resolve-Path -LiteralPath $VsixPath).Path)
try {
    $templates = @($vsix.Entries | Where-Object { $_.FullName -match '^ItemTemplates/.*\.vstemplate$' })
    if ($templates.Count -ne 7) {
        throw "Expected seven classic item templates; found $($templates.Count)."
    }
    [xml]$manifest = Read-ZipText $vsix 'extension.vsixmanifest'
    if (@($manifest.PackageManifest.Assets.Asset | Where-Object {
        $_.Type -eq 'Microsoft.VisualStudio.ItemTemplate' -and $_.Path -eq 'ItemTemplates'
    }).Count -ne 1) {
        throw 'The VSIX must register the classic ItemTemplates asset.'
    }

    foreach ($template in $templates) {
        $templateText = Read-ZipText $vsix $template.FullName
        if ($templateText -match 'FIXME-') {
            throw "Unresolved VS package resource registration in $($template.FullName)."
        }
        [xml]$definition = $templateText
        $directory = $template.FullName.Substring(0, $template.FullName.LastIndexOf('/') + 1)
        $iconPath = $directory + $definition.VSTemplate.TemplateData.Icon
        if ($null -eq $vsix.GetEntry($iconPath.Replace('\', '/'))) {
            throw "Missing icon for $($template.FullName)."
        }
        foreach ($item in $definition.VSTemplate.TemplateContent.ProjectItem) {
            $itemPath = $directory + $item.InnerText
            $text = Read-ZipText $vsix $itemPath
            if ($text -match '__WINUI_') {
                throw "CLI-only placeholder leaked into $itemPath (#6968)."
            }
            if ($item.InnerText -like '*.xaml') {
                if ($item.GetAttribute('ItemType') -ne 'Page' -or
                    $item.GetAttribute('CustomTool') -ne 'MSBuild:Compile') {
                    throw "XAML must use the Page build action: $itemPath."
                }
                [xml]$rendered = $text.Replace('$rootnamespace$', 'TestApp.Controls').Replace('$safeitemname$', 'GeneratedItem')
                $expectedType = switch -Wildcard ($item.InnerText) {
                    '*UserControl.xaml' { 'UserControl' }
                    '*ResourceDictionary.xaml' { 'ResourceDictionary' }
                    '*BlankPage.xaml' { 'Page' }
                    '*BlankWindow.xaml' { 'Window' }
                    '*ContentDialog.xaml' { 'ContentDialog' }
                    default { throw "Unexpected XAML item: $itemPath." }
                }
                if ($rendered.DocumentElement.LocalName -ne $expectedType) {
                    throw "Incorrect generated root type in $itemPath."
                }
            }
            if ($item.InnerText -eq 'UserControl.xaml.cs' -and $text -notmatch ': UserControl\b') {
                throw 'The UserControl code-behind must inherit from the literal UserControl type.'
            }
        }
    }

    $embeddedPackage = @($vsix.Entries | Where-Object { $_.FullName -like 'ProjectTemplates/*.nupkg' })
    if ($embeddedPackage.Count -ne 1) {
        throw 'Expected exactly one embedded project-template package.'
    }
    $package = [System.IO.Compression.ZipArchive]::new($embeddedPackage[0].Open())
    try {
        if (@($package.Entries | Where-Object { $_.FullName -match '^content/(item-|reactor-)' }).Count -ne 0) {
            throw 'The VSIX JSON template pack must exclude item and Reactor templates.'
        }
        if ($null -eq $package.GetEntry('content/blank-app/.template.config/template.json')) {
            throw 'The VSIX must retain its JSON project templates.'
        }
    }
    finally {
        $package.Dispose()
    }
}
finally {
    $vsix.Dispose()
}

$cliPackage = [System.IO.Compression.ZipFile]::OpenRead((Resolve-Path -LiteralPath $CliTemplatePackagePath).Path)
try {
    if (@($cliPackage.Entries | Where-Object { $_.FullName -like '*.vstemplate' }).Count -ne 0) {
        throw 'Classic VS metadata must not be included in the standalone CLI pack.'
    }
    $cliItems = @($cliPackage.Entries | Where-Object { $_.FullName -match '^content/item-[^/]+/\.template.config/template\.json$' })
    if ($cliItems.Count -ne 7) {
        throw 'The standalone CLI pack must retain all seven JSON item templates.'
    }
}
finally {
    $cliPackage.Dispose()
}

Write-Host 'C# VSIX and CLI item-template checks passed.'
exit 0
