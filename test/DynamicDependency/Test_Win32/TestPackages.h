// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

namespace Test::Packages::FrameworkMathAdd
{
    constexpr PCWSTR c_PackageDirName = L"Framework.Math.Add";
    constexpr PCWSTR c_PackageFamilyName = L"ProjectReunion.Test.DynDep.Fwk.Math.Add_8wekyb3d8bbwe";
    constexpr PCWSTR c_PackageFullName = L"ProjectReunion.Test.DynDep.Fwk.Math.Add_1.2.3.4_neutral__8wekyb3d8bbwe";
}

namespace Test::Packages::FrameworkMathMultiply
{
    constexpr PCWSTR c_PackageDirName = L"Framework.Math.Multiply";
    constexpr PCWSTR c_PackageFamilyName = L"ProjectReunion.Test.DynDep.Fwk.Math.Multiply_8wekyb3d8bbwe";
    constexpr PCWSTR c_PackageFullName = L"ProjectReunion.Test.DynDep.Fwk.Math.Multiply_1.2.3.4_neutral__8wekyb3d8bbwe";
}

#define TEST_PACKAGE_DDLM_NAMEPREFIX    L"ProjectReunion.Test.DDLM"
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
namespace Test::Packages::DynamicDependencyLifetimeManager
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
}

namespace Test::Packages::ProjectReunionFramework
{
    constexpr PCWSTR c_PackageDirName = L"Microsoft.ProjectReunion.Framework";
    constexpr PCWSTR c_PackageFamilyName = L"Microsoft.ProjectReunion.Framework_8wekyb3d8bbwe";
    constexpr PCWSTR c_PackageFullName = L"Microsoft.ProjectReunion.Framework_4.1.1967.333_neutral__8wekyb3d8bbwe";
}

namespace Test::Packages::DynamicDependencyDataStore
{
    constexpr PCWSTR c_PackageDirName = L"DynamicDependency.DataStore";
    constexpr PCWSTR c_PackageFamilyName = L"ProjectReunion.Test.DynDep.DataStore_8wekyb3d8bbwe";
    constexpr PCWSTR c_PackageFullName = L"ProjectReunion.Test.DynDep.DataStore_10.1.2004.0_neutral__8wekyb3d8bbwe";
}

namespace Test::Packages
{
    void AddPackageIfNecessary(PCWSTR packageDirName, PCWSTR packageFullName);

    void AddPackage(PCWSTR packageDirName, PCWSTR packageFullName);

    void RemovePackageIfNecessary(PCWSTR packageFullName);

    void RemovePackage(PCWSTR packageFullName);

    bool IsPackageRegistered(PCWSTR packageFullName);

    std::wstring GetPackagePath(PCWSTR packageFullName);

    std::wstring GetPackagePath(const std::wstring& packageFullName);

    void AddPackage_DynamicDependencyLifetimeManager();

    void RemovePackage_DynamicDependencyLifetimeManager();

    void AddPackage_ProjectReunionFramework();

    void RemovePackage_ProjectReunionFramework();

    void AddPackage_FrameworkMathAdd();

    void RemovePackage_FrameworkMathAdd();

    void AddPackage_FrameworkMathMultiply();

    void RemovePackage_FrameworkMathMultiply();

    void AddPackage_DynamicDependencyDataStore();

    void RemovePackage_DynamicDependencyDataStore();

    std::filesystem::path GetProjectReunionFrameworkMsixPath();
}
