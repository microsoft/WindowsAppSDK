// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <package_runtime.h>

#include <IsWindowsVersion.h>

#include "PackageTests_PackageGraph_Base.h"

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TD = ::Test::Diagnostics;

namespace Test::Package::Tests
{
    class PackageTests_PackageGraph_Packaged_CPP : PackageTests_PackageGraph_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageTests_PackageGraph_Packaged_CPP)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:AppXManifest", L"PackagedCwaFullTrust")
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

        TEST_METHOD(GetFilePath)
        {
            PCWSTR packageFullName{ Framework_PackageFullName };
            PCWSTR packageFamilyName{ Framework_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_None };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePathInPackageGraph(fileName, options, wil::out_param(absoluteFilename)));

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.get()));
            VERIFY_IS_NOT_NULL(absoluteFilename);
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName, fileName, PackagePathType_Effective) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.get()});
        }

        TEST_METHOD(GetFilePath_InstallPath)
        {
            PCWSTR packageFullName{ Framework_PackageFullName };
            PCWSTR packageFamilyName{ Framework_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchInstallPath };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePathInPackageGraph(fileName, options, wil::out_param(absoluteFilename)));

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.get()));
            VERIFY_IS_NOT_NULL(absoluteFilename);
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName, fileName, PackagePathType_Install) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.get()});
        }

        TEST_METHOD(GetFilePath_MutablePath)
        {
            PCWSTR packageFullName{ Mutable_PackageFullName };
            PCWSTR packageFamilyName{ Mutable_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchMutablePath };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePathInPackageGraph(fileName, options, wil::out_param(absoluteFilename)));

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.get()));
            VERIFY_IS_NOT_NULL(absoluteFilename);
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName, fileName, PackagePathType_Mutable) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.get()});
        }

        TEST_METHOD(GetFilePath_MachineExternalPath)
        {
            PCWSTR packageFullName{ MachineExternal_PackageFullName };
            PCWSTR packageFamilyName{ MachineExternal_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            PCWSTR fileName{ L"Shadow.cat" };
            const auto options{ GetPackageFilePathOptions_SearchMachineExternalPath };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePathInPackageGraph(fileName, options, wil::out_param(absoluteFilename)));

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.get()));
            VERIFY_IS_NOT_NULL(absoluteFilename);
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName, fileName, PackagePathType_MachineExternal) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.get()});
        }

        TEST_METHOD(GetFilePath_UserExternalPath)
        {
            PCWSTR packageFullName{ UserExternal_PackageFullName };
            PCWSTR packageFamilyName{ UserExternal_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            PCWSTR fileName{ L"Shadow.cat" };
            const auto options{ GetPackageFilePathOptions_SearchUserExternalPath };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePathInPackageGraph(fileName, options, wil::out_param(absoluteFilename)));

            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Found: %ls", absoluteFilename.get()));
            VERIFY_IS_NOT_NULL(absoluteFilename);
            const std::filesystem::path expected{ ::AppModel::Package::GetAbsoluteFilename(packageFullName, fileName, PackagePathType_UserExternal) };
            VERIFY_ARE_EQUAL(expected, std::filesystem::path{absoluteFilename.get()});
        }

        TEST_METHOD(GetFilePath_FilterPackageType_Main_NoMatch)
        {
            const auto packageFullName{ ::AppModel::Identity::GetCurrentPackageFullName<std::wstring>() };
            const auto packageFamilyName{ ::AppModel::Identity::GetCurrentPackageFamilyName<std::wstring>() };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchInstallPath |
                                GetPackageFilePathOptions_SearchFrameworkPackages };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePathInPackageGraph(fileName, options, wil::out_param(absoluteFilename)));
            VERIFY_IS_NULL(absoluteFilename);
        }

        TEST_METHOD(GetFilePath_FilterPackageType_Framework_NoMatch)
        {
            PCWSTR packageFamilyName{ Framework_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchInstallPath |
                                GetPackageFilePathOptions_SearchMainPackages };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePathInPackageGraph(fileName, options, wil::out_param(absoluteFilename)));
            VERIFY_IS_NULL(absoluteFilename);
        }

        TEST_METHOD(GetFilePath_Filter_Static_NoMatch)
        {
            PCWSTR packageFamilyName{ Framework_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchInstallPath |
                                GetPackageFilePathOptions_SearchFrameworkPackages |
                                GetPackageFilePathOptions_SearchStaticDependencies };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePathInPackageGraph(fileName, options, wil::out_param(absoluteFilename)));
            VERIFY_IS_NULL(absoluteFilename);
        }

        TEST_METHOD(GetFilePath_Filter_Dynamic_NoMatch)
        {
            PCWSTR packageFamilyName{ Framework_PackageFamilyName };
            wil::unique_package_dependency_context packageDependencyContext{ AddDynamicDependency(packageFamilyName) };

            PCWSTR fileName{ L"AppxManifest.xml" };
            const auto options{ GetPackageFilePathOptions_SearchInstallPath |
                                GetPackageFilePathOptions_SearchFrameworkPackages |
                                GetPackageFilePathOptions_SearchDynamicDependencies };
            wil::unique_process_heap_ptr<WCHAR> absoluteFilename;
            VERIFY_SUCCEEDED(::GetPackageFilePathInPackageGraph(fileName, options, wil::out_param(absoluteFilename)));
            VERIFY_IS_NULL(absoluteFilename);
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
