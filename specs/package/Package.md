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
  - [3.1. Find a packaged file](#31-find-a-packaged-file)
    - [3.1.1. Package Location Search Order](#311-package-location-search-order)
    - [3.1.2. GetPackageFilePath](#312-getpackagefilepath)
    - [3.1.3. GetPackageFilePathInPackageGraph](#313-getpackagefilepathinpackagegraph)
- [4. Examples](#4-examples)
  - [4.1. Get a file path in the current process' main package](#41-get-a-file-path-in-the-current-process-main-package)
    - [4.1.1. C# Example](#411-c-example)
    - [4.1.2. C++ Example](#412-c-example)
  - [4.2. Get a file path in a specific package](#42-get-a-file-path-in-a-specific-package)
    - [4.2.1. C# Example](#421-c-example)
    - [4.2.2. C++ Example](#422-c-example)
  - [4.3. Get a file path in a specific package with options](#43-get-a-file-path-in-a-specific-package-with-options)
    - [4.3.1. C# Example](#431-c-example)
    - [4.3.2. C++ Example](#432-c-example)
  - [4.4. Get a file path in the current process' package graph](#44-get-a-file-path-in-the-current-process-package-graph)
    - [4.4.1. C# Example](#441-c-example)
    - [4.4.2. C++ Example](#442-c-example)
  - [4.5. Get a file path in the current process' package graph with options](#45-get-a-file-path-in-the-current-process-package-graph-with-options)
    - [4.5.1. C# Example](#451-c-example)
    - [4.5.2. C++ Example](#452-c-example)
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

* Find a packaged file in a package
* Find a packaged file in the current process' package graph

## 3.1. Find a packaged file

An MSIX package contains...

* [Footprint files](https://learn.microsoft.com/windows/win32/api/appxpackaging/ne-appxpackaging-appx_footprint_file_type)
  e.g. `AppxManifest.xml`
* Content files i.e. all other files (*.exe, *.dll, *.jpg, *.dat, ...)

A package always has an Install location and may also have other locations:

* Install location
* Mutable location
* Machine External location
* User External location

Locations other than the Install location are optional and may occur in any combination.

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
ByDesign, sometimes due to bugs). Changing behavior by reducing location awareness poses appcompat
risks leading some features needing to broaden their support to search across multiple locations.

The `find package file` APIs search the filesystem for a specified file as appropriate across the
package(s)' location(s).

The APIs are available as Win32 exports and WinRT, similar to existing APIs in `appmodel.h` and
`namespace Windows.ApplicationModel`.

**NOTE:** This functionality is available today but requires multiple steps, and understanding
that packages may have multiple locations and how to search across them. This puts a high bar on all
developers using MSIX to do the legwork, and doing so correctly, consistently and efficiently. These
new APIs provide a consistent, correct and easy to use solution.

### 3.1.1. Package Location Search Order

The search order for a package's locations is:

1. External (User or Machine)
2. Mutable
3. Install

**NOTE:** If a package has a UserExternal location then MachineExternal location is not checked
(even if the package has one).

### 3.1.2. Get file path for a package

`Package.GetFilePath(filename[packageFullName, [, options]])` searches the location(s)
of a package for the specified file, per the algorithm:

```
IF packageFullName not specified
    IF current process has package identity
        package = GetPackageForCurrentProcess()
    ELSE current process lacks package identity
        throw APPMODEL_ERROR_NO_PACKAGE
ELSE
    package = GetPackage(packageFullName)

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


### 3.1.3. Get file path in current process' package graph

`PackageGraph.GetFilePath(filename[, options])` searches the location(s) of each package in the caller's
package graph for the specified file, per the algorithm:

```
FOREACH pkg IN GetPackageGraph():
    file = Package.GetFilePath(filename, pkg.fullname)
    IF file != null
        RETURN file
NEXT

// Not found
RETURN null
```

Overloads without the `options` parameter use the default (search everything).

# 4. Examples

## 4.1. Get a file path in the current process' main package

Locate `resources.pri` in the main package for the current packaged process.

### 4.1.1. C# Example

```c#
using Microsoft.Windows.ApplicationModel;

string GetResourcesPri()
{
    var absoluteFilename = Package.GetFilePath("resources.pri");
    if (absoluteFilename == null)
    {
        Console.WriteLine($"ERROR: resources.pri not found for {Package.Current.Id.FullName}");
        throw new FileNotFoundException($"resources.pri not found for {Package.Current.Id.FullName}");
    }
    return absoluteFilename;
}
```

### 4.1.2. C++ Example

```c++
std::wstring GetResourcesPri(PCWSTR packageFullName)
{
    GetPackageFilePathOptions options{};
    wil::unique_process_heap_string absoluteFilename;
    const HRESULT hr{ GetPackageFilePath(
        nullptr, L"resources.pri", options, wistd::out_param(absoluteFilename)) };
    if (FAILED_LOG(hr))
    {
        wprintf(L"ERROR: 0x%08X locating resources.pri in the current process' main package\n", hr);
        THROW_HR(hr);
    }
    else if (!absoluteFilename)
    {
        wprintf(L"ERROR: resources.pri not found in the current process' main package\n");
        THROW_WIN32_ERROR(ERROR_FILE_NOT_FOUND);
    }
    return std::wstring{ absoluteFilename.get() };
}
```

## 4.2. Get a file path in a specific package

Locate `resources.pri` in the package `Contoso_1.2.3.4_x64__1234567890abc`.

### 4.2.1. C# Example

```c#
using Microsoft.Windows.ApplicationModel;

string GetResourcesPri(string packageFullName)
{
    var absoluteFilename = Package.GetFilePath("resources.pri", packageFullName);
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
std::wstring GetResourcesPri(PCWSTR packageFullName)
{
    GetPackageFilePathOptions options{};
    wil::unique_process_heap_string absoluteFilename;
    const HRESULT hr{ GetPackageFilePath(
        packageFullName, L"resources.pri", options, wistd::out_param(absoluteFilename)) };
    if (FAILED_LOG(hr))
    {
        wprintf(L"ERROR: 0x%08X locating resources.pri for %ls\n", hr, packageFullName);
        THROW_HR(hr);
    }
    else if (!absoluteFilename)
    {
        wprintf(L"ERROR: resources.pri not found for %ls\n", hr, packageFullName);
        THROW_WIN32_ERROR(ERROR_FILE_NOT_FOUND);
    }
    return std::wstring{ absoluteFilename.get() };
}
```

## 4.3. Get a file path in a specific package with options

Locate `resources.pri` in the package `Contoso_1.2.3.4_x64__1234567890abc` but ignore the package's
Mutable location.

### 4.3.1. C# Example

```c#
using Microsoft.Windows.ApplicationModel;

string GetResourcesPri(string packageFullName)
{
    var options = GetPackageFilePathOptions.SearchInstallPath |
                  GetPackageFilePathOptions.SearchMachineExternalPath |
                  GetPackageFilePathOptions.SearchUserExternalPath;
    var absoluteFilename = Package.GetFilePath("resources.pri", packageFullName, options);
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
std::wstring GetResourcesPri(PCWSTR packageFullName)
{
    GetPackageFilePathOptions options{ GetPackageFilePathOptions_SearchInstallPath |
                                       GetPackageFilePathOptions_SearchMachineExternalPath |
                                       GetPackageFilePathOptions_SearchUserExternalPath };
    wil::unique_process_heap_string absoluteFilename;
    const HRESULT hr{ GetPackageFilePath(
        packageFullName, L"resources.pri", options, wistd::out_param(absoluteFilename)) };
    if (FAILED_LOG(hr))
    {
        wprintf(L"ERROR: 0x%08X locating resources.pri for %ls\n", hr, packageFullName);
        THROW_HR(hr);
    }
    else if (!absoluteFilename)
    {
        wprintf(L"ERROR: resources.pri not found for %ls\n", hr, packageFullName);
        THROW_WIN32_ERROR(ERROR_FILE_NOT_FOUND);
    }
    return std::wstring{ absoluteFilename.get() };
}
```

## 4.4. Get a file path in the current process' package graph

Locate `Microsoft.UI.Xaml.winmd` in the current process' package graph.

### 4.4.1. C# Example

```c#
using Microsoft.Windows.ApplicationModel;

string GetXamlWinMD()
{
    var absoluteFilename = PackageGraph.GetFilePath("Microsoft.UI.Xaml.winmd");
    if (absoluteFilename == null)
    {
        Console.WriteLine($"ERROR: Microsoft.UI.Xaml.winmd pri not found");
        throw new FileNotFoundException($"Microsoft.UI.Xaml.winmd not found");
    }
    return absoluteFilename;
}
```

### 4.4.2. C++ Example

```c++
std::wstring GetXamlWinMD()
{
    GetPackageFilePathOptions options{};
    wil::unique_process_heap_string absoluteFilename;
    const HRESULT hr{ GetPackageFilePathInPackageGraph(
        L"Microsoft.UI.Xaml.winmd", options, wistd::out_param(absoluteFilename)) };
    if (FAILED_LOG(hr))
    {
        wprintf(L"ERROR: 0x%08X locating Microsoft.UI.Xaml.winmd\n", hr);
        THROW_HR(hr);
    }
    else if (!absoluteFilename)
    {
        wprintf(L"ERROR: Microsoft.UI.Xaml.winmd not found\n", hr);
        THROW_WIN32_ERROR(ERROR_FILE_NOT_FOUND);
    }
    return std::wstring{ absoluteFilename.get() };
}
```

## 4.5. Get a file path in the current process' package graph with options

Locate `Microsoft.UI.Xaml.winmd` in the current process' package graph but ignore Mutable locations,
Resource and Resource packages and HostRuntime dependencies.

### 4.5.1. C# Example

```c#
using Microsoft.Windows.ApplicationModel;

string GetXamlWinMD()
{
    var options = GetPackageFilePathOptions.SearchInstallPath |
                  GetPackageFilePathOptions.SearchMachineExternalPath |
                  GetPackageFilePathOptions.SearchUserExternalPath |
                  GetPackageFilePathOptions.SearchMainPackages |
                  GetPackageFilePathOptions.SearchFrameworkPath |
                  GetPackageFilePathOptions.SearchOptionalPath;
    var absoluteFilename = PackageGraph.GetFilePath("Microsoft.UI.Xaml.winmd", options);
    if (absoluteFilename == null)
    {
        Console.WriteLine($"ERROR: Microsoft.UI.Xaml.winmd not found");
        throw new FileNotFoundException($"Microsoft.UI.Xaml.winmd not found");
    }
    return absoluteFilename;
}
```

### 4.5.2. C++ Example

```c++
std::wstring GetXamlWinMD()
{
    GetPackageFilePathOptions options{ GetPackageFilePathOptions_SearchInstallPath |
                                       GetPackageFilePathOptions_SearchMachineExternalPath |
                                       GetPackageFilePathOptions_SearchUserExternalPath |
                                       GetPackageFilePathOptions_SearchMainPackages |
                                       GetPackageFilePathOptions_SearchFrameworkPath |
                                       GetPackageFilePathOptions_SearchOptionalPath };
    wil::unique_process_heap_string absoluteFilename;
    const HRESULT hr{ GetPackageFilePathInPackageGraph(
        L"Microsoft.UI.Xaml.winmd", options, wistd::out_param(absoluteFilename)) };
    if (FAILED_LOG(hr))
    {
        wprintf(L"ERROR: 0x%08X locating Microsoft.UI.Xaml.winmd\n", hr);
        THROW_HR(hr);
    }
    else if (!absoluteFilename)
    {
        wprintf(L"ERROR: Microsoft.UI.Xaml.winmd not found\n", hr);
        THROW_WIN32_ERROR(ERROR_FILE_NOT_FOUND);
    }
    return std::wstring{ absoluteFilename.get() };
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

    /// Options for GetFilePath*()
    /// @see Package.GetFilePath
    /// @see PackageGraph.GetFilePath
    [contract(PackageRuntimeContract, 1)]
    [flags]
    enum GetFilePathOptions
    {
        /// Default behavior
        None = 0,

        /// Include the package's Install path in the file search order
        /// @note If SearchInstallPath, SearchMutablePath, SearchMachineExternalPath and SearchUserExternalPath
        ///        are omitted then all locations are searched (i.e. specify all or none yields the same result).
        SearchInstallPath = 0x0001,

        /// Include the package's Mutable path (if it has one) in the file search order
        /// @note If SearchInstallPath, SearchMutablePath, SearchMachineExternalPath and SearchUserExternalPath
        ///        are omitted then all locations are searched (i.e. specify all or none yields the same result).
        SearchMutablePath = 0x0002,

        /// Include the package's Machine External path (if it has one) in the file search order
        /// @note If SearchInstallPath, SearchMutablePath, SearchMachineExternalPath and SearchUserExternalPath
        ///        are omitted then all locations are searched (i.e. specify all or none yields the same result).
        SearchMachineExternalPath = 0x0004,

        /// Include the package's User External path (if it has one) in the file search order
        /// @note If SearchInstallPath, SearchMutablePath, SearchMachineExternalPath and SearchUserExternalPath
        ///        are omitted then all locations are searched (i.e. specify all or none yields the same result).
        SearchUserExternalPath = 0x0008,

        /// Include Main packages in the file search order
        /// @note If SearchMainPackages, SearchFrameworkPackages, SearchOptionalPackages,
        ///       SearchResourcePackages, SearchBundlePackages and SearchHostRuntimeDependencies
        ///       are omitted then all package types are searched (i.e. specify all or none
        ///       yields the same result).
        SearchMainPackages = 0x0010,

        /// Include Framework packages in the file search order
        /// @note If SearchMainPackages, SearchFrameworkPackages, SearchOptionalPackages,
        ///       SearchResourcePackages, SearchBundlePackages and SearchHostRuntimeDependencies
        ///       are omitted then all package types are searched (i.e. specify all or none
        ///       yields the same result).
        SearchFrameworkPackages = 0x0020,

        /// Include Optional packages in the file search order
        /// @note If SearchMainPackages, SearchFrameworkPackages, SearchOptionalPackages,
        ///       SearchResourcePackages, SearchBundlePackages and SearchHostRuntimeDependencies
        ///       are omitted then all package types are searched (i.e. specify all or none
        ///       yields the same result).
        SearchOptionalPackages = 0x0040,

        /// Include Resource packages in the file search order
        /// @note If SearchMainPackages, SearchFrameworkPackages, SearchOptionalPackages,
        ///       SearchResourcePackages, SearchBundlePackages and SearchHostRuntimeDependencies
        ///       are omitted then all package types are searched (i.e. specify all or none
        ///       yields the same result).
        SearchResourcePackages = 0x0080,

        /// Include Bundle packages in the file search order
        /// @note If SearchMainPackages, SearchFrameworkPackages, SearchOptionalPackages,
        ///       SearchResourcePackages, SearchBundlePackages and SearchHostRuntimeDependencies
        ///       are omitted then all package types are searched (i.e. specify all or none
        ///       yields the same result).
        SearchBundlePackages = 0x0100,

        /// Include HostRuntime dependencies in the file search order
        /// @note If SearchMainPackages, SearchFrameworkPackages, SearchOptionalPackages,
        ///       SearchResourcePackages, SearchBundlePackages and SearchHostRuntimeDependencies
        ///       are omitted then all package types are searched (i.e. specify all or none
        ///       yields the same result).
        SearchHostRuntimeDependencies = 0x0200,
    };

    [contract(PackageRuntimeContract, 1)]
    runtimeclass Package
    {
        /// Return the absolute path to the file in the current process' package. This uses the
        /// current process' package identity, or fails with HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE)
        /// if the process lacks package identity.
        /// @param filename file to locate.
        /// @param packageFile absolute path to the packaged file, or empty string ("") if not found.
        /// @note The package path search order is External(User or Machine) -> Mutable -> Install.
        /// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
        /// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
        /// @see PackageGraph.GetFilePath
        static String GetFilePath(String filename);

        /// Return the absolute path to the file in the package.
        /// @param filename file to locate.
        /// @param packageFullName the package.
        /// @param packageFile absolute path to the packaged file, or empty string ("") if not found.
        /// @note The package path search order is External(User or Machine) -> Mutable -> Install.
        /// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
        /// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
        /// @see PackageGraph.GetFilePath
        [method_name("GetFilePathInPackage")]
        static String GetFilePath(String filename, String packageFullName);

        /// Return the absolute path to the file in the package.
        /// @param filename file to locate.
        /// @param packageFullName the package.
        /// @param packageFile absolute path to the packaged file, or empty string ("") if not found.
        /// @param options options for the search.
        /// @note The package path search order is External(User or Machine) -> Mutable -> Install.
        /// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
        /// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
        /// @see PackageGraph.GetFilePath
        /// @see PackageGraph.GetFilePathOptions
        [method_name("GetFilePathInPackageWithOptions")]
        static String GetFilePath(String filename, String packageFullName, GetFilePathOptions options);
    }

    [contract(PackageRuntimeContract, 1)]
    runtimeclass PackageGraph
    {
        /// Return the absolute path to the file in the package graph.
        /// @param filename file to locate.
        /// @param packageFile absolute path to the packaged file, or empty string ("") if not found.
        /// @note The package paths search order is External(User or Machine) -> Mutable -> Install.
        /// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
        /// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
        /// @see Package.GetFilePath
        static String GetFilePath(String filename);

        /// Return the absolute path to the file in the package graph.
        /// @param filename file to locate.
        /// @param packageFile absolute path to the packaged file, or empty string ("") if not found.
        /// @param options options for the search.
        /// @note The package paths search order is External(User or Machine) -> Mutable -> Install.
        /// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
        /// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
        /// @see Package.GetFilePath
        /// @see GetPackageFilePathOptions
        [method_name("GetFilePathWithOptions")]
        static String GetFilePath(String filename, GetFilePathOptions options);
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

/// Options for GetPackageFilePath*() functions
typedef enum GetPackageFilePathOptions
{
    /// Default behavior
    GetPackageFilePathOptions_None = 0,

    /// Include the package's Install path in the file search order
    /// @note If GetPackageFilePathOptions_SearchInstallPath, GetPackageFilePathOptions_SearchMutablePath,
    ///        GetPackageFilePathOptions_SearchMachineExternalPath and GetPackageFilePathOptions_SearchUserExternalPath
    ///        are omitted then all locations are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchInstallPath = 0x0001,

    /// Include the package's Mutable path (if it has one) in the file search order
    /// @note If GetPackageFilePathOptions_SearchInstallPath, GetPackageFilePathOptions_SearchMutablePath,
    ///        GetPackageFilePathOptions_SearchMachineExternalPath and GetPackageFilePathOptions_SearchUserExternalPath
    ///        are omitted then all locations are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchMutablePath = 0x0002,

    /// Include the package's Machine External path (if it has one) in the file search order
    /// @note If GetPackageFilePathOptions_SearchInstallPath, GetPackageFilePathOptions_SearchMutablePath,
    ///        GetPackageFilePathOptions_SearchMachineExternalPath and GetPackageFilePathOptions_SearchUserExternalPath
    ///        are omitted then all locations are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchMachineExternalPath = 0x0004,

    /// Include the package's User External path (if it has one) in the file search order
    /// @note If GetPackageFilePathOptions_SearchInstallPath, GetPackageFilePathOptions_SearchMutablePath,
    ///        GetPackageFilePathOptions_SearchMachineExternalPath and GetPackageFilePathOptions_SearchUserExternalPath
    ///        are omitted then all locations are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchUserExternalPath = 0x0008,

    /// Include Main packages in the file search order
    /// @note If GetPackageFilePathOptions_SearchMainPackages, GetPackageFilePathOptions_SearchFrameworkPackages,
    ///       GetPackageFilePathOptions_SearchOptionalPackages, GetPackageFilePathOptions_SearchResourcePackages,
    ///       GetPackageFilePathOptions_SearchBundlePackages and GetPackageFilePathOptions_SearchHostRuntimeDependencies
    ///       are omitted then all package types are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchMainPackages = 0x0010,

    /// Include Framework packages in the file search order
    /// @note If GetPackageFilePathOptions_SearchMainPackages, GetPackageFilePathOptions_SearchFrameworkPackages,
    ///       GetPackageFilePathOptions_SearchOptionalPackages, GetPackageFilePathOptions_SearchResourcePackages,
    ///       GetPackageFilePathOptions_SearchBundlePackages and GetPackageFilePathOptions_SearchHostRuntimeDependencies
    ///       are omitted then all package types are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchFrameworkPackages = 0x0020,

    /// Include Optional packages in the file search order
    /// @note If GetPackageFilePathOptions_SearchMainPackages, GetPackageFilePathOptions_SearchFrameworkPackages,
    ///       GetPackageFilePathOptions_SearchOptionalPackages, GetPackageFilePathOptions_SearchResourcePackages,
    ///       GetPackageFilePathOptions_SearchBundlePackages and GetPackageFilePathOptions_SearchHostRuntimeDependencies
    ///       are omitted then all package types are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchOptionalPackages = 0x0040,

    /// Include Resource packages in the file search order
    /// @note If GetPackageFilePathOptions_SearchMainPackages, GetPackageFilePathOptions_SearchFrameworkPackages,
    ///       GetPackageFilePathOptions_SearchOptionalPackages, GetPackageFilePathOptions_SearchResourcePackages,
    ///       GetPackageFilePathOptions_SearchBundlePackages and GetPackageFilePathOptions_SearchHostRuntimeDependencies
    ///       are omitted then all package types are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchResourcePackages = 0x0080,

    /// Include Bundle packages in the file search order
    /// @note If GetPackageFilePathOptions_SearchMainPackages, GetPackageFilePathOptions_SearchFrameworkPackages,
    ///       GetPackageFilePathOptions_SearchOptionalPackages, GetPackageFilePathOptions_SearchResourcePackages,
    ///       GetPackageFilePathOptions_SearchBundlePackages and GetPackageFilePathOptions_SearchHostRuntimeDependencies
    ///       are omitted then all package types are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchBundlePackages = 0x0100,

    /// Include HostRuntime dependencies in the file search order
    /// @note If GetPackageFilePathOptions_SearchMainPackages, GetPackageFilePathOptions_SearchFrameworkPackages,
    ///       GetPackageFilePathOptions_SearchOptionalPackages, GetPackageFilePathOptions_SearchResourcePackages,
    ///       GetPackageFilePathOptions_SearchBundlePackages and GetPackageFilePathOptions_SearchHostRuntimeDependencies
    ///       are omitted then all package types are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchHostRuntimeDependencies = 0x0200,
} GetPackageFilePathOptions;
DEFINE_ENUM_FLAG_OPERATORS(GetPackageFilePathOptions)

/// Return the absolute path to the file in the package.
/// @param packageFullName the package, or NULL or "" to use the current process' package identity.
/// @param filename file to locate.
/// @param options options for the search.
/// @param packageFile absolute path to the packaged file, or NULL if not found. Allocated via HeapAlloc; use HeapFree to deallocate
/// @note The package path search order is External(User or Machine) -> Mutable -> Install.
/// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
/// @see GetPackageFilePathInPackageGraph()
/// @see GetPackageFilePathOptions
STDAPI GetPackageFilePath(
    PCWSTR packageFullName,
    _In_ PCWSTR filename,
    _In_ GetPackageFilePathOptions options,
    _Outptr_result_maybenull_ PWSTR* packageFile) noexcept;

/// Return the absolute path to the file in the caller's package graph.
/// @param filename file to locate.
/// @param options options for the search.
/// @param packageFile absolute path to the packaged file, or NULL if not found. Allocated via HeapAlloc; use HeapFree to deallocate
/// @note The search order is External(User or Machine) -> Mutable -> Install for each package in the package graph.
/// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
/// @see GetPackageFilePath()
/// @see GetPackageFilePathOptions
STDAPI GetPackageFilePathInPackageGraph(
    _In_ PCWSTR filename,
    _In_ GetPackageFilePathOptions options,
    _Outptr_result_maybenull_ PWSTR* packageFile) noexcept;

#endif // PACKAGE_RUNTIME_H
```
