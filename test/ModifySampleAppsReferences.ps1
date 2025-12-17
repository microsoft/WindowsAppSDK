# This script is a Foundation version of https://github.com/microsoft/WindowsAppSDK-Samples/blob/release/experimental/UpdateVersions.ps1
Param(
    [string]$SampleRepoRoot = "",
    [string]$FoundationVersion = "",
    [string]$FoundationPackagesFolder = "",
    [string]$WASDKNugetDependencies = "" 
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

$packagesToRemoveList = $WASDKNugetDependencies -split ';'
$packagesToRemoveList += @("Microsoft.WindowsAppSDK")

$packagesToUpdateTable = @{"Microsoft.WindowsAppSDK.Foundation" = $FoundationVersion}

# Go through the nuget packages folder to get the versions of all dependency packages.
if (!($FoundationPackagesFolder -eq ""))
{
    Get-ChildItem $FoundationPackagesFolder | 
    Where-Object { $_.Name -like "Microsoft.WindowsAppSDK.*" -or 
                   $_.Name -like "Microsoft.Windows.SDK.BuildTools.*"} | 
    Where-Object { $_.Name -notlike "*.nupkg" } |
    ForEach-Object { 
        if ($_.Name -match "^(Microsoft\.WindowsAppSDK\.[a-zA-Z]+)\.([0-9].*)$" -or
            $_.Name -match "^(Microsoft\.Windows\.SDK\.BuildTools\.MSIX)\.([0-9].*)$" -or
            $_.Name -match "^(Microsoft\.Windows\.SDK\.BuildTools)\.([0-9].*)$")
        {
            $packagesToUpdateTable[$Matches[1]] = $Matches[2]
            Write-Host "Found $($Matches[1]) - $($Matches[2])"

            $packagesToRemoveList = $packagesToRemoveList | Where-Object { $_ -ne $Matches[1] }
        } 
    }
}
Write-Host "NuGet packages to version table: $($packagesToUpdateTable | Out-String)"
Write-Host "NuGet packages to remove: $($packagesToRemoveList | Out-String)"

Get-ChildItem -Recurse Directory.Packages.props -Path $SampleRepoRoot | foreach-object {
    $content = Get-Content $_.FullName -Raw

    foreach ($nugetPackageToVersion in $packagesToUpdateTable.GetEnumerator())
    {
        $newVersionString = 'PackageVersion Include="' + $nugetPackageToVersion.Key + '" Version="' + $nugetPackageToVersion.Value + '"'
        $oldVersionString = 'PackageVersion Include="' + $nugetPackageToVersion.Key + '" Version="[-.0-9a-zA-Z]*"'
        $content = $content -replace $oldVersionString, $newVersionString
    }

    Set-Content -Path $_.FullName -Value $content
    Write-Host "Modified " $_.FullName 
}

Get-ChildItem -Recurse packages.config -Path $SampleRepoRoot | foreach-object {
    $content = Get-Content $_.FullName -Raw

    foreach ($nugetPackageToVersion in $packagesToUpdateTable.GetEnumerator())
    {
        $newVersionString = 'package id="' + $nugetPackageToVersion.Key + '" version="' + $nugetPackageToVersion.Value + '"'
        $oldVersionString = 'package id="' + $nugetPackageToVersion.Key + '" version="[-.0-9a-zA-Z]*"'
        $content = $content -replace $oldVersionString, $newVersionString
    }
    foreach ($package in $packagesToRemoveList)
    {
        $packageReferenceString = '(?m)^\s*<package id="' + $package + '" version="[-.0-9a-zA-Z]*"[^>]*?/>\s*$\r?\n?'
        $content = $content -replace $packageReferenceString, ''
    }

    Set-Content -Path $_.FullName -Value $content
    Write-Host "Modified " $_.FullName 
}

Get-ChildItem -Recurse *.vcxproj -Path $SampleRepoRoot | foreach-object {
    $content = Get-Content $_.FullName -Raw

    foreach ($nugetPackageToVersion in $packagesToUpdateTable.GetEnumerator())
    {
        $newVersionString = "\$($nugetPackageToVersion.Key)." + $nugetPackageToVersion.Value + '\'
        $oldVersionString = "\\$($nugetPackageToVersion.Key).[0-9][-.0-9a-zA-Z]*\\"
        $content = $content -replace $oldVersionString, $newVersionString
    }
    foreach ($package in $packagesToRemoveList)
    {
        $packageReferenceString = "(?m)^.*\\$package\.[0-9][-.0-9a-zA-Z]*\\.*\r?\n?"
        $content = $content -replace $packageReferenceString, ''
    }

    Set-Content -Path $_.FullName -Value $content
    Write-Host "Modified " $_.FullName 
}

Get-ChildItem -Recurse *.wapproj -Path $SampleRepoRoot | foreach-object {
    $newVersionString = 'PackageReference Include="Microsoft.WindowsAppSDK.Foundation" Version="'+ $FoundationVersion + '"'
    $oldVersionString = 'PackageReference Include="Microsoft.WindowsAppSDK" Version="[-.0-9a-zA-Z]*"'
    $content = Get-Content $_.FullName -Raw
    $content = $content -replace $oldVersionString, $newVersionString
    Set-Content -Path $_.FullName -Value $content
    Write-Host "Modified " $_.FullName 
}

Get-ChildItem -Recurse *.csproj -Path $SampleRepoRoot | foreach-object {
    $newVersionString = 'PackageReference Include="Microsoft.WindowsAppSDK.Foundation" Version="'+ $FoundationVersion + '"'
    $oldVersionString = 'PackageReference Include="Microsoft.WindowsAppSDK" Version="[-.0-9a-zA-Z]*"'
    $content = Get-Content $_.FullName -Raw
    $content = $content -replace $oldVersionString, $newVersionString
    Set-Content -Path $_.FullName -Value $content
    Write-Host "Modified " $_.FullName 
}