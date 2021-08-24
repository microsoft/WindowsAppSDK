# Hybrid CRT

Windows App SDK runs in diverse environments and contexts (i.e. all of them ;-) Much of the runtime
is implemented in C++ and thus dependent on the Standard C/C++ Runtime aka the CRT. To ensure a
highly reliable and friction-less experience (for developers as well as users) all DLLs and EXEs
containing C/C++ code are built using the 'hybrid CRT' technique.

## What is the 'Hybrid CRT'?

The 'Hybrid CRT' is a technique using the
[Universal CRT](https://docs.microsoft.com/en-us/cpp/windows/universal-crt-deployment?view=msvc-160)
AND the static CRT to get functional coverage without the overhead of the static CRT or the external
dependency of the dynamic CRT.

Visual Studio offers the CRT in 2 forms: DLLs needed at runtime (dynamic) and static
libraries linked into PE files (static). These are controlled via
[compiler options](https://docs.microsoft.com/en-us/cpp/build/reference/md-mt-ld-use-run-time-library?view=msvc-160)

* /MD - Dynamic, non-debug
* /MDd - Dynamic, debug
* /MT - Static, non-debug
* /MTd - Static, debug

Dynamic CRT requires the Visual Studio CRT DLLs be present at runtime. It's up to the dependent
application to install them if necessary. This would be an implicit dependency for anyone using
Windows App SDK, e.g. a C# or Rust application having no need for the CRT would be forced to install
it if necessary. Further, how the CRT is resolved varies for packaged vs unpackaged apps.

Static CRT links needed symbols into PE files making avoiding the need for an external dependency at
runtime at the cost of increased size of every PE file in Windows App SDK. The cost varies depending
on the symbols needed but 1M+ is common.

Windows includes the
[Universal CRT](https://docs.microsoft.com/en-us/cpp/windows/universal-crt-deployment?view=msvc-160)
(aka UCRT) as system binaries. The UCRT is available on all platforms supported by Windows App SDK
(and older too). However the UCRT only provides a subset of the CRT (`malloc`, `fopen`, etc what's
generally thought of as the Standard C Library, provided via a stable ABI). Visual Studio's
implementation of the Standard C/C++ Library includes some symbols that aren't ABI stable
(compiler-specific helpers for C++ exception handling, STL-related code, etc).

The Hybrid CRT combines the UCRT and static CRT. Files build with the UCRT to get much of the CRT
dependencies, supplemented by the static CRT as necessary. This poses a theoretical maximum
worst-case static linkage size of ~200KB, but that assumes every symbol in the Standard C/C++
Library is needed. In practice it's a smaller slice.

For example, Microsoft.ProjectReunion.dll in 0.8-preview grew from 516,096 bytes using the dynamic
CRT to 554,496 using the hybrid CRT (+37KB or ~+7%). See pull request
[Use the Universal C Runtime #888](https://github.com/microsoft/WindowsAppSDK/pull/888) for more
details.

Windows App SDK uses the hybrid CRT for all PE files.

## How to use the 'Hybrid CRT'

TL;DR Do nothing and all projects use it. If you create a new *.vcxproj delete any `<RuntimeLibrary>` tags.

Windows App SDK defines the rules for Visual Studio in
[https://github.com/microsoft/WindowsAppSDK/HybridCRT.props](https://github.com/microsoft/WindowsAppSDK/blob/main/HybridCRT.props).
This is imported by
[Directory.Build.props](https://github.com/microsoft/WindowsAppSDK/Directory.Build.props) so all
projects in the directory tree get this support.

If new projects are created DO NOT specify `<RuntimeLibrary>` in *.vcxproj as that's unnecessary and
potentially contradictory with proper use of the hybrid CRT. Delete any `<RuntimeLibrary>` tags in
*.vcxproj and the right values will be inherited from
[HybridCRT.props](https://github.com/microsoft/WindowsAppSDK/blob/main/HybridCRT.props).

### HybridCRT.props

[HybridCRT.props](https://github.com/microsoft/WindowsAppSDK/blob/main/HybridCRT.props) defines the
rules for Visual Studio to build projects with the Hybrid CRT.

The steps involved:

1. `<UseUnicrt>` = true -- use the UCRT
2. `<RuntimeLibrary>` = MultiThreaded\[Debug\] -- use the static CRT
3. `<IgnoreSpecificDefaultLibraries>` includes `libucrt[d].lib` -- ignore the libucrt\[d\] library
4. `<AdditionalOptions>` includes `/defaultlib:ucrt[d].lib` -- link the ucrt\[d\] library

```xml
<?xml version="1.0" encoding="utf-8"?>
<!-- Copyright (c) Microsoft Corporation. All rights reserved. Licensed under the MIT License. See LICENSE in the project root for license information. -->
<Project ToolsVersion="14.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">

  <PropertyGroup Label="Globals">
    <UseUnicrt>true</UseUnicrt>
  </PropertyGroup>

  <ItemDefinitionGroup Condition="'$(Configuration)'=='Debug'">
    <ClCompile>
      <!-- We use MultiThreadedDebug, rather than MultiThreadedDebugDLL, to avoid DLL dependencies on VCRUNTIME140d.dll and MSVCP140d.dll. -->
      <RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>
    </ClCompile>
    <Link>
      <!-- Link statically against the runtime and STL, but link dynamically against the CRT by ignoring the static CRT
           lib and instead linking against the Universal CRT DLL import library. This "hybrid" linking mechanism is
           supported according to the CRT maintainer. Dynamic linking against the CRT makes the binaries a bit smaller
           than they would otherwise be if the CRT, runtime, and STL were all statically linked in. -->
      <IgnoreSpecificDefaultLibraries>%(IgnoreSpecificDefaultLibraries);libucrtd.lib</IgnoreSpecificDefaultLibraries>
      <AdditionalOptions>%(AdditionalOptions) /defaultlib:ucrtd.lib</AdditionalOptions>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)'=='Release'">
    <ClCompile>
      <!-- We use MultiThreaded, rather than MultiThreadedDLL, to avoid DLL dependencies on VCRUNTIME140.dll and MSVCP140.dll. -->
      <RuntimeLibrary>MultiThreaded</RuntimeLibrary>
    </ClCompile>
    <Link>
      <!-- Link statically against the runtime and STL, but link dynamically against the CRT by ignoring the static CRT
           lib and instead linking against the Universal CRT DLL import library. This "hybrid" linking mechanism is
           supported according to the CRT maintainer. Dynamic linking against the CRT makes the binaries a bit smaller
           than they would otherwise be if the CRT, runtime, and STL were all statically linked in. -->
      <IgnoreSpecificDefaultLibraries>%(IgnoreSpecificDefaultLibraries);libucrt.lib</IgnoreSpecificDefaultLibraries>
      <AdditionalOptions>%(AdditionalOptions) /defaultlib:ucrt.lib</AdditionalOptions>
    </Link>
  </ItemDefinitionGroup>

</Project>
```

### Directory.Build.props

[Directory.Build.props](https://github.com/microsoft/WindowsAppSDK/Directory.Build.props) in the
repository root imports
[HybridCRT.props](https://github.com/microsoft/WindowsAppSDK/blob/main/HybridCRT.props) to apply to
all projects in the repository via this statement:

```xml
  <!-- Build with the hybrid CRT (Universal CRT + Static VS CRT (for what little the Universal CRT doesn't cover) -->
  <Import Project="$(MSBuildThisFileDirectory)HybridCRT.props" />
```

This applies to all projects in the repository (product, test, ...).
