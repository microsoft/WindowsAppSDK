# Producing the Projection Headers

## Acquire Tooling

Start by creating a temporary location to work:

```pwsh
$working_dir = Join-Path $env:temp wasdk_inc
Remove-Item -Force -Recurse $working_dir
mkdir -force -ErrorAction SilentlyContinue $working_dir
nuget install Microsoft.Windows.AbiWinRT -OutputDirectory $working_dir\packages
```

Install a Windows Platform SDK if you don't have one already:

```pwsh
winget install Microsoft.WindowsSDK.10.0.26100
```

## Acquire metadata from latest release

Check [the NuGet package release list](https://nuget.info/packages/Microsoft.WindowsAppSDK) to find
the latest packages (including preview and experimental).  Note their version number. In this example,
we'll be using [Microsoft.WindowsAppSDK.ML version 1.8.126-experimental](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.ML/1.8.126-experimental)

Fetch the package from nuget:

```pwsh
nuget install Microsoft.WindowsAppSDK.ML -Version 1.8.126-experimental -OutputDirectory $working_dir\packages
```

## Generate Projections

This example generates the projections from the `Microsoft.WindowsAppSDK.ML` package.

```pwsh
# Run these in the root directory of the repo
$abiwinrt = gci -r $working_dir\packages\*abi*\abi.exe
$metadata = gci -r $working_dir\packages\microsoft.windowsappsdk.ml*\metadata
& $abiwinrt -input $metadata -reference sdk -output inc/abi/winml -lowercase-include-guard -ns-prefix always
```

## Commit changes

Create or switch to the release branch for the output artifacts, then commit the changes

```pwsh
# Run these in the root directory of the repo
git add inc/
git commit -m "ABI Headers for WinML" inc/
```

