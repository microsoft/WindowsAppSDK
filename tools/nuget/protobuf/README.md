# Microsoft.WindowsAppSDK.Protobuf Nuget Package

## Problem: Where's the Nuget Package?

Google's Protocol Buffers (aka protobuf) is available as nuget packages on https://nuget.org for
most languages (C#, Python, ...) but for C++ developers there's only google.protobuf.tools
providing a precompiled message compiler (protoc.exe). That reads *.proto files and generates C++
source and header files but doesn't provide protobuf's headers and lib(s) required to compile your
generated code.

The documented solution is to use VCPKG to download and compile protobuf's sources but VCPKG
doesn't provide as clean an isolation model as nuget packages, plus the VCPKG built solution
doesn't quite align with our needs (e.g. debug CRT). VCPKG can export to a nuget package but
that's rather sizable (115M for x86+x64+arm64 support, unsurprisingly as it contains Release and
Debug builds) and GitHub rejects any push'd commit if it contains a file >100M.

## Solution: Roll up our sleeves...

VCPKG does the heavy lifting for us, driving the protobuf build process to produce the desired
artifacts. We then finish the job to create a nuget to suit our needs:

1. Use VCPKG to download and build protobuf
2. Define our own .props/.targets to integrate protobuf into VS/MSBuild
3. Define our own script to create a nuget from the VCPKG build

The resulting nuget package is named Microsoft.WindowsAppSDK.Protobuf.

NOTE: Only the developer creating the nuget (or creating a new version) has to wade through this
process. Everyone else in the project is blissfully aware and can just consume the nuget package
like any others.

## Where's the Nuget?

A new directory is created as an in-repo-repository of nuget package: `tools\nuget`

`\nuget.config` is updated to find Microsoft.WindowsAppSDK.Protobuf nuget packages in this local repository.

## HOWTO: Build the nuget

Run `tools\nuget\protobuf\protobuf-makenuget.cmd` (no parameters) for help.

The steps to build the protobuf nuget (assumed windowsappsdk is located at c:\source\repos\windowsappsdk):

```
cd /d c:\source\repos
git clone https://github.com/microsoft/vcpkg
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install protobuf:x86-windows-static protobuf:x64-windows-static protobuf:arm64-windows-static
cd /d c:\source\repos\windowsappsdk\tools\nuget
protobuf\protobuf-makenuget.cmd c:\source\repos\vcpkg . 3.21.12
```

NOTE: Replace the `3.21.12` parameter with the version you're creating.

This will produce the nuget e.g. `tools\nuget\Microsoft.WindowsAppSDK.Protobuf.3.21.12.nupkg`.
