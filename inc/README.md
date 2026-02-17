# Producing the Projection Headers

Current projection packages:

* [Microsoft.WindowsAppSDK.ML v1.8.2091](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.ML/1.8.2091)
* [Microsoft.WindowsAppSDK.Runtime v1.8.250916003](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.Runtime/1.8.250916003)

## Acquire Tooling

Install a Windows Platform SDK if you don't have one already:

```pwsh
winget install Microsoft.WindowsSDK.10.0.26100
```

Create a temporary location to work:

```pwsh
$working_dir = Join-Path $env:temp wasdk_inc
Remove-Item -Force -Recurse $working_dir -ErrorAction SilentlyContinue
mkdir -force -ErrorAction SilentlyContinue $working_dir
nuget install Microsoft.Windows.AbiWinRT -OutputDirectory $working_dir\packages
```

## Acquire metadata from latest release

Fetch the package from nuget using the above package names:

```pwsh
$ml_version = "1.8.2091"
$runtime_version = "1.8.250916003"
nuget install Microsoft.WindowsAppSDK.ML -Version $ml_version -OutputDirectory $working_dir\packages
nuget install Microsoft.WindowsAppSDK.Runtime -Version $runtime_version -OutputDirectory $working_dir\packages
```

## Projections and Related Headers

Currently, only a subset of interfaces are projected and available in this repo. See the list above.
File a new issue to request inclusion of other content.

From the root of the repo:

```pwsh
# Generate WinML projections, copy headers (replace inc\abi\winml with inc\abi\othercomponent as needed)
mkdir inc\abi\winml -ErrorAction SilentlyContinue
$abiwinrt = gci -r $working_dir\packages\*abi*\abi.exe
$metadata = gci -r $working_dir\packages\microsoft.windowsappsdk.ml.$ml_version\metadata
& $abiwinrt -input $metadata -reference sdk -output inc\abi\winml -lowercase-include-guard -ns-prefix always
copy $working_dir\packages\microsoft.windowsappsdk.ml.$ml_version\include\* inc\abi\winml -recurse -force

# Copy common runtime headers
mkdir inc\abi\runtime -ErrorAction SilentlyContinue
copy $working_dir\packages\microsoft.windowsappsdk.runtime.$runtime_version\include\*.h inc\abi\runtime -recurse -force

# Remove accidental over-projection
gci -r inc\abi\runtime\Windows.* | remove-item
```

## Update Copyright Stamps

Ensure that any new files have the Microsoft copyright and MIT license notice at the top.  Run
[VerifyCopyrightHeaders.cmd -fix](../tools/VerifyCopyrightHeaders.cmd) before committing.

## Commit changes

> **NOTE:** Only a specific subset of headers from Windows App SDK may be include.

Create or switch to the release branch for the output artifacts, then commit the changes:

```pwsh
# Run these in the root directory of the repo
git add inc/
git commit -m {suitable comment here} inc/
```
