// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

namespace Test::Packages::FrameworkMathAdd
{
    constexpr PCWSTR c_PackageDirName = L"Framework.Math.Add";
    constexpr PCWSTR c_PackageFamilyName = L"Framework.Math.Add_8wekyb3d8bbwe";
    constexpr PCWSTR c_PackageFullName = L"Framework.Math.Add_1.2.3.4_neutral__8wekyb3d8bbwe";
}

namespace Test::Packages::FrameworkMathMultiply
{
    constexpr PCWSTR c_PackageDirName = L"Framework.Math.Multiply";
    constexpr PCWSTR c_PackageFamilyName = L"Framework.Math.Multiply_8wekyb3d8bbwe";
    constexpr PCWSTR c_PackageFullName = L"Framework.Math.Multiply_1.2.3.4_neutral__8wekyb3d8bbwe";
}

namespace Test::Packages::MainSidecar
{
    constexpr PCWSTR c_PackageDirName = L"Main.Sidecar";
    constexpr PCWSTR c_PackageFamilyName = L"ProjectReunion.Test.DynDep.Main.Sidecar_8wekyb3d8bbwe";
    constexpr PCWSTR c_PackageFullName = L"ProjectReunion.Test.DynDep.Main.Sidecar_4.1.1967.333_neutral__8wekyb3d8bbwe";

    // coclass MyLifetimeManager == CLSID {32E7CF70-038C-429a-BD49-88850F1B4A11}
    // See winmain.cpp in Main.Sidecar.LifetimeManager project for more details
    constexpr GUID c_MyLifetimeManagerClsid
    {
        0x32e7cf70, 0x038c, 0x429a, { 0xbd, 0x49, 0x88, 0x85, 0x0f, 0x1b, 0x4a, 0x11 }
    };
}

namespace Test::Packages::ProjectReunionFramework
{
    constexpr PCWSTR c_PackageDirName = L"Microsoft.ProjectReunion.Framework";
    constexpr PCWSTR c_PackageFamilyName = L"Microsoft.ProjectReunion.Framework_8wekyb3d8bbwe";
    constexpr PCWSTR c_PackageFullName = L"Microsoft.ProjectReunion.Framework_0.1.2.3_neutral__8wekyb3d8bbwe";
}

namespace Test::Packages
{
    void AddPackageIfNecessary(PCWSTR packageDirName, PCWSTR packageFullName);

    void AddPackage(PCWSTR packageDirName, PCWSTR packageFullName);

    void RemovePackageIfNecessary(PCWSTR packageFullName);

    void RemovePackage(PCWSTR packageFullName);

    bool IsPackageRegistered(PCWSTR packageFullName);

    std::wstring GetPackagePath(PCWSTR packageFullName);

    void AddPackage_MainSidecar();

    void RemovePackage_MainSidecar();

    void AddPackage_ProjectReunionFramework();

    void RemovePackage_ProjectReunionFramework();

    std::filesystem::path GetMainSidecarMsixPath();

    std::filesystem::path GetProjectReunionFrameworkMsixPath();
}
