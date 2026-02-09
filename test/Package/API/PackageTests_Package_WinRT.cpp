// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TD = ::Test::Diagnostics;

static const winrt::hstring null_hstring;

namespace Test::Package::Tests
{
    const auto Main_PackageFullName{ ::TP::WindowsAppRuntimeMain::c_PackageFullName };
    const auto Framework_PackageFullName{ ::TP::WindowsAppRuntimeFramework::c_PackageFullName };
    const auto Mutable_PackageFullName{ ::TP::Mutable::c_packageFullName };
    const auto UserExternal_PackageFullName{ ::TP::UserExternal::c_packageFullName };
    const auto MachineExternal_PackageFullName{ ::TP::MachineExternal::c_packageFullName };

    class PackageTests_Package_WinRT
    {
    public:
        BEGIN_TEST_CLASS(PackageTests_Package_WinRT)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            ::TB::Setup();

            RemovePackage_MachineExternal();
            RemovePackage_UserExternal();
            RemovePackage_Mutable();

            AddPackage_Mutable();
            AddPackage_UserExternal();
            StagePackage_MachineExternal();
            AddPackage_MachineExternal();

            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::TB::Cleanup();

            RemovePackage_MachineExternal();
            RemovePackage_UserExternal();
            RemovePackage_Mutable();

            return true;
        }

        TEST_METHOD(GetFilePath_InvalidParameter)
        {
            try
            {
                winrt::hstring packageFullName{ Framework_PackageFullName };
                winrt::hstring noFileName;
                std::ignore = winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(noFileName, packageFullName);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                winrt::hstring packageFullName{ Framework_PackageFullName };
                winrt::hstring noFileName;
                const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::None };
                std::ignore = winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(noFileName, packageFullName, options);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(GetFilePath_NullPackageFullName_UnpackagedProcess_NoPackage)
        {
            try
            {
                winrt::hstring noPackageFullName;
                winrt::hstring fileName{ L"AppxManifest.xml" };
                std::ignore = winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(fileName, noPackageFullName);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                winrt::hstring noPackageFullName;
                winrt::hstring fileName{ L"AppxManifest.xml" };
                const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::None };
                std::ignore = winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(fileName, noPackageFullName, options);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(GetFilePath_NullPackageFullName_PackagedProcess_InstallPath)
        {
            //TODO
        }

        TEST_METHOD(GetFilePath)
        {
            winrt::hstring packageFullName{ Framework_PackageFullName };
            winrt::hstring fileName{ L"AppxManifest.xml" };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(fileName, packageFullName) };

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.c_str()));
            VERIFY_IS_FALSE(absoluteFilename.empty());
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName.c_str(), fileName.c_str(), PackagePathType_Effective) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.c_str()});
        }

        TEST_METHOD(GetFilePath_InstallPath)
        {
            winrt::hstring packageFullName{ Framework_PackageFullName };
            winrt::hstring fileName{ L"AppxManifest.xml" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchInstallPath };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(fileName, packageFullName, options) };

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.c_str()));
            VERIFY_IS_FALSE(absoluteFilename.empty());
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName.c_str(), fileName.c_str(), PackagePathType_Install) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.c_str()});
        }

        TEST_METHOD(GetFilePath_MutablePath)
        {
            winrt::hstring packageFullName{ Mutable_PackageFullName };
            winrt::hstring fileName{ L"AppxManifest.xml" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchMutablePath };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(fileName, packageFullName, options) };

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.c_str()));
            VERIFY_IS_FALSE(absoluteFilename.empty());
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName.c_str(), fileName.c_str(), PackagePathType_Mutable) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.c_str()});
        }

        TEST_METHOD(GetFilePath_MachineExternalPath)
        {
            winrt::hstring packageFullName{ MachineExternal_PackageFullName };
            winrt::hstring fileName{ L"Shadow.cat" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchMachineExternalPath };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(fileName, packageFullName, options) };

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.c_str()));
            VERIFY_IS_FALSE(absoluteFilename.empty());
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName.c_str(), fileName.c_str(), PackagePathType_MachineExternal) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.c_str()});
        }

        TEST_METHOD(GetFilePath_UserExternalPath)
        {
            winrt::hstring packageFullName{ UserExternal_PackageFullName };
            winrt::hstring fileName{ L"Shadow.cat" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchUserExternalPath };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(fileName, packageFullName, options) };

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.c_str()));
            VERIFY_IS_FALSE(absoluteFilename.empty());
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName.c_str(), fileName.c_str(), PackagePathType_UserExternal) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.c_str()});
        }

        TEST_METHOD(GetFilePath_FilterPackageType_Main_NoMatch)
        {
            winrt::hstring packageFullName{ Main_PackageFullName };
            winrt::hstring fileName{ L"Shadow.cat" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchInstallPath |
                                winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchFrameworkPackages };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(fileName, packageFullName, options) };
            VERIFY_IS_TRUE(absoluteFilename.empty(), WEX::Common::String().Format(L"AbsoluteFilename:%ls", absoluteFilename.c_str()));
        }

        TEST_METHOD(GetFilePath_FilterPackageType_Framework_NoMatch)
        {
            winrt::hstring packageFullName{ Framework_PackageFullName };
            winrt::hstring fileName{ L"Shadow.cat" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchInstallPath |
                                winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchMainPackages };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(fileName, packageFullName, options) };
            VERIFY_IS_TRUE(absoluteFilename.empty(), WEX::Common::String().Format(L"AbsoluteFilename:%ls", absoluteFilename.c_str()));
        }
    };
}
