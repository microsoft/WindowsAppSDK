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
    const auto Mutable_PackageFullName{ ::TP::Mutable::c_packageFullName };
    const auto UserExternal_PackageFullName{ ::TP::UserExternal::c_packageFullName };
    const auto MachineExternal_PackageFullName{ ::TP::MachineExternal::c_packageFullName };

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

        std::filesystem::path ToAbsoluteFilename(
            PCWSTR packageFullName,
            PCWSTR filename,
            PackagePathType packageType)
        {
            const auto path{ ::AppModel::Package::GetPath<std::wstring>(packageFullName, packageType) };
            std::filesystem::path absoluteFilename{ path };
            absoluteFilename /= filename;
            return absoluteFilename;
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

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.get()));
            VERIFY_IS_NOT_NULL(absoluteFilename);
            const std::filesystem::path expected{ ToAbsoluteFilename(packageFullName, fileName, PackagePathType_Effective) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.get()});
        }

        TEST_METHOD(GetPackageFilePath_InstallPath)
        {
            PCWSTR packageFullName{ Framework_PackageFullName };
            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchInstallPath };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePath(packageFullName, fileName, options, wil::out_param(absoluteFilename)));

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.get()));
            VERIFY_IS_NOT_NULL(absoluteFilename);
            const std::filesystem::path expected{ ToAbsoluteFilename(packageFullName, fileName, PackagePathType_Install) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.get()});
        }

        TEST_METHOD(GetPackageFilePath_MutablePath)
        {
            PCWSTR packageFullName{ Mutable_PackageFullName };
            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchMutablePath };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePath(packageFullName, fileName, options, wil::out_param(absoluteFilename)));

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.get()));
            VERIFY_IS_NOT_NULL(absoluteFilename);
            const std::filesystem::path expected{ ToAbsoluteFilename(packageFullName, fileName, PackagePathType_Mutable) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.get()});
        }

        TEST_METHOD(GetPackageFilePath_MachineExternalPath)
        {
            PCWSTR packageFullName{ MachineExternal_PackageFullName };
            PCWSTR fileName{ L"msix\\AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchMachineExternalPath };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePath(packageFullName, fileName, options, wil::out_param(absoluteFilename)));

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.get()));
            VERIFY_IS_NOT_NULL(absoluteFilename);
            const std::filesystem::path expected{ ToAbsoluteFilename(packageFullName, fileName, PackagePathType_MachineExternal) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.get()});
        }

        TEST_METHOD(GetPackageFilePath_UserExternalPath)
        {
            PCWSTR packageFullName{ UserExternal_PackageFullName };
            PCWSTR fileName{ L"msix\\AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchUserExternalPath };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePath(packageFullName, fileName, options, wil::out_param(absoluteFilename)));

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.get()));
            VERIFY_IS_NOT_NULL(absoluteFilename);
            const std::filesystem::path expected{ ToAbsoluteFilename(packageFullName, fileName, PackagePathType_UserExternal) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.get()});
        }

        TEST_METHOD(GetPackageFilePath_FilterPackageType_Main_NoMatch)
        {
            PCWSTR packageFullName{ Main_PackageFullName };
            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchInstallPath |
                                GetPackageFilePathOptions_SearchFrameworkPackages };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePath(packageFullName, fileName, options, wil::out_param(absoluteFilename)));
            VERIFY_IS_NULL(absoluteFilename);
        }

        TEST_METHOD(GetPackageFilePath_FilterPackageType_Framework_NoMatch)
        {
            PCWSTR packageFullName{ Framework_PackageFullName };
            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchInstallPath |
                                GetPackageFilePathOptions_SearchMainPackages };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePath(packageFullName, fileName, options, wil::out_param(absoluteFilename)));
            VERIFY_IS_NULL(absoluteFilename);
        }

#if 0
        TEST_METHOD(GetPackageFilePath_Filter_Static_NoMatch)
        {
            PCWSTR packageFullName{ Framework_PackageFullName };
            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchInstallPath |
                                GetPackageFilePathOptions_SearchFrameworkPackages |
                                GetPackageFilePathOptions_SearchStaticDependencies };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePath(packageFullName, fileName, options, wil::out_param(absoluteFilename)));
            VERIFY_IS_NULL(absoluteFilename);
        }

        TEST_METHOD(GetPackageFilePath_Filter_Dynamic_NoMatch)
        {
            PCWSTR packageFullName{ Framework_PackageFullName };
            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchInstallPath |
                                GetPackageFilePathOptions_SearchFrameworkPackages |
                                GetPackageFilePathOptions_SearchDynamicDependencies };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePath(packageFullName, fileName, options, wil::out_param(absoluteFilename)));
            VERIFY_IS_NULL(absoluteFilename);
        }

        TEST_METHOD(GetPackageFilePath_Filter_Static)
        {
            //TODO
        }

        TEST_METHOD(GetPackageFilePath_Filter_Dynamic)
        {
            //TODO
        }
#endif
    };
}
