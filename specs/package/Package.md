# 1. MSIX Package

This feature provides package APIs comparable to those in appmodel.h and Package-related types in
namespace Windows.ApplicationModel
([Package](https://learn.microsoft.com/uwp/api/windows.applicationmodel.package),
[PackageId](https://learn.microsoft.com/uwp/api/windows.applicationmodel.packageid),
[PackageStatus](https://learn.microsoft.com/uwp/api/windows.applicationmodel.packagestatus), etc)
but with additional functionality, improved developer experience and performance optimizations.

- [1. MSIX Package](#1-msix-package)
- [2. Background](#2-background)
- [3. Description](#3-description)
  - [3.1. FindPackageFile\*()](#31-findpackagefile)
    - [3.1.1. Package Location Search Order](#311-package-location-search-order)
    - [3.1.2. FindPackageFileInPackage](#312-findpackagefileinpackage)
    - [3.1.3. FindPackageFileInPackageGraph](#313-findpackagefileinpackagegraph)
- [4. Examples](#4-examples)
  - [4.1. FindPackageFileInPackage](#41-findpackagefileinpackage)
    - [4.1.1. C# Example](#411-c-example)
    - [4.1.2. C++ Example](#412-c-example)
  - [4.2. FindPackageFileInPackage with Options](#42-findpackagefileinpackage-with-options)
    - [4.2.1. C# Example](#421-c-example)
    - [4.2.2. C++ Example](#422-c-example)
  - [4.3. FindPackageFileInPackageGraph](#43-findpackagefileinpackagegraph)
    - [4.3.1. C# Example](#431-c-example)
    - [4.3.2. C++ Example](#432-c-example)
  - [4.4. FindPackageFileInPackageGraph with Options](#44-findpackagefileinpackagegraph-with-options)
    - [4.4.1. C# Example](#441-c-example)
    - [4.4.2. C++ Example](#442-c-example)
- [5. Remarks](#5-remarks)
  - [5.1. Platform Support](#51-platform-support)
- [6. API Details](#6-api-details)
  - [6.1. WinRT API](#61-winrt-api)
  - [6.2. Win32 API](#62-win32-api)

# 2. Background

Windows supports the ability to query, format, parse, validate and otherwise examine MSIX packages
via Win32 APIs in appmodel.h and WinRT APIs in the Windows.ApplicationModel namespace.

The package APIs were originally introduced in Windows 8 and have continuously expanded to meet
MSIX's growing demands over the past decade. However, as one of the earliest WinRT APIs they include
some patterns out of step with current API practices and recommendations. Windows App SDK offers the
opportunity to provide a new generation of package APIs in line with the latest patterns and
recommendations for an improved developer experience as well as functional enhancements and improved
runtime efficiencies.

Microsoft-internal task [TODO](https://task.ms/TODO)

# 3. Description

This API provides enhanced access to Windows' package information, focusing on the following
scenarios:

* Find a packaged file

## 3.1. FindPackageFile*()

An MSIX package contains...

* [Footprint files](https://learn.microsoft.com/windows/win32/api/appxpackaging/ne-appxpackaging-appx_footprint_file_type)
  e.g. `AppxManifest.xml`
* Content files i.e. all other files (*.exe, *.dll, *.jpg, *.dat, ...)

A package always has an Install location and may also have other locations:

* Install location
* Mutable location
* Machine External location
* User External location

Mutable and External locations are optional and not mutually exclusive.

See [PackagePathType](https://learn.microsoft.com/windows/win32/api/appmodel/ne-appmodel-packagepathtype)
for more details.

Footprint files are always in a package's Install location. Content files can by in any of a
package's location(s) e.g.

* Install location contains Content files when the package has no other location
* Mutable location typically contains files modified (overridden) by a user
* Packages registered for a user typically use Machine -or- User External location e.g.
  * Package Foo has Machine External location = Q:\Foo
  * Package Foo is registered for Bob has a User External location = X:\Bar
  * Package Foo is registered for Mary w/no User External location
  * THUS:
    * Bob uses his User External location (X:\Bar) and ignores the Machine External location
    * Mary has no User External location so she uses the Machine External location (Q:\Foo)

Packages typically have Content files in one location but this isn't required. For example, some
files can appear in any of multiple locations and some code isn't External location aware (sometimes
ByDesign, sometimes due to bugs). Changing behavior reducing location awareness poses appcompat
risks leading some features to need to broaden their support to search across multiple locations.

The `FindPackageFile*()` APIs search the filesystem for a specified file as appropriate across the
package(s)' location(s).

The APIs are available as Win32 exports and WinRT, similar to existing APIs in `appmodel.h` and
`namespace Windows.ApplicationModel`.

**NOTE:** This functionality is available today but requires multiple steps, and understanding
packages may have multiple locations and how to search across them. This puts a high bar on all
developers using MSIX to do the legwork, and doing so correctly, consistently and efficiently. These
new APIs provide a consistent, correct and easy to use solution.

### 3.1.1. Package Location Search Order

The search order for a package's locations is:

1. External (User or Machine)
2. Mutable
3. Install

**NOTE:** If a package has a UserExternal location then MachineExternal location is not checked
(even if the package has one).

### 3.1.2. FindPackageFileInPackage

`FindPackageFileInPackage(packageFullName, filename[, options])` searches the location(s) of a specific package
for the specified file, per the algorithm:

```
IF SearchUserExternalPath OR SearchMachineExternalPath in options
    IF SearchUserExternalPath AND SearchMachineExternalPath in options
        path = package.GetEffectiveExternalPath()
    ELSEIF SearchUserExternalPath in options
        path = package.GetUserExternalPath()
    ELSEIF SearchMachineExternalPath in options
        path = package.GetMachineExternalPath()     
    IF path != null AND FileExists(path\filename)
        RETURN path\filename       

IF SearchMutablePath in options
    path = package.GetMutablePath()
    IF path != null AND FileExists(path\filename)
        RETURN path\filename

path = package.GetInstallPath()
IF FileExists(path\filename)
    RETURN path\filename

// Not Found
RETURN null
```

Overloads without the `options` parameter use the default (search everything).


### 3.1.3. FindPackageFileInPackageGraph

`FindPackageFileInPackageGraph(filename[, options])` searches the location(s) of each package in the caller's
package graph for the specified file, per the algorithm:

```
FOREACH package IN GetPackageGraph():

    file = FindPackageFileInPackage(package.fullname, filename)
    IF file != null
        RETURN file

NEXT

// Not found
RETURN null
```

Overloads without the `options` parameter use the default (search everything).

# 4. Examples

## 4.1. FindPackageFileInPackage

Locate `resource.pri` in the package `Contoso_1.2.3.4_x64__1234567890abc`.

### 4.1.1. C# Example

```c#
using Microsoft.Windows.ApplicationModel;

string GetResourcesPri(string packageFullName)
{
    var absoluteFilename = Package.FindPackageFileInPackage(packageFullName, "resources.pri");
    if (absoluteFilename == null)
    {
        Console.WriteLine($"ERROR: resources.pri not found for {packageFullName}");
        throw new FileNotFoundException($"resources.pri not found for {packageFullName}");
    }
    return absoluteFilename;
}
```

### 4.1.2. C++ Example

```c++
wil::unique_process_heap_string GetResourcesPri(PCWSTR packageFullName)
{
    FindPackageFileOptions options{};
    wil::unique_process_heap_string absoluteFilename;
    const HRESULT hr{ LOG_IF_FAILED(FindPackageFileInPackage(
        packageFullName, L"resources.pri", options, wistd::out_param(absoluteFilename))) };
    if (FAILED(hr))
    {
        wprintf(L"ERROR: 0x%08X locating resources.pri for %ls\n", hr, packageFullName);
        THROW_HR(hr);
    }
    else if (!absoluteFilename)
    {
        wprintf(L"ERROR: resources.pri not found for %ls\n", hr, packageFullName);
        THROW_WIN32_ERROR(ERROR_FILE_NOT_FOUND);
    }
    return absoluteFilename;
}
```

## 4.2. FindPackageFileInPackage with Options

Locate `resource.pri` in the package `Contoso_1.2.3.4_x64__1234567890abc` but ignore the package's
Mutable location.

### 4.2.1. C# Example

```c#
using Microsoft.Windows.ApplicationModel;

string GetResourcesPri(string packageFullName)
{
    var options = FindPackageFileOptions.SearchInstallPath |
                  FindPackageFileOptions.SearchMachineExternalPath |
                  FindPackageFileOptions.SearchUserExternalPath;
    var absoluteFilename = Package.FindPackageFileInPackage(packageFullName, "resources.pri", options);
    if (absoluteFilename == null)
    {
        Console.WriteLine($"ERROR: resources.pri not found for {packageFullName}");
        throw new FileNotFoundException($"resources.pri not found for {packageFullName}");
    }
    return absoluteFilename;
}
```

### 4.2.2. C++ Example

```c++
wil::unique_process_heap_string GetResourcesPri(PCWSTR packageFullName)
{
    FindPackageFileOptions options{ FindPackageFileOptions_SearchInstallPath |
                                    FindPackageFileOptions_SearchMachineExternalPath |
                                    FindPackageFileOptions_SearchUserExternalPath };
    wil::unique_process_heap_string absoluteFilename;
    const HRESULT hr{ LOG_IF_FAILED(FindPackageFileInPackage(
        packageFullName, L"resources.pri", options, wistd::out_param(absoluteFilename))) };
    if (FAILED(hr))
    {
        wprintf(L"ERROR: 0x%08X locating resources.pri for %ls\n", hr, packageFullName);
        THROW_HR(hr);
    }
    else if (!absoluteFilename)
    {
        wprintf(L"ERROR: resources.pri not found for %ls\n", hr, packageFullName);
        THROW_WIN32_ERROR(ERROR_FILE_NOT_FOUND);
    }
    return absoluteFilename;
}
```

## 4.3. FindPackageFileInPackageGraph

Locate `resource.pri` in the current process' package graph.

### 4.3.1. C# Example

```c#
using Microsoft.Windows.ApplicationModel;

string GetXamlWinMD()
{
    var absoluteFilename = Package.FindPackageFileInPackageGraph("Microsoft.UI.Xaml.winmd");
    if (absoluteFilename == null)
    {
        Console.WriteLine($"ERROR: resources.pri not found for {packageFullName}");
        throw new FileNotFoundException($"resources.pri not found for {packageFullName}");
    }
    return absoluteFilename;
}
```

### 4.3.2. C++ Example

```c++
wil::unique_process_heap_string GetXamlWinMD()
{
    FindPackageFileOptions options{};
    wil::unique_process_heap_string absoluteFilename;
    const HRESULT hr{ LOG_IF_FAILED(FindPackageFileInPackageGraph(
        L"Microsoft.UI.Xaml.winmd", options, wistd::out_param(absoluteFilename))) };
    if (FAILED(hr))
    {
        wprintf(L"ERROR: 0x%08X locating resources.pri for %ls\n", hr, packageFullName);
        THROW_HR(hr);
    }
    else if (!absoluteFilename)
    {
        wprintf(L"ERROR: resources.pri not found for %ls\n", hr, packageFullName);
        THROW_WIN32_ERROR(ERROR_FILE_NOT_FOUND);
    }
    return absoluteFilename;
}
```

## 4.4. FindPackageFileInPackageGraph with Options

Locate `resource.pri` in the current process' package graph but ignore Mutable locations.

### 4.4.1. C# Example

```c#
using Microsoft.Windows.ApplicationModel;

string GetXamlWinMD()
{
    var options = FindPackageFileOptions.SearchInstallPath |
                  FindPackageFileOptions.SearchMachineExternalPath |
                  FindPackageFileOptions.SearchUserExternalPath;
    var absoluteFilename = Package.FindPackageFileInPackageGraph("Microsoft.UI.Xaml.winmd", options);
    if (absoluteFilename == null)
    {
        Console.WriteLine($"ERROR: resources.pri not found for {packageFullName}");
        throw new FileNotFoundException($"resources.pri not found for {packageFullName}");
    }
    return absoluteFilename;
}
```

### 4.4.2. C++ Example

```c++
wil::unique_process_heap_string GetXamlWinMD()
{
    FindPackageFileOptions options{ FindPackageFileOptions_SearchInstallPath |
                                    FindPackageFileOptions_SearchMachineExternalPath |
                                    FindPackageFileOptions_SearchUserExternalPath };
    wil::unique_process_heap_string absoluteFilename;
    const HRESULT hr{ LOG_IF_FAILED(FindPackageFileInPackageGraph(
        L"Microsoft.UI.Xaml.winmd", options, wistd::out_param(absoluteFilename))) };
    if (FAILED(hr))
    {
        wprintf(L"ERROR: 0x%08X locating resources.pri for %ls\n", hr, packageFullName);
        THROW_HR(hr);
    }
    else if (!absoluteFilename)
    {
        wprintf(L"ERROR: resources.pri not found for %ls\n", hr, packageFullName);
        THROW_WIN32_ERROR(ERROR_FILE_NOT_FOUND);
    }
    return absoluteFilename;
}
```

# 5. Remarks

## 5.1. Platform Support

This API is available on Windows >= 10.0.17763.0 (aka RS5).

# 6. API Details

## 6.1. WinRT API

```c# (but really MIDL3)
namespace Microsoft.Windows.ApplicationModel
{
    [contractversion(1)]
    apicontract PackageRuntimeContract{};

    /// Options for Package.FindPackageFile*() methods
    [contract(PackageRuntimeContract, 1)]
    enum FindPackageFileOptions
    {
        /// Default behavior
        None = 0,

        /// Include the package's Install path in the file search order
        SearchInstallPath = 1,

        /// Include the package's Mutable path (if it has one) in the file search order
        SearchMutablePath = 2,

        /// Include the package's Machine External path (if it has one) in the file search order
        SearchMachineExternalPath = 3,

        /// Include the package's User External path (if it has one) in the file search order
        SearchUserExternalPath = 4,
    }

    [contract(PackageRuntimeContract, 1)]
    runtimeclass Package
    {
        /// Return the absolute path to the file in the package.
        /// @param packageFullName the package, or empty string ("") to use the current process' package identity.
        /// @param filename file to locate.
        /// @param packageFile absolute path to the packaged file, or empty string ("") if not found.
        /// @note The package path search order is External(User or Machine) -> Mutable -> Install.
        /// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
        /// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
        /// @see FindPackageFileInPackageGraph
        static String FindPackageFileInPackage(String packageFullName, String filename);

        /// Return the absolute path to the file in the package.
        /// @param packageFullName the package, or empty string ("") to use the current process' package identity.
        /// @param filename file to locate.
        /// @param packageFile absolute path to the packaged file, or empty string ("") if not found.
        /// @param options options for the search.
        /// @note The package path search order is External(User or Machine) -> Mutable -> Install.
        /// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
        /// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
        /// @see FindPackageFileInPackageGraph
        /// @see FindPackageFileOptions
        [method_name("FindPackageFileInPackageWithOptions")]
        static String FindPackageFileInPackage(String packageFullName, String filename, FindPackageFileOptions options);

        /// Return the absolute path to the file in the package graph.
        /// @param filename file to locate.
        /// @param packageFile absolute path to the packaged file, or empty string ("") if not found.
        /// @note The package paths search order is External(User or Machine) -> Mutable -> Install.
        /// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
        /// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
        /// @see FindPackageFileInPackage
        static String FindPackageFileInPackageGraph(String filename);

        /// Return the absolute path to the file in the package graph.
        /// @param filename file to locate.
        /// @param packageFile absolute path to the packaged file, or empty string ("") if not found.
        /// @param options options for the search.
        /// @note The package paths search order is External(User or Machine) -> Mutable -> Install.
        /// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
        /// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
        /// @see FindPackageFileInPackage
        /// @see FindPackageFileOptions
        [method_name("FindPackageFileInPackageGraphWithOptions")]
        static String FindPackageFileInPackageGraph(String filename, FindPackageFileOptions options);
    };
}
```

## 6.2. Win32 API

```c
// package_runtime.h

// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(PACKAGE_RUNTIME_H)
#define PACKAGE_RUNTIME_H

/// Options for FindPackageFile*() functions
typedef enum FindPackageFileOptions
{
    /// Default behavior
    FindPackageFileOptions_None = 0,

    /// Include the package's Install path in the file search order
    FindPackageFileOptions_SearchInstallPath = 1,

    /// Include the package's Mutable path (if it has one) in the file search order
    FindPackageFileOptions_SearchMutablePath = 2,

    /// Include the package's Machine External path (if it has one) in the file search order
    FindPackageFileOptions_SearchMachineExternalPath = 3,

    /// Include the package's User External path (if it has one) in the file search order
    FindPackageFileOptions_SearchUserExternalPath = 4,
}

/// Return the absolute path to the file in the package.
/// @param packageFullName the package, or NULL or "" to use the current process' package identity.
/// @param filename file to locate.
/// @param options options for the search.
/// @param packageFile absolute path to the packaged file, or NULL if not found. Allocated via HeapAlloc; use HeapFree to deallocate
/// @note The package path search order is External(User or Machine) -> Mutable -> Install.
/// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
/// @see FindPackageFileInPackageGraph()
/// @see FindPackageFileOptions
STDAPI FindPackageFileInPackage(
    PCWSTR packageFullName,
    _In_ PCWSTR filename,
    _In_ FindPackageFileOptions options,
    _Outptr_result_maybenull_ PWSTR* packageFile) noexcept;

/// Return the absolute path to the file in the caller's package graph.
/// @param filename file to locate.
/// @param options options for the search.
/// @param packageFile absolute path to the packaged file, or NULL if not found. Allocated via HeapAlloc; use HeapFree to deallocate
/// @note The search order is External(User or Machine) -> Mutable -> Install for each package in the package graph.
/// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
/// @see FindPackageFileInPackage()
/// @see FindPackageFileOptions
STDAPI FindPackageFileInPackageGraph(
    _In_ PCWSTR filename,
    _In_ FindPackageFileOptions options,
    _Outptr_result_maybenull_ PWSTR* packageFile) noexcept;

#endif // PACKAGE_RUNTIME_H
```
