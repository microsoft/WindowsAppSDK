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
        $packageId = $nugetPackageToVersion.Key
        $packageVersion = $nugetPackageToVersion.Value
        $newVersionString = 'PackageVersion Include="' + $packageId + '" Version="' + $packageVersion + '"'
        $oldVersionPattern = 'PackageVersion Include="' + [regex]::Escape($packageId) + '" Version="[-.0-9a-zA-Z]*"'

        if ($content -match $oldVersionPattern)
        {
            $content = $content -replace $oldVersionPattern, $newVersionString
        }
        else
        {
            # Missing entry: insert into the first ItemGroup. Ensures transitive
            # Foundation dependencies (e.g. Microsoft.WindowsAppSDK.Base) get a
            # centrally-managed PackageVersion matching Foundation; otherwise NuGet
            # sees a downgrade and SamplesCompatTest fails with NU1605.
            $insertion = "`r`n    <" + $newVersionString + ' />'
            $content = [regex]::Replace($content, '(<ItemGroup[^>]*>)', '$1' + $insertion, 1)
            Write-Host "Inserted PackageVersion for $packageId ($packageVersion) into $($_.FullName)"
        }
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

$projectFileExtensions = @("*.vcxproj", "*.wapproj", "*.csproj")
$newPackageReference = 'PackageReference Include="Microsoft.WindowsAppSDK.Foundation"'
$oldPackageReference = 'PackageReference Include="Microsoft\.WindowsAppSDK"'
foreach ($extension in $projectFileExtensions) {
    Get-ChildItem -Recurse $extension -Path $SampleRepoRoot | foreach-object {
        $content = Get-Content $_.FullName -Raw
        $content = $content -replace $oldPackageReference, $newPackageReference
        Set-Content -Path $_.FullName -Value $content
        Write-Host "Modified " $_.FullName 
    }
}