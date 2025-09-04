# Producing the Projection Headers

## Acquire Tooling

Install a Windows Platform SDK if you don't have one already:

```pwsh
winget install Microsoft.WindowsSDK.10.0.26100
```

Create a temporary location to work:

```pwsh
$working_dir = Join-Path $env:temp wasdk_inc
Remove-Item -Force -Recurse $working_dir
mkdir -force -ErrorAction SilentlyContinue $working_dir
nuget install Microsoft.Windows.AbiWinRT -OutputDirectory $working_dir\packages
```

## Acquire metadata from latest release

Check [the NuGet package release list](https://nuget.info/packages/Microsoft.WindowsAppSDK) to find
the latest packages (including preview and experimental).  Note their version number. In this example,
we'll be using [Microsoft.WindowsAppSDK version 1.8.250702007-experimental4](https://www.nuget.org/packages/Microsoft.WindowsAppSDK/1.8.250702007-experimental4)

Fetch the package from nuget:

```pwsh
nuget install Microsoft.WindowsAppSDK -Version "1.8.250702007-experimental4" -OutputDirectory $working_dir\packages
```

## Projections and Related Headers

This example generates the projections from the `Microsoft.WindowsAppSDK.ML` package, and copies the related
versioning headers and samples in as well. Run these from the root of the repo:

```pwsh
# Generate WinML projections, copy headers (replace inc\abi\winml with inc\abi\othercomponent as needed)
mkdir inc\abi\winml -ErrorAction SilentlyContinue
$abiwinrt = gci -r $working_dir\packages\*abi*\abi.exe
$metadata = gci -r $working_dir\packages\microsoft.windowsappsdk.ml*\metadata
& $abiwinrt -input $metadata -reference sdk -output inc\abi\winml -lowercase-include-guard -ns-prefix always
copy $working_dir\packages\microsoft.windowsappsdk.ml*\include\* inc\abi\winml -recurse -force

# Copy common runtime headers
mkdir inc\abi\runtime -ErrorAction SilentlyContinue
copy $working_dir\packages\microsoft.windowsappsdk.runtime*\include\*.h inc\abi\runtime -recurse -force
```

## Update Copyright Stamps

Ensure that any new files have the Microsoft copyright and MIT license notice at the top.  Run
[VerifyCopyrightHeaders.cmd](../tools/VerifyCopyrightHeaders.cmd) before committing.

## Commit changes

Create or switch to the release branch for the output artifacts, then commit the changes

```pwsh
# Run these in the root directory of the repo
git add inc/
git commit -m {suitable comment here} inc/
```

