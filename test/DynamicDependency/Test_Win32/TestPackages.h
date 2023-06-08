// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

namespace Test::Packages
{
namespace FrameworkMathAdd
{
    constexpr PCWSTR c_PackageDirName = L"Framework.Math.Add";
    constexpr PCWSTR c_PackageFamilyName = L"WindowsAppRuntime.Test.DynDep.Fwk.Math.Add_8wekyb3d8bbwe";
    constexpr PCWSTR c_PackageFullName = L"WindowsAppRuntime.Test.DynDep.Fwk.Math.Add_1.2.3.4_neutral__8wekyb3d8bbwe";
}

namespace FrameworkMathMultiply
{
    constexpr PCWSTR c_PackageDirName = L"Framework.Math.Multiply";
    constexpr PCWSTR c_PackageFamilyName = L"WindowsAppRuntime.Test.DynDep.Fwk.Math.Multiply_8wekyb3d8bbwe";
    constexpr PCWSTR c_PackageFullName = L"WindowsAppRuntime.Test.DynDep.Fwk.Math.Multiply_1.2.3.4_neutral__8wekyb3d8bbwe";
}

namespace FrameworkWidgets
{
    constexpr PCWSTR c_PackageDirName = L"Framework.Widgets";
    constexpr PCWSTR c_PackageFamilyName = L"WindowsAppRuntime.Test.DynDep.Fwk.Widgets_8wekyb3d8bbwe";
    constexpr PCWSTR c_PackageFullName = L"WindowsAppRuntime.Test.DynDep.Fwk.Widgets_1.2.3.4_neutral__8wekyb3d8bbwe";
}

#define TEST_PACKAGE_DDLM_NAMEPREFIX    L"WindowsAppRuntime.Test.DDLM"
#define TEST_PACKAGE_DDLM_VERSION       L"4.1.1967.333"
#if defined(_M_X64)
#define TEST_PACKAGE_DDLM_ARCHITECTURE  L"x64"
#elif defined(_M_IX86)
#define TEST_PACKAGE_DDLM_ARCHITECTURE  L"x86"
#elif defined(_M_ARM64)
#define TEST_PACKAGE_DDLM_ARCHITECTURE  L"arm64"
#elif defined(_M_ARM)
#define TEST_PACKAGE_DDLM_ARCHITECTURE  L"arm"
#else
#   error "Unknown processor architecture"
#endif
#define TEST_PACKAGE_DDLM_NAME          TEST_PACKAGE_DDLM_NAMEPREFIX L"-" TEST_PACKAGE_DDLM_VERSION L"-" TEST_PACKAGE_DDLM_ARCHITECTURE
#define TEST_PACKAGE_DDLM_PUBLISHERID   L"8wekyb3d8bbwe"
#define TEST_PACKAGE_DDLM_FAMILYNAME    TEST_PACKAGE_DDLM_NAME L"_" TEST_PACKAGE_DDLM_PUBLISHERID
#define TEST_PACKAGE_DDLM_FULLNAME      TEST_PACKAGE_DDLM_NAME L"_" TEST_PACKAGE_DDLM_VERSION L"_" TEST_PACKAGE_DDLM_ARCHITECTURE L"__" TEST_PACKAGE_DDLM_PUBLISHERID
namespace DynamicDependencyLifetimeManager
{
    constexpr PCWSTR c_PackageDirName = L"DynamicDependencyLifetimeManager";
    constexpr PCWSTR c_PackageNamePrefix = TEST_PACKAGE_DDLM_NAMEPREFIX;
    constexpr PCWSTR c_PackagePublisherId = TEST_PACKAGE_DDLM_PUBLISHERID;
    constexpr PCWSTR c_PackageFamilyName = TEST_PACKAGE_DDLM_FAMILYNAME;
    constexpr PCWSTR c_PackageFullName = TEST_PACKAGE_DDLM_FULLNAME;
    constexpr const PACKAGE_VERSION GetPackageVersion()
    {
        PACKAGE_VERSION version{};
        version.Major = 4;
        version.Minor = 1;
        version.Build = 1967;
        version.Revision = 333;
        return version;
    }
    constexpr const PACKAGE_VERSION c_Version = GetPackageVersion();

