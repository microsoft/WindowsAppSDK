<#
.SYNOPSIS
    Creates a WinUI 3 verification app that references the locally built SDK NuGet package.

.DESCRIPTION
    Scaffolds a minimal WinUI 3 C# app in Generated Files/verifyFix/<IssueNumber>/app/
    and configures it to consume the local BuildOutput .nupkg. Intended for developers
    to manually verify that a fix works end-to-end.

.PARAMETER IssueNumber
    The GitHub issue number this verification app targets.

.PARAMETER RepoRoot
    Path to the Windows App SDK repo root. Defaults to the repo root detected from
    the script location.

.PARAMETER Force
    Skip confirmation prompts.

.EXAMPLE
    .\New-VerificationApp.ps1 -IssueNumber 6075
    .\New-VerificationApp.ps1 -IssueNumber 6075 -RepoRoot C:\WindowsAppSDK -Force
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [int]$IssueNumber,

    [Parameter()]
    [string]$RepoRoot,

    [Parameter()]
    [switch]$Force
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

# Resolve repo root
if (-not $RepoRoot) {
    $RepoRoot = (Get-Item "$PSScriptRoot\..\..\..\..\").FullName.TrimEnd('\')
}

$buildOutput = Join-Path $RepoRoot 'BuildOutput'
$appName = "VerifyFix${IssueNumber}App"
$outputBase = Join-Path $RepoRoot "Generated Files" "verifyFix" "$IssueNumber"
$appDir = Join-Path $outputBase 'app'
$signalPath = Join-Path $outputBase '.signal'

Write-Host "=== New-VerificationApp ===" -ForegroundColor Cyan
Write-Host "  Issue:       #$IssueNumber"
Write-Host "  App Name:    $appName"
Write-Host "  Output:      $appDir"
Write-Host "  BuildOutput: $buildOutput"

# --- Step 1: Find the .nupkg ---
$foundationPkg = Get-ChildItem "$buildOutput\Microsoft.WindowsAppSDK.Foundation.*.nupkg" -ErrorAction SilentlyContinue |
    Where-Object { $_.Name -notmatch 'TransportPackage' } |
    Sort-Object LastWriteTime -Descending |
    Select-Object -First 1

if (-not $foundationPkg) {
    $signal = @{
        status      = 'failure'
        issueNumber = $IssueNumber
        reason      = "No Microsoft.WindowsAppSDK.Foundation.*.nupkg found in $buildOutput"
        timestamp   = (Get-Date -Format 'o')
    }
    New-Item -Path $outputBase -ItemType Directory -Force | Out-Null
    $signal | ConvertTo-Json -Depth 5 | Set-Content -Path $signalPath -Encoding utf8
    Write-Error $signal.reason
    exit 1
}

$version = $foundationPkg.BaseName -replace '^Microsoft\.WindowsAppSDK\.Foundation\.', ''
Write-Host "  SDK Version: $version" -ForegroundColor Green

# --- Step 2: Scaffold the app directory ---
if (Test-Path $appDir) {
    if ($Force) {
        Remove-Item $appDir -Recurse -Force
    }
    else {
        $answer = Read-Host "App directory exists. Overwrite? [y/N]"
        if ($answer -ne 'y') { exit 0 }
        Remove-Item $appDir -Recurse -Force
    }
}

New-Item -Path $appDir -ItemType Directory -Force | Out-Null

# --- Step 3: nuget.config ---
$nugetConfig = @"
<?xml version="1.0" encoding="utf-8"?>
<configuration>
  <packageSources>
    <clear />
    <add key="LocalSDKBuild" value="$buildOutput" />
    <add key="nuget.org" value="https://api.nuget.org/v3/index.json" />
  </packageSources>
</configuration>
"@
Set-Content -Path (Join-Path $appDir 'nuget.config') -Value $nugetConfig -Encoding utf8

# --- Step 4: .csproj ---
$csproj = @"
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <OutputType>WinExe</OutputType>
    <TargetFramework>net8.0-windows10.0.19041.0</TargetFramework>
    <TargetPlatformMinVersion>10.0.17763.0</TargetPlatformMinVersion>
    <RootNamespace>$appName</RootNamespace>
    <ApplicationManifest>app.manifest</ApplicationManifest>
    <Platforms>x86;x64;ARM64</Platforms>
    <RuntimeIdentifiers>win-x86;win-x64;win-arm64</RuntimeIdentifiers>
    <UseWinUI>true</UseWinUI>
    <WindowsPackageType>None</WindowsPackageType>
  </PropertyGroup>
  <ItemGroup>
    <PackageReference Include="Microsoft.WindowsAppSDK" Version="$version" />
    <PackageReference Include="Microsoft.Windows.SDK.BuildTools" Version="10.0.26100.1742" />
  </ItemGroup>
</Project>
"@
Set-Content -Path (Join-Path $appDir "$appName.csproj") -Value $csproj -Encoding utf8

# --- Step 5: app.manifest ---
$appManifest = @"
<?xml version="1.0" encoding="utf-8"?>
<assembly manifestVersion="1.0" xmlns="urn:schemas-microsoft-com:asm.v1">
  <assemblyIdentity version="1.0.0.0" name="$appName" />
  <compatibility xmlns="urn:schemas-microsoft-com:compatibility.v1">
    <application>
      <supportedOS Id="{8e0f7a12-bfb3-4fe8-b9a5-48fd50a15a9a}" />
    </application>
  </compatibility>
</assembly>
"@
Set-Content -Path (Join-Path $appDir 'app.manifest') -Value $appManifest -Encoding utf8

# --- Step 6: App.xaml ---
$appXaml = @"
<Application
    x:Class="$appName.App"
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml">
</Application>
"@
Set-Content -Path (Join-Path $appDir 'App.xaml') -Value $appXaml -Encoding utf8

# --- Step 7: App.xaml.cs ---
$appXamlCs = @"
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

using Microsoft.UI.Xaml;

namespace $appName;

public partial class App : Application
{
    public App()
    {
        this.InitializeComponent();
    }

    protected override void OnLaunched(LaunchActivatedEventArgs args)
    {
        m_window = new MainWindow();
        m_window.Activate();
    }

    private Window m_window;
}
"@
Set-Content -Path (Join-Path $appDir 'App.xaml.cs') -Value $appXamlCs -Encoding utf8

# --- Step 8: MainWindow.xaml ---
$mainXaml = @"
<Window
    x:Class="$appName.MainWindow"
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
    Title="Verify Fix #$IssueNumber">

    <StackPanel HorizontalAlignment="Center" VerticalAlignment="Center" Spacing="16">
        <TextBlock x:Name="StatusText"
                   Text="Verification app for issue #$IssueNumber"
                   FontSize="20"
                   HorizontalAlignment="Center" />
        <Button x:Name="VerifyButton" Content="Run Verification" Click="VerifyButton_Click"
                HorizontalAlignment="Center" />
        <TextBlock x:Name="ResultText" TextWrapping="Wrap" MaxWidth="600" />
    </StackPanel>
</Window>
"@
Set-Content -Path (Join-Path $appDir 'MainWindow.xaml') -Value $mainXaml -Encoding utf8

# --- Step 9: MainWindow.xaml.cs ---
$mainCs = @"
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

using Microsoft.UI.Xaml;

namespace $appName;

public sealed partial class MainWindow : Window
{
    public MainWindow()
    {
        this.InitializeComponent();
    }

    private void VerifyButton_Click(object sender, RoutedEventArgs e)
    {
        // TODO: Add verification code for issue #$IssueNumber here.
        // The VerifyFix agent will replace this with actual verification logic.
        ResultText.Text = "Verification logic not yet implemented. " +
            "The VerifyFix agent should add issue-specific code here.";
    }
}
"@
Set-Content -Path (Join-Path $appDir 'MainWindow.xaml.cs') -Value $mainCs -Encoding utf8

# --- Step 10: README ---
$readme = @"
# Verification App for Issue #$IssueNumber

This app was auto-generated to verify the fix for
[issue #$IssueNumber](https://github.com/microsoft/WindowsAppSDK/issues/$IssueNumber).

## SDK Package

- **Package**: ``Microsoft.WindowsAppSDK.Foundation.$version.nupkg``
- **Source**: ``$buildOutput``

## How to Run

``````powershell
cd `"$appDir`"
dotnet build -c Debug
dotnet run -c Debug
``````

## What It Verifies

See ``MainWindow.xaml.cs`` for the verification logic.
"@
Set-Content -Path (Join-Path $appDir 'README.md') -Value $readme -Encoding utf8

Write-Host "`nApp scaffolded at: $appDir" -ForegroundColor Green
Write-Host "Next: Add verification code to MainWindow.xaml.cs, then build." -ForegroundColor Yellow
