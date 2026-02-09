// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

#include "PackageTests_PackageGraph_Base.h"

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TD = ::Test::Diagnostics;

static const winrt::hstring null_hstring;

namespace Test::Package::Tests
{
    class PackageTests_PackageGraph_Unpackaged_WinRT : PackageTests_PackageGraph_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageTests_PackageGraph_Unpackaged_WinRT)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!::WindowsVersion::IsWindows11_24H2OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageGraph tests require >= 24H2. Skipping tests");
                return true;
            }

            return PackageTests_PackageGraph_Base::ClassSetup();
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            return PackageTests_PackageGraph_Base::ClassCleanup();
        }

        TEST_METHOD(GetFilePath_InvalidParameter)
        {
            try
            {
                winrt::hstring noFileName;
                std::ignore = winrt::Microsoft::Windows::ApplicationModel::PackageGraph::GetFilePath(noFileName);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                winrt::hstring noFileName;
                const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::None };
                std::ignore = winrt::Microsoft::Windows::ApplicationModel::PackageGraph::GetFilePath(noFileName, options);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(GetFilePath)
        {
            winrt::hstring packageFullName{ Framework_PackageFullName };
            winrt::hstring packageFamilyName{ Framework_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            winrt::hstring fileName{ L"AppxManifest.xml" };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::PackageGraph::GetFilePath(fileName) };

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.c_str()));
            VERIFY_IS_FALSE(absoluteFilename.empty());
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName.c_str(), fileName.c_str(), PackagePathType_Effective) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.c_str()});
        }

        TEST_METHOD(GetFilePath_InstallPath)
        {
            winrt::hstring packageFullName{ Framework_PackageFullName };
            winrt::hstring packageFamilyName{ Framework_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            winrt::hstring fileName{ L"AppxManifest.xml" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchInstallPath };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::PackageGraph::GetFilePath(fileName, options) };

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.c_str()));
            VERIFY_IS_FALSE(absoluteFilename.empty());
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName.c_str(), fileName.c_str(), PackagePathType_Install) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.c_str()});
        }

        TEST_METHOD(GetFilePath_MutablePath)
        {
            winrt::hstring packageFullName{ Mutable_PackageFullName };
            winrt::hstring packageFamilyName{ Mutable_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            winrt::hstring fileName{ L"AppxManifest.xml" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchMutablePath };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::PackageGraph::GetFilePath(fileName, options) };

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.c_str()));
            VERIFY_IS_FALSE(absoluteFilename.empty());
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName.c_str(), fileName.c_str(), PackagePathType_Mutable) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.c_str()});
        }

        TEST_METHOD(GetFilePath_MachineExternalPath)
        {
            winrt::hstring packageFullName{ MachineExternal_PackageFullName };
            winrt::hstring packageFamilyName{ MachineExternal_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            winrt::hstring fileName{ L"Shadow.cat" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchMachineExternalPath };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::PackageGraph::GetFilePath(fileName, options) };

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.c_str()));
            VERIFY_IS_FALSE(absoluteFilename.empty());
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName.c_str(), fileName.c_str(), PackagePathType_MachineExternal) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.c_str()});
        }

        TEST_METHOD(GetFilePath_UserExternalPath)
        {
            winrt::hstring packageFullName{ UserExternal_PackageFullName };
            winrt::hstring packageFamilyName{ UserExternal_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            winrt::hstring fileName{ L"Shadow.cat" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchUserExternalPath };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::PackageGraph::GetFilePath(fileName, options) };

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.c_str()));
            VERIFY_IS_FALSE(absoluteFilename.empty());
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName.c_str(), fileName.c_str(), PackagePathType_UserExternal) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.c_str()});
        }

        TEST_METHOD(GetFilePath_FilterPackageType_Main_NoMatch)
        {
            winrt::hstring packageFamilyName{ Main_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            winrt::hstring fileName{ L"Shadow.cat" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchInstallPath |
                                winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchFrameworkPackages };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::PackageGraph::GetFilePath(fileName, options) };
            VERIFY_IS_TRUE(absoluteFilename.empty(), WEX::Common::String().Format(L"AbsoluteFilename:%ls", absoluteFilename.c_str()));
        }

        TEST_METHOD(GetFilePath_FilterPackageType_Framework_NoMatch)
        {
            winrt::hstring packageFamilyName{ Framework_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            winrt::hstring fileName{ L"Shadow.cat" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchInstallPath |
                                winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchMainPackages };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::PackageGraph::GetFilePath(fileName, options) };
            VERIFY_IS_TRUE(absoluteFilename.empty(), WEX::Common::String().Format(L"AbsoluteFilename:%ls", absoluteFilename.c_str()));
        }
    };
}
