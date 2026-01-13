# Producing the Projection Headers

Current projection packages, for [Microsoft.WindowsAppSDK v1.8.251106002](https://www.nuget.org/packages/Microsoft.WindowsAppSDK/1.8.251106002):
* [Microsoft.WindowsAppSDK.InteractiveExperiences v1.8.251104001](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.InteractiveExperiences/1.8.251104001)
* [Microsoft.WindowsAppSDK.Foundation v1.8.251104000](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.Foundation/1.8.251104000)
* [Microsoft.WindowsAppSDK.AI v1.8.39](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.AI/1.8.39)
* [Microsoft.WindowsAppSDK.ML v1.8.2109](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.ML/1.8.2109)
* [Microsoft.WindowsAppSDK.Runtime v1.8.251106002](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.Runtime/1.8.251106002)

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

Fetch component packages from nuget using the above package names:

```pwsh
$ixp_version = "1.8.251104001"
nuget install Microsoft.WindowsAppSDK.InteractiveExperiences -Version $ixp_version -OutputDirectory $working_dir\packages

$foundation_version = "1.8.251104000"
nuget install Microsoft.WindowsAppSDK.Foundation -Version $foundation_version -OutputDirectory $working_dir\packages

$ai_version = "1.8.39"
nuget install Microsoft.WindowsAppSDK.AI -Version $ai_version -OutputDirectory $working_dir\packages

$ml_version = "1.8.2109"
nuget install Microsoft.WindowsAppSDK.ML -Version $ml_version -OutputDirectory $working_dir\packages

$runtime_version = "1.8.251106002"
nuget install Microsoft.WindowsAppSDK.Runtime -Version $runtime_version -OutputDirectory $working_dir\packages
```

## Projections and Related Headers

Currently, only a subset of interfaces are projected and available in this repo. See the list above.
File a new issue to request inclusion of other content.

From the root of the repo:

```pwsh
# Generate and copy projection headers for a selection of components
$abiwinrt = gci -r $working_dir\packages\*abi*\abi.exe

mkdir inc\abi\interactiveexperiences -ErrorAction SilentlyContinue
$ixp_metadata = gci -r "$working_dir\packages\microsoft.windowsappsdk.interactiveexperiences.$ixp_version\metadata\10.0.17763.0\*.winmd"
& $abiwinrt -input $ixp_metadata.FullName -reference sdk -output inc\abi\interactiveexperiences -lowercase-include-guard -ns-prefix always
copy $working_dir\packages\microsoft.windowsappsdk.interactiveexperiences.$ixp_version\include\* inc\abi\interactiveexperiences -recurse -force

mkdir inc\abi\foundation -ErrorAction SilentlyContinue
$foundation_metadata = gci -r "$working_dir\packages\microsoft.windowsappsdk.foundation.$foundation_version\metadata\*.winmd"
& $abiwinrt -input $foundation_metadata.FullName -reference sdk $ixp_metadata.FullName -output inc\abi\foundation -lowercase-include-guard -ns-prefix always
copy $working_dir\packages\microsoft.windowsappsdk.foundation.$foundation_version\include\* inc\abi\foundation -recurse -force

mkdir inc\abi\winai -ErrorAction SilentlyContinue
$ai_metadata = gci -r "$working_dir\packages\microsoft.windowsappsdk.ai.$ai_version\metadata\*.winmd"
& $abiwinrt -input $ai_metadata.FullName -reference sdk -output inc\abi\winai -lowercase-include-guard -ns-prefix always

mkdir inc\abi\winml -ErrorAction SilentlyContinue
$ml_metadata = gci -r "$working_dir\packages\microsoft.windowsappsdk.ml.$ml_version\metadata\*.winmd"
& $abiwinrt -input $ml_metadata.FullName -reference sdk -output inc\abi\winml -lowercase-include-guard -ns-prefix always
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