    constexpr const UINT32 GetPackageVersionMajorMinor()
    {
        return static_cast<UINT32>((GetPackageVersion().Major << 16) | GetPackageVersion().Minor);
    }
    constexpr const UINT32 c_Version_MajorMinor = GetPackageVersionMajorMinor();
}

#define TEST_PACKAGE_DDLMGC_NAMEPREFIX  TEST_PACKAGE_DDLM_NAMEPREFIX L".GC"
namespace DynamicDependencyLifetimeManagerGC
{
    constexpr PCWSTR c_PackageNamePrefix = TEST_PACKAGE_DDLMGC_NAMEPREFIX;
    constexpr PCWSTR c_PackagePublisherId = TEST_PACKAGE_DDLM_PUBLISHERID;
}

#define TEST_PACKAGE_DDLMGC1000_NAME    TEST_PACKAGE_DDLMGC_NAMEPREFIX L"-1.0.0.0-" TEST_PACKAGE_DDLM_ARCHITECTURE
namespace DynamicDependencyLifetimeManagerGC1000
{
    constexpr PCWSTR c_PackageDirName = L"DynamicDependencyLifetimeManagerGC1000";
    constexpr PCWSTR c_PackageNamePrefix = TEST_PACKAGE_DDLMGC_NAMEPREFIX;
    constexpr PCWSTR c_PackagePublisherId = TEST_PACKAGE_DDLM_PUBLISHERID;
    constexpr PCWSTR c_PackageFamilyName = TEST_PACKAGE_DDLMGC1000_NAME L"_" TEST_PACKAGE_DDLM_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = TEST_PACKAGE_DDLMGC1000_NAME L"_" L"1.0.0.0" L"_" TEST_PACKAGE_DDLM_ARCHITECTURE L"__" TEST_PACKAGE_DDLM_PUBLISHERID;
    constexpr const PACKAGE_VERSION GetPackageVersion()
    {
        PACKAGE_VERSION version{};
        version.Major = 1;
        version.Minor = 0;
        version.Build = 0;
        version.Revision = 0;
        return version;
    }
    constexpr const PACKAGE_VERSION c_Version = GetPackageVersion();

    constexpr const UINT32 GetPackageVersionMajorMinor()
    {
        return static_cast<UINT32>((GetPackageVersion().Major << 16) | GetPackageVersion().Minor);
    }
    constexpr const UINT32 c_Version_MajorMinor = GetPackageVersionMajorMinor();
}

#define TEST_PACKAGE_DDLMGC1010_NAME    TEST_PACKAGE_DDLMGC_NAMEPREFIX L"-1.0.1.0-" TEST_PACKAGE_DDLM_ARCHITECTURE
namespace DynamicDependencyLifetimeManagerGC1010
{
    constexpr PCWSTR c_PackageDirName = L"DynamicDependencyLifetimeManagerGC1010";
    constexpr PCWSTR c_PackageNamePrefix = TEST_PACKAGE_DDLMGC_NAMEPREFIX;
    constexpr PCWSTR c_PackagePublisherId = TEST_PACKAGE_DDLM_PUBLISHERID;
    constexpr PCWSTR c_PackageFamilyName = TEST_PACKAGE_DDLMGC1010_NAME L"_" TEST_PACKAGE_DDLM_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = TEST_PACKAGE_DDLMGC1010_NAME L"_" L"1.0.1.0" L"_" TEST_PACKAGE_DDLM_ARCHITECTURE L"__" TEST_PACKAGE_DDLM_PUBLISHERID;
    constexpr const PACKAGE_VERSION GetPackageVersion()
    {
        PACKAGE_VERSION version{};
        version.Major = 1;
        version.Minor = 0;
        version.Build = 1;
        version.Revision = 0;
        return version;
    }
    constexpr const PACKAGE_VERSION c_Version = GetPackageVersion();

