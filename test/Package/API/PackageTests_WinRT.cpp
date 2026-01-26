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

    class PackageTests_WinRT
    {
    public:
        BEGIN_TEST_CLASS(PackageTests_WinRT)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            ::TB::Setup();

            //RemovePackage_MachineExternal();
            RemovePackage_UserExternal();
            RemovePackage_Mutable();

            AddPackage_Mutable();
            AddPackage_UserExternal();
            //AddPackage_MachineExternal();

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
            //TODO
        }

        TEST_METHOD(GetFilePath_InstallPath)
        {
            winrt::hstring packageFullName{ Framework_PackageFullName };
            winrt::hstring fileName{ L"AppxManifest.xml" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchInstallPath };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(fileName, packageFullName, options) };
            //TODO
        }

        TEST_METHOD(GetFilePath_MutablePath)
        {
            //TODO
        }

        TEST_METHOD(GetFilePath_MachineExternalPath)
        {
            //TODO
        }

        TEST_METHOD(GetFilePath_UserExternalPath)
        {
            //TODO
        }

        TEST_METHOD(GetFilePath_FilterPackageType_Main_NoMatch)
        {
            winrt::hstring packageFullName{ Main_PackageFullName };
            winrt::hstring fileName{ L"AppxManifest.xml" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchInstallPath |
                                winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchFrameworkPackages };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(fileName, packageFullName, options) };
            VERIFY_IS_TRUE(absoluteFilename.empty());
        }

        TEST_METHOD(GetFilePath_FilterPackageType_Framework_NoMatch)
        {
            winrt::hstring packageFullName{ Framework_PackageFullName };
            winrt::hstring fileName{ L"AppxManifest.xml" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchInstallPath |
                                winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchMainPackages };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(fileName, packageFullName, options) };
            VERIFY_IS_TRUE(absoluteFilename.empty());
        }

        TEST_METHOD(GetFilePath_Filter_Static_NoMatch)
        {
            //TODO
        }

        TEST_METHOD(GetFilePath_Filter_Dynamic_NoMatch)
        {
            winrt::hstring packageFullName{ Framework_PackageFullName };
            winrt::hstring fileName{ L"AppxManifest.xml" };
            const auto options{ winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchInstallPath |
                                winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchFrameworkPackages |
                                winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions::SearchDynamicDependencies };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::Package::GetFilePath(fileName, packageFullName, options) };
            VERIFY_IS_TRUE(absoluteFilename.empty());
        }

        TEST_METHOD(GetFilePath_Filter_Static)
        {
            //TODO
        }

        TEST_METHOD(GetFilePath_Filter_Dynamic)
        {
            //TODO
        }
    };
}
