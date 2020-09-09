// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MddBootstrap.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test::Packages::MainSidecar
{
    PCWSTR c_PackageDirName = L"Main.Sidecar";
    PCWSTR c_PackageFullName = L"ProjectReunion.Test.DynDep.Main.Sidecar_4.1.1967.333_neutral__8wekyb3d8bbwe";
}

namespace Test
{
    namespace DynamicDependency
    {
        TEST_CLASS(BootstrapTests)
        {
        public:

            TEST_METHOD_INITIALIZE(Setup)
            {
                AddPackage_MainSidecar();
            }

            TEST_METHOD_CLEANUP(Cleanup)
            {
                RemovePackage_MainSidecar();
            }

            TEST_METHOD(Initialize_ClassNotFound)
            {
                const GUID doesNotExist{};
                Assert::AreEqual(REGDB_E_CLASSNOTREG, MddBootstrapInitialize(doesNotExist));
            }

            TEST_METHOD(Initialize)
            {
                const GUID clsid = {};//TODO
                Assert::AreEqual(S_OK, MddBootstrapInitialize(clsid));
            }

            TEST_METHOD(ShutdownWithoutInitialize)
            {
                MddBootstrapShutdown();
                MddBootstrapShutdown();
            }

        private:
            void AddPackageIfNecessary(PCWSTR packageDirName, PCWSTR packageFullName)
            {
                if (IsPackageRegistered(packageFullName))
                {
                    return;
                }

                // Target MSIX is located in a peer directory to the current process' executable
                auto msix = GetModulePath();
                msix.remove_filename();
                msix /= packageDirName;
                msix /= packageDirName;
                msix += L".msix";
                auto msixUri = winrt::Windows::Foundation::Uri(msix.c_str());

                winrt::Windows::Management::Deployment::PackageManager packageManager;
                auto options = winrt::Windows::Management::Deployment::DeploymentOptions::None;
                auto deploymentResult = packageManager.AddPackageAsync(msixUri, nullptr, options).get();
                if (!deploymentResult)
                {
                    auto message = wil::str_printf<wil::unique_process_heap_string>(L"AddPackageAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str());
                    Assert::Fail(message.get());
                }
            }

            void RemovePackageIfNecessary(PCWSTR packageFullName)
            {
                if (IsPackageRegistered(packageFullName))
                {
                    return;
                }

                winrt::Windows::Management::Deployment::PackageManager packageManager;
                auto deploymentResult = packageManager.RemovePackageAsync(packageFullName).get();
                if (!deploymentResult)
                {
                    auto message = wil::str_printf<wil::unique_process_heap_string>(L"RemovePackageAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str());
                    Assert::Fail(message.get());
                }
            }

            bool IsPackageRegistered(PCWSTR packageFullName)
            {
                const auto path = GetPackagePath(packageFullName);
                return !path.empty();
            }

            std::wstring GetPackagePath(PCWSTR packageFullName)
            {
                UINT32 pathLength{};
                const auto rc = GetPackagePathByFullName(packageFullName, &pathLength, nullptr);
                if (rc == ERROR_NOT_FOUND)
                {
                    return std::wstring();
                }

                Assert::AreEqual(ERROR_INSUFFICIENT_BUFFER, rc);
                auto path = wil::make_process_heap_string(nullptr, pathLength);
                Assert::AreEqual(ERROR_SUCCESS, GetPackagePathByFullName(packageFullName, &pathLength, path.get()));
                return std::wstring(path.get());
            }

            std::filesystem::path GetModulePath(HMODULE hmodule = nullptr)
            {
                auto path = GetModuleFileName(hmodule);
                return path.remove_filename();
            }

            std::filesystem::path GetModuleFileName(HMODULE hmodule = nullptr)
            {
                auto moduleFileName = wil::GetModuleFileNameW(hmodule);
                return std::filesystem::path(moduleFileName.get());
            }

            void AddPackage_MainSidecar()
            {
                AddPackageIfNecessary(Test::Packages::MainSidecar::c_PackageDirName, Test::Packages::MainSidecar::c_PackageFullName);
            }

            void RemovePackage_MainSidecar()
            {
                RemovePackageIfNecessary(Test::Packages::MainSidecar::c_PackageFullName);
            }
        };
    }
}
