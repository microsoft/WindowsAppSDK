# Hybrid CRT

The Windows App SDK runs in diverse environments and contexts. Much of the Windows App Runtime
is implemented in C++ and is thus dependent on the Standard C/C++ Runtime (the CRT).
As of versions 1.0.3 and 1.1 Preview 2, all Windows App SDK DLLs and EXEs containing C/C++ code are built
using the 'Hybrid CRT' technique. This frees developers from the burden of installing the CRT
redistributables on end user devices - whether
the [VCLibs UWPDesktop framework package](https://docs.microsoft.com/troubleshoot/developer/visualstudio/cpp/libraries/c-runtime-packages-desktop-bridge)
for packaged apps, or the
[vc_redist](https://docs.microsoft.com/cpp/windows/latest-supported-vc-redist?view=msvc-170)
for unpackaged apps.

For additional information on Hybrid CRT, see the [WinUI Community Call – April 20, 2022](https://www.youtube.com/watch?v=bNHGU6xmUzE&t=16m17s)

## What is the 'Hybrid CRT'?

The 'Hybrid CRT' is a technique using the
[Universal CRT](https://docs.microsoft.com/cpp/windows/universal-crt-deployment?view=msvc-160)
AND the static CRT to get functional coverage without the overhead of the static CRT or the external
dependency of the dynamic CRT.

Visual Studio offers the CRT in 2 forms: DLLs needed at runtime (dynamic) and static
libraries linked into PE files (static). These are controlled via
[compiler options](https://docs.microsoft.com/cpp/build/reference/md-mt-ld-use-run-time-library?view=msvc-160)

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
[Universal CRT](https://docs.microsoft.com/cpp/windows/universal-crt-deployment?view=msvc-160)
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
CRT to 554,496 using the Hybrid CRT (+37KB or ~+7%). See pull request
[Use the Universal C Runtime #888](https://github.com/microsoft/WindowsAppSDK/pull/888) for more
details.

## Hybrid CRT for the Windows App SDK

Windows App SDK defines the rules for Visual Studio in [HybridCRT.props](https://github.com/microsoft/WindowsAppSDK/blob/main/HybridCRT.props).
This is imported by
[Directory.Build.props](https://github.com/microsoft/WindowsAppSDK/blob/main/Directory.Build.props) so all
projects in the directory tree (product and test) get this support.

If new projects are created DO NOT specify `<RuntimeLibrary>` in *.vcxproj as that's unnecessary and
potentially contradictory with proper use of the Hybrid CRT. Delete any `<RuntimeLibrary>` tags in
*.vcxproj and the right values will be inherited from
[HybridCRT.props](https://github.com/microsoft/WindowsAppSDK/blob/main/HybridCRT.props).

### HybridCRT.props

[HybridCRT.props](https://github.com/microsoft/WindowsAppSDK/blob/main/HybridCRT.props) defines the
rules for Visual Studio to build projects with the Hybrid CRT.

The steps involved:

1. `<RuntimeLibrary>` = MultiThreaded\[Debug\] -- use the static CRT
2. `<IgnoreSpecificDefaultLibraries>` includes `libucrt[d].lib` -- ignore the libucrt\[d\] library
3. `<AdditionalOptions>` includes `/defaultlib:ucrt[d].lib` -- link the ucrt\[d\] library

```xml
<?xml version="1.0" encoding="utf-8"?>
<!-- Copyright (c) Microsoft Corporation. All rights reserved. Licensed under the MIT License. See LICENSE in the project root for license information. -->
<Project ToolsVersion="14.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">

  <ItemDefinitionGroup Condition="'$(Configuration)'=='Debug'">
    <ClCompile>
      <!-- We use MultiThreadedDebug, rather than MultiThreadedDebugDLL, to avoid DLL dependencies on VCRUNTIME140d.dll and MSVCP140d.dll. -->
      <RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>
    </ClCompile>
    <Link>
      <!-- Link statically against the runtime and STL, but link dynamically against the CRT by ignoring the static CRT
           lib and instead linking against the Universal CRT DLL import library. This "Hybrid" linking mechanism is
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
           lib and instead linking against the Universal CRT DLL import library. This "Hybrid" linking mechanism is
           supported according to the CRT maintainer. Dynamic linking against the CRT makes the binaries a bit smaller
           than they would otherwise be if the CRT, runtime, and STL were all statically linked in. -->
      <IgnoreSpecificDefaultLibraries>%(IgnoreSpecificDefaultLibraries);libucrt.lib</IgnoreSpecificDefaultLibraries>
      <AdditionalOptions>%(AdditionalOptions) /defaultlib:ucrt.lib</AdditionalOptions>
    </Link>
  </ItemDefinitionGroup>

</Project>
```

### Directory.Build.props

[Directory.Build.props](https://github.com/microsoft/WindowsAppSDK/blob/main/Directory.Build.props) in the
repository root imports
[HybridCRT.props](https://github.com/microsoft/WindowsAppSDK/blob/main/HybridCRT.props) to apply to
all projects in the repository via this statement:

```xml
  <!-- Build with the Hybrid CRT (Universal CRT + Static VS CRT (for what little the Universal CRT doesn't cover) -->
  <Import Project="$(MSBuildThisFileDirectory)HybridCRT.props" />
```

## Hybrid CRT for End Developers

### Hybrid CRT C/C++ Apps

For their own CRT usage, C/C++ Windows App SDK app developers may continue to link statically,
with no redistribution requirements, or dynamically, requiring either a VCLibs*
dependency (for packaged apps) or a vc_redist.*.exe dependency (for unpackaged apps).

For unpackaged self-contained C/C++ Windows App SDK apps, developers may find
Hybrid CRT linkage useful for enabling xcopy deployment. For these apps, the Directory.Build.*
files described above can be included in the project. For apps that also include C++/CX code,
additional considerations are described below.

### Hybrid CRT C/C++ Libs

Existing libraries targeting Universal Windows (UWP) may be consumed by a Windows App SDK app,
provided:

* The app references [VCRT Forwarders](https://github.com/microsoft/vcrt-forwarders),
to map App CRT linkage to Desktop CRT (vcruntime140_app.dll -> vcruntime140.dll ...), or
* The library project includes this property, to force Desktop CRT linkage (vcruntime140.dll ...):

  ```xml
  <DesktopCompatible>true</DesktopCompatible>
  ```

In either case, dynamic CRT linkage is used.
Converting the UWP library to Hybrid CRT will trigger this build warning:

```xml
Using static version of the C++ runtime library is not supported
```

This can be resolved by one of two methods:

* Converting the library project to target Windows Desktop by removing these properties:

  ```xml
  <AppContainerApplication>true</AppContainerApplication>
  <ApplicationType>Windows Store</ApplicationType>
  ```

* Suppressing the warning by adding this property:

  ```xml
  <UseCrtSDKReferenceStaticWarning>false</UseCrtSDKReferenceStaticWarning>
  ```

## C++/CX Special Considerations

Projects that include CX code, and wish to use Hybrid CRT, require the following compile
settings (explanations below):

```xml
  <ClCompile>
    <PreprocessorDefinitions>_CRTIMP2_IMPORT=;_CRTIMP2_PURE_IMPORT=;_CRTDATA2_IMPORT=;_ALLOW_RUNTIME_LIBRARY_MISMATCH;%(PreprocessorDefinitions)</PreprocessorDefinitions>
  </ClCompile>
```

As stated above, ClCompile.RuntimeLibrary should not be specified in a C++ project.  
But CX involves a bit more work.  CX compilation requires the /ZW switch, which in turn
requires dynamic CRT linkage, via the /MD(d) switch, which in turn requires
ClCompile.RuntimeLibrary to be set to MultiThreaded(Debug)Dll:  

```build
1>cl : command line error D8016: '/MTd' and '/ZW' command-line options are incompatible 
```

The /MD(d) switch in turn defines the preprocessor symbol _DLL, causing the compile-time
and link-time issues below.

### Compilation

The CRT yvals.h header consults _DLL to conditionally add __declspec(dllimport) to any
CRT/STL externals.  Compiling CX code that expects to use dynamic CRT, but linking with
the static CRT libraries, produces warnings and errors such as:

```build
1>warning LNK4217: symbol '…' defined in 'libcpmtd.lib(cout.obj)' is imported by '…' 
1>error LNK2019: unresolved external symbol "__declspec(dllimport) …"
```

To ensure that CX code is compiled to expect static CRT linkage, the following symbols
are defined (with no values, to mimic #defines), preventing decoration of externals with
__declspec(dllimport):

```xml
<ClCompile>
  <PreprocessorDefinitions>_CRTIMP2_IMPORT=;_CRTIMP2_PURE_IMPORT=;_CRTDATA2_IMPORT=;%(PreprocessorDefinitions)</PreprocessorDefinitions>
</ClCompile>
```

### Linking

The CRT yvals.h header also uses _DLL to determine the value of the RuntimeLibrary pragma
detect mismatch (PDM).  Normally, this PDM would ensure that a mixture of CRTs (static and
dynamic) is not introduced into a single binary.  But this produces an error linking CX code
with C++ code compiled for Hybrid (static) CRT linkage:

```build
1>error LNK2038: mismatch detected for 'RuntimeLibrary': value 'MDd_DynamicDebug' doesn't match value 'MTd_StaticDebug'
```

There are two potential sources of the RuntimeLibrary PDM being set to dynamic.
One is the scenario described above - compiling user CX code with /MD(d).
The other is linking with the CRT import library, msvcrt(d).lib.  

For user CX code compilation, the only option is to suppress definition of the
RuntimeLibrary PDM by defining the following symbol:  

```xml
<ClCompile>
  <PreprocessorDefinitions>_ALLOW_RUNTIME_LIBRARY_MISMATCH;%(PreprocessorDefinitions)</PreprocessorDefinitions>
</ClCompile>
```

For linkage, msvcrt(d).lib must never be used.  In other words, even test code
which pulls in production code must use Hybrid (static) CRT linkage.
