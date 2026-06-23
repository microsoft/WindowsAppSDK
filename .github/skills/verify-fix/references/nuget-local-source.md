# Local NuGet Source Configuration for Verification Apps

When the Windows App SDK is built locally via `BuildAll.ps1`, the output NuGet packages land in `BuildOutput/` at the repo root. Verification apps must reference these local packages instead of published ones from nuget.org.

## Package Location

After a successful build, you will find:

```
BuildOutput/
├── Microsoft.WindowsAppSDK.Foundation.{version}.nupkg
├── Microsoft.WindowsAppSDK.Foundation.TransportPackage.{version}.nupkg
└── ...
```

The **Foundation** package is the one WinUI 3 apps consume. The version comes from `eng/Version.Details.xml` and `SdkVersion.props`.

## Extracting the Version

```powershell
# From the .nupkg filename
$pkg = Get-ChildItem "$repoRoot\BuildOutput\Microsoft.WindowsAppSDK.Foundation.*.nupkg" |
    Where-Object { $_.Name -notmatch 'TransportPackage' } |
    Sort-Object LastWriteTime -Descending |
    Select-Object -First 1

$version = $pkg.BaseName -replace '^Microsoft\.WindowsAppSDK\.Foundation\.', ''
Write-Host "SDK Version: $version"
```

## nuget.config Setup

Place this file in the **solution root** of the verification app (same directory as `.sln`):

```xml
<?xml version="1.0" encoding="utf-8"?>
<configuration>
  <packageSources>
    <!-- Clear all inherited sources so we control exactly where packages come from -->
    <clear />
    <!-- Local SDK build output — checked FIRST -->
    <add key="LocalSDKBuild" value="C:\WindowsAppSDK\BuildOutput" />
    <!-- Fallback to nuget.org for non-SDK packages (e.g., CommunityToolkit, etc.) -->
    <add key="nuget.org" value="https://api.nuget.org/v3/index.json" />
  </packageSources>
</configuration>
```

### Why `<clear />`?

Without `<clear />`, NuGet will also search the global package cache and any machine-level `nuget.config` sources. This can cause it to resolve a *published* version of `Microsoft.WindowsAppSDK` instead of the locally built one. Always clear first.

## .csproj PackageReference

Pin the exact version in the project file:

```xml
<ItemGroup>
  <PackageReference Include="Microsoft.WindowsAppSDK" Version="1.8.0" />
</ItemGroup>
```

Do **not** use version ranges (`[1.8.0, )`) or floating versions (`1.8.*`).

## Verifying the Correct Package Is Used

After `dotnet restore`, check which package was resolved:

```powershell
# Check the assets file
$assetsFile = "app\obj\project.assets.json"
$assets = Get-Content $assetsFile -Raw | ConvertFrom-Json
$sdkPkg = $assets.libraries.PSObject.Properties |
    Where-Object { $_.Name -match 'Microsoft.WindowsAppSDK' } |
    Select-Object -First 1
Write-Host "Resolved: $($sdkPkg.Name) from $($sdkPkg.Value.path)"
```

Or check the NuGet cache:

```powershell
dotnet nuget locals global-packages --list
# Then look for: Microsoft.WindowsAppSDK/{version}
```

## Common Issues

| Issue | Cause | Fix |
|-------|-------|-----|
| `NU1101: Unable to find package` | Path in nuget.config is wrong or relative | Use absolute path to `BuildOutput/` |
| Old version resolved | Global cache has a cached version | Run `dotnet nuget locals all --clear` |
| Foundation package not found | Build didn't produce `.nupkg` | Re-run `BuildAll.ps1` and check exit code |
| `NETSDK1147` error | Missing Windows SDK targeting pack | Install Windows SDK 10.0.19041.0+ via VS Installer |
