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
    const auto Framework_PackageFullName{ ::TP::WindowsAppRuntimeFramework::c_PackageFullName };

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
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(FindPackageFile_InvalidParameter)
        {
            try
            {
                winrt::hstring packageFullName{ Framework_PackageFullName };
                winrt::hstring noFileName;
                std::ignore = winrt::Microsoft::Windows::ApplicationModel::Package::FindPackageFile(packageFullName, noFileName);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(FindPackageFile_NullPackageFullName_UnpackagedProcess)
        {
            try
            {
                winrt::hstring noPackageFullName;
                winrt::hstring fileName{ L"AppxManifest.xml" };
                std::ignore = winrt::Microsoft::Windows::ApplicationModel::Package::FindPackageFile(noPackageFullName, fileName);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(FindPackageFile_NullPackageFullName_PackagedProcess)
        {
            //TODO
        }

        TEST_METHOD(FindPackageFile_InstallPath)
        {
            winrt::hstring packageFullName{ Framework_PackageFullName };
            winrt::hstring fileName{ L"AppxManifest.xml" };
            const auto absoluteFilename{ winrt::Microsoft::Windows::ApplicationModel::Package::FindPackageFile(packageFullName, fileName) };
            //TODO
        }
    };
}
