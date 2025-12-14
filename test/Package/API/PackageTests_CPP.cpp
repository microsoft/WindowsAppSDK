// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <package_runtime.h>

#include <IsWindowsVersion.h>

#include "PackageTests.Packages.h"

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TD = ::Test::Diagnostics;

namespace Test::Package::Tests
{
    const auto Main_PackageFullName{ ::TP::WindowsAppRuntimeMain::c_PackageFullName };
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

            //RemovePackage_MachineExternal();
            //RemovePackage_UserExternal();
            //RemovePackage_Mutable();

            //AddPackage_Mutable();
            //AddPackage_UserExternal();
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

        TEST_METHOD(GetPackageFilePath_InvalidParameter)
        {
            PCWSTR packageFullName{ Framework_PackageFullName };
            PCWSTR noFileName{};
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            const auto options{ GetPackageFilePathOptions_None };
            VERIFY_ARE_EQUAL(E_INVALIDARG, ::GetPackageFilePath(packageFullName, noFileName, options, wil::out_param(absoluteFilename)));
        }

        TEST_METHOD(GetPackageFilePath_NullPackageFullName_UnpackagedProcess_NoPackage)
        {
            PCWSTR noPackageFullName{};
            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_None };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), ::GetPackageFilePath(noPackageFullName, fileName, options, wil::out_param(absoluteFilename)));
        }

        TEST_METHOD(GetPackageFilePath_NullPackageFullName_PackagedProcess_InstallPath)
        {
            //TODO
        }

        TEST_METHOD(GetPackageFilePath)
        {
            PCWSTR packageFullName{ Framework_PackageFullName };
            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_None };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePath(packageFullName, fileName, options, wil::out_param(absoluteFilename)));
            //TODO
        }

        TEST_METHOD(GetPackageFilePath_InstallPath)
        {
            PCWSTR packageFullName{ Framework_PackageFullName };
            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchInstallPath };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePath(packageFullName, fileName, options, wil::out_param(absoluteFilename)));
            //TODO
        }

        TEST_METHOD(GetPackageFilePath_MutablePath)
        {
            //TODO
        }

        TEST_METHOD(GetPackageFilePath_MachineExternalPath)
        {
            //TODO
        }

        TEST_METHOD(GetPackageFilePath_UserExternalPath)
        {
            //TODO
        }

        TEST_METHOD(GetPackageFilePath_FilterPackageType_Main_NoMatch)
        {
            //TODO
        }

        TEST_METHOD(GetPackageFilePath_FilterPackageType_Framework_NoMatch)
        {
            //TODO
        }

        TEST_METHOD(GetPackageFilePath_Filter_Static_NoMatch)
        {
            //TODO
        }

        TEST_METHOD(GetPackageFilePath_Filter_Dynamic_NoMatch)
        {
            //TODO
        }

        TEST_METHOD(GetPackageFilePath_Filter_Static)
        {
            //TODO
        }

        TEST_METHOD(GetPackageFilePath_Filter_Dynamic)
        {
            //TODO
        }
    };
}
