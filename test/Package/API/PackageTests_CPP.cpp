// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <package_runtime.h>

#include <IsWindowsVersion.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TD = ::Test::Diagnostics;

namespace Test::Package::Tests
{
    const auto Framework_PackageFullName{ ::TP::WindowsAppRuntimeFramework::c_PackageFullName };

    class PackageTests_CPP
    {
    public:
        BEGIN_TEST_CLASS(PackageTests_CPP)
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
            PCWSTR packageFullName{ Framework_PackageFullName };
            PCWSTR noFileName{};
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_ARE_EQUAL(E_INVALIDARG, ::FindPackageFile(packageFullName, noFileName, wil::out_param(absoluteFilename));
        }

        TEST_METHOD(FindPackageFile_NullPackageFullName_UnpackagedProcess)
        {
            PCWSTR noPackageFullName{};
            PCWSTR fileName{ L"AppxManifest.xml" };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), ::FindPackageFile(noPackageFullName, fileName, wil::out_param(absoluteFilename)));
        }

        TEST_METHOD(FindPackageFile_NullPackageFullName_PackagedProcess)
        {
            //TODO
        }

        TEST_METHOD(FindPackageFile_InstallPath)
        {
            PCWSTR packageFullName{ Framework_PackageFullName };
            PCWSTR fileName{ L"AppxManifest.xml" };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::FindPackageFile(noPackageFullName, fileName, wil::out_param(absoluteFilename)));
            //TODO
        }
    };
}
