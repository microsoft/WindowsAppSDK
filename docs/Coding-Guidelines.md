Windows App SDK Coding Guidelines

- [1. General](#1-general)
  - [1.1. Languages](#11-languages)
    - [1.1.1. C++](#111-c)
        - [1.1.1.0.1. Catching C++/WinRT Exceptions and HRESULT](#11101-catching-cwinrt-exceptions-and-hresult)
    - [1.1.2. Markdown](#112-markdown)
  - [1.2. Git Checkin-to-main Policy](#12-git-checkin-to-main-policy)
    - [1.2.1. Policy: Preview and Stable (aka non-Experimental)](#121-policy-preview-and-stable-aka-non-experimental)
    - [1.2.2. Policy: Experimental](#122-policy-experimental)
- [2. Hybrid CRT](#2-hybrid-crt)
  - [2.1. What is the 'Hybrid CRT'?](#21-what-is-the-hybrid-crt)
  - [2.2. How to use the 'Hybrid CRT'](#22-how-to-use-the-hybrid-crt)
    - [2.2.1. HybridCRT.props](#221-hybridcrtprops)
    - [Directory.Build.props](#directorybuildprops)

# 1. General

The Windows App SDK prefers using industry-standard coding styles, guidelines, and patterns for any
languages used in implementation or testing.

## 1.1. Languages

This list is non-exhaustive; new guidelines for languages will be added over time.

### 1.1.1. C++

**DO** implement types using C++ and [C++/WinRT](https://github.com/microsoft/cppwinrt)

**DO** follow the [CppCoreGudelines](https://github.com/isocpp/CppCoreGuidelines) for all new code.

**DO** enable `/W4 /Wx` for all new code.

**CONSIDER** using the [Windows Implementation Library](https://github.com/Microsoft/wil) for
Windows-specific helpers rather than creating your own.

**DO** use 4-space indentation instead of tab characters.

##### 1.1.1.0.1. Catching C++/WinRT Exceptions and HRESULT

Exceptions should not be used for standard flow control.

When a catch clause is required, note that `winrt::hresult_error` does not also catch
`std::bad_alloc` or any of the other C++ standard exceptions. In cases where a single catch handler
desires to pull out an HRESULT, use the following:

```c++
// For code using C++/WinRT
catch (...)
{
    auto e{ winrt::hresult_error(winrt::to_hresult(), winrt::take_ownership_from_abi) };
    auto hr{ e.code() };
    auto message { e.message() };
    // hr contains the WinRT exception or best-guess conversion from a C++ exception,
    // message contains the best-guess textual format of that exception
}

// For code using WIL
catch (...)
{
    auto hr{ wil::ResultFromCaughtException() };
    // hr contains the WinRT exception, WIL exception, or best-guess conversion from a C++ exception
}
```

C++/WinRT's ABI layer automatically catches and converts exceptions generated during a method call
and uses a similar mechanism to map a C++ exception to an `HRESULT` that can be delivered across the
ABI.

### 1.1.2. Markdown

**DO** wrap lines at ~100 characters. GitHub formats lines regardless of individual length but
GitHub diff is line oriented. Keeping lines within the preferred limit makes changes easier to
review. Use a tool like Prettier to bulk-reformat files, or configure your editor's "rulers." If new
languages become common, we will describe the coding guidelines for such languages here.

## 1.2. Git Checkin-to-main Policy

The main branch needs to be kept 'healthy' and ready to ship near daily (daily, or within a day or
two). An unhealthy main branch negatively impacts day-to-day development and jeopardizes release
schedules. We have policies to ensure a high quality bar in main. The details differ depending if a
code change is Experimental vs Preview or Stable.

See [Final Decision: Release channels and cadences #637](https://github.com/microsoft/WindowsAppSDK/discussions/637)
for the expectations of the various release channels.

### 1.2.1. Policy: Preview and Stable (aka non-Experimental)

The following requirements must be met to checkin non-Experimental changes to main:

1. API Review approval
2. Tests
3. Prepared to accept bug reports from the world

Changes of a non-Experimental nature must meet these policies to be committed to the main branch.

### 1.2.2. Policy: Experimental

The policies for Experimental content differ from non-Experimental content because of the reasons for Experimental content:

1. **Selfhost** – a change is good but you're interested in community usage and feedback to verify
   it's ready for Preview/Stable.
2. **Skeleton** – API Review has approved and you've made an initial 'skeletal' implementation to
   get the interface and infrastructure building but isn't functionally complete e.g. skeletal code
   compiles but everything returns E_NOTIMPL/false/null/etc). Having the API surface building in
   main can unblock documentation, test and sample writers.
3. **Feedback** – your API shape isn't locked (or even clear) but you want and/or need feedback from
   the community, partners and/or others before deciding the API is ready to consider for
   non-Experimental releases. The API is not yet ready to go through API Review.

Reasons NOT to make Experimental content:

1. **Prototype** – prototypes, ideas and wild experimentation should be done on a 'feature branch'
   and not checked into main. To make a 'feature branch' checkout a new branch off main (or a child
   of main) with no intention to checkin to main any time soon (or maybe ever). Make a feature
   branch and don't check into main

Changes of an Experimental nature follow a modified form of the policies for non-Experimental content:

1. CONSIDER: Review API with your local-representative
2. Tests
3. Prepared to accept feedback from the world
4. Experimental APIs are marked experimental

Experimental APIs don't go through full API Review but should be discussed with your local API
Review representative. This ensures your API is aligned with API practices and policies and avoids
the risk of significant changes required to pass API Review.

Experimental content requires appropriate test coverage. This is no different than non-Experimental
content, except meaning of 'appropriate' may vary. For instance, 'skeletal' Experimental APIs don't
need the same breadth of test coverage as non-Experimental APIs.

Experimenal content is broadly shipped via Experimental releases. You should be prepared to receive
feedback on Experimental content.

Experimental content must be tagged to indicate it's Experimental. The mechanisms to do so may vary
(WinRT APIs, Flat-C APIs, non-API content (e.g. data files), etc) but the policy is the same -
Experimental content must be marked to indicate it's Experimental.

# 2. Hybrid CRT

Windows App SDK runs in diverse environments and contexts (i.e. all of them ;-) Much of the runtime
is implemented in C++ and thus dependent on the Standard C/C++ Runtime aka the CRT. To ensure a
highly reliable and friction-less experience (for developers as well as users) all DLLs and EXEs
containing C/C++ code are built using the 'hybrid CRT' technique.

## 2.1. What is the 'Hybrid CRT'?

The 'Hybrid CRT' is a technique using the
[Universal CRT](https://docs.microsoft.com/en-us/cpp/windows/universal-crt-deployment?view=msvc-160)
AND the static CRT to get functional coverage without the overhead of the static CRT or the external
dependency of the dynamic CRT.

Visual Studio offers the CRT in 2: DLLs needed at runtime (dynamic) and static
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

## 2.2. How to use the 'Hybrid CRT'

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

### 2.2.1. HybridCRT.props

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