    constexpr const UINT32 GetPackageVersionMajorMinor()
    {
        return static_cast<UINT32>((GetPackageVersion().Major << 16) | GetPackageVersion().Minor);
    }
    constexpr const UINT32 c_Version_MajorMinor = GetPackageVersionMajorMinor();
}

namespace WindowsAppRuntimeFramework
{
    constexpr PCWSTR c_PackageDirName = L"Microsoft.WindowsAppRuntime.Framework";
    constexpr PCWSTR c_PackageNamePrefix = L"Microsoft.WindowsAppRuntime.Framework";
    constexpr PCWSTR c_PackageFamilyName = L"Microsoft.WindowsAppRuntime.Framework-4.1_8wekyb3d8bbwe";
    constexpr PCWSTR c_PackageFullName = L"Microsoft.WindowsAppRuntime.Framework-4.1_4.1.1967.333_neutral__8wekyb3d8bbwe";
    constexpr const PACKAGE_VERSION GetPackageVersion()
    {
        PACKAGE_VERSION version{};
        version.Major = 4;
        version.Minor = 1;
        version.Build = 1967;
        version.Revision = 333;
        return version;
    }
    constexpr const PACKAGE_VERSION c_Version = GetPackageVersion();

    constexpr const UINT32 GetPackageVersionMajorMinor()
    {
        return static_cast<UINT32>((GetPackageVersion().Major << 16) | GetPackageVersion().Minor);
    }
    constexpr const UINT32 c_Version_MajorMinor = GetPackageVersionMajorMinor();
}

namespace DynamicDependencyDataStore
{
    constexpr PCWSTR c_PackageDirName = L"DynamicDependency.DataStore";
    constexpr PCWSTR c_PackageNamePrefix = L"WindowsAppRuntime.Test.DynDep.DataStore";
    constexpr PCWSTR c_PackageFamilyName = L"WindowsAppRuntime.Test.DynDep.DataStore-4.1_8wekyb3d8bbwe";
    constexpr PCWSTR c_PackageFullName = L"WindowsAppRuntime.Test.DynDep.DataStore-4.1_4.1.1967.333_neutral__8wekyb3d8bbwe";
}
namespace WindowsAppRuntimeMain = DynamicDependencyDataStore;

void AddPackageIfNecessary(PCWSTR packageDirName, PCWSTR packageFullName);

void AddPackage(PCWSTR packageDirName, PCWSTR packageFullName);

void RemovePackageIfNecessary(PCWSTR packageFullName);

void RemovePackage(PCWSTR packageFullName);

bool IsPackageRegistered(PCWSTR packageFullName);

std::wstring GetPackagePath(PCWSTR packageFullName);

std::wstring GetPackagePath(const std::wstring& packageFullName);

winrt::hstring GetPackagePath(const winrt::hstring& packageFullName);

void AddPackage_DynamicDependencyLifetimeManager();

void RemovePackage_DynamicDependencyLifetimeManager();

void AddPackageIfNecessary_DynamicDependencyLifetimeManagerGC1000();

void AddPackage_DynamicDependencyLifetimeManagerGC1000();

void RemovePackage_DynamicDependencyLifetimeManagerGC1000();

void AddPackageIfNecessary_DynamicDependencyLifetimeManagerGC1010();

void AddPackage_DynamicDependencyLifetimeManagerGC1010();

void RemovePackage_DynamicDependencyLifetimeManagerGC1010();

void AddPackage_WindowsAppRuntimeFramework();

void RemovePackage_WindowsAppRuntimeFramework();

void AddPackage_FrameworkMathAdd();

void RemovePackage_FrameworkMathAdd();

void AddPackage_FrameworkMathMultiply();

void RemovePackage_FrameworkMathMultiply();

void AddPackage_FrameworkWidgets();

void RemovePackage_FrameworkWidgets();

void AddPackage_DynamicDependencyDataStore();

void RemovePackage_DynamicDependencyDataStore();

std::filesystem::path GetWindowsAppRuntimeFrameworkMsixPath();
}
