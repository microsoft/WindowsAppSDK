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

namespace Test::DynamicDependency
{
    TEST_CLASS(BootstrapTests)
    {
    public:

        TEST_CLASS_INITIALIZE(Setup)
        {
            // CppUnitTest initializes COM as STA before we get called
            // But we don't need (or want) STA, and we do want MTA. We can't
            // stop CppUnitTest from initializing COM but we can uninitialize
            // it and (re)initialize it as MTA. Don't think of it as crude
            // and brutish but rather 'thinking outside the box'...
            winrt::uninit_apartment();
            winrt::init_apartment();

            // We need to find Microsoft.ProjectReunion.Bootstrap.dll.
            // Normally it's colocated with the application (i.e. same dir as the exe)
            // but that's not true of our test project (a dll) in our build environment
            // (different directories). So we'll explicitly find and load it so the
            // rest of our test is fine
            auto bootstrapDllAbsoluteFilename{ GetBootstrapAbsoluteFilename() };
            wil::unique_hmodule bootstrapDll(LoadLibrary(bootstrapDllAbsoluteFilename.c_str()));
            const auto lastError{ GetLastError() };
            Assert::IsNotNull(bootstrapDll.get());

            AddPackage_MainSidecar();

            m_bootstrapDll = std::move(bootstrapDll);
        }

        TEST_CLASS_CLEANUP(Cleanup)
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
            // coclass MyLifetimeManager == CLSID {32E7CF70-038C-429a-BD49-88850F1B4A11}
            // See winmain.cpp in Main.Sidecar.LifetimeManager project for more details
            constexpr GUID clsid
            {
                0x32e7cf70, 0x038c, 0x429a, { 0xbd, 0x49, 0x88, 0x85, 0x0f, 0x1b, 0x4a, 0x11 }
            };
            Assert::AreEqual(S_OK, MddBootstrapInitialize(clsid));
        }

        TEST_METHOD(ShutdownWithoutInitialize)
        {
            MddBootstrapShutdown();
            MddBootstrapShutdown();
        }

    private:
        static void AddPackageIfNecessary(PCWSTR packageDirName, PCWSTR packageFullName)
        {
            if (IsPackageRegistered(packageFullName))
            {
                return;
            }

            // Build the target package's .msix filename. It's under the Solution's $(OutDir)
            auto msix = GetSolutionOutDirPath();
            msix /= packageDirName;
            msix += L".msix";
            msix /= packageDirName;
            msix += L".msix";
            auto msixUri = winrt::Windows::Foundation::Uri(msix.c_str());

            winrt::Windows::Management::Deployment::PackageManager packageManager;
            auto options{ winrt::Windows::Management::Deployment::DeploymentOptions::None };
            auto deploymentResult{ packageManager.AddPackageAsync(msixUri, nullptr, options).get() };
            if (deploymentResult)
            {
                auto message = wil::str_printf<wil::unique_process_heap_string>(L"AddPackageAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str());
                Assert::Fail(message.get());
            }
        }

        static void RemovePackageIfNecessary(PCWSTR packageFullName)
        {
            if (IsPackageRegistered(packageFullName))
            {
                return;
            }

            winrt::Windows::Management::Deployment::PackageManager packageManager;
            auto deploymentResult{ packageManager.RemovePackageAsync(packageFullName).get() };
            if (!deploymentResult)
            {
                auto message = wil::str_printf<wil::unique_process_heap_string>(L"RemovePackageAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str());
                Assert::Fail(message.get());
            }
        }

        static bool IsPackageRegistered(PCWSTR packageFullName)
        {
            const auto path = GetPackagePath(packageFullName);
            return !path.empty();
        }

        static std::wstring GetPackagePath(PCWSTR packageFullName)
        {
            UINT32 pathLength{};
            const auto rc{ GetPackagePathByFullName(packageFullName, &pathLength, nullptr) };
            if (rc == ERROR_NOT_FOUND)
            {
                return std::wstring();
            }

            Assert::AreEqual(ERROR_INSUFFICIENT_BUFFER, rc);
            auto path = wil::make_process_heap_string(nullptr, pathLength);
            Assert::AreEqual(ERROR_SUCCESS, GetPackagePathByFullName(packageFullName, &pathLength, path.get()));
            return std::wstring(path.get());
        }

        static std::filesystem::path GetModulePath(HMODULE hmodule = nullptr)
        {
            auto path = GetModuleFileName(hmodule);
            return path.remove_filename();
        }

        static std::filesystem::path GetModuleFileName(HMODULE hmodule = nullptr)
        {
            auto moduleFileName = wil::GetModuleFileNameW(hmodule);
            return std::filesystem::path(moduleFileName.get());
        }

        static void AddPackage_MainSidecar()
        {
            AddPackageIfNecessary(Test::Packages::MainSidecar::c_PackageDirName, Test::Packages::MainSidecar::c_PackageFullName);
        }

        static void RemovePackage_MainSidecar()
        {
            RemovePackageIfNecessary(Test::Packages::MainSidecar::c_PackageFullName);
        }

        static std::filesystem::path GetTestAbsoluteFilename()
        {
            wil::unique_hmodule dll(LoadLibrary(L"DynamicDependency_Test_Win32.dll"));
            const auto lastError{ GetLastError() };
            Assert::IsNotNull(dll.get());
            return GetModulePath(dll.get());
        }

        static std::filesystem::path GetTestAbsolutePath()
        {
            auto path = GetTestAbsoluteFilename();
            path = path.remove_filename();
            path = path.parent_path();
            return path;
        }

        static std::filesystem::path GetSolutionOutDirPath()
        {
            // We can't lookup the location of project outputs in our solution
            // but we can infer them relative to our test dll's location
            // as we all share a common $(OutDir), as Visual Studio calls it
            //
            // \...
            //    \DynamicDependency_Test_Win32
            //        DynamicDependency_Test_Win32.dll      <== This test .dll
            //    \Main.SideCar.Msix
            //        Main.Sidecar.Msix
            //    \ProjectReunion_BootstrapDLL
            //        Microsoft.ProjectReunion.Bootstrap.dll

            // Find the test dll's directory
            auto testPath = GetTestAbsoluteFilename();

            // Find the common parent directory
            auto path = testPath.parent_path().parent_path();
            return path;
        }

        static std::filesystem::path GetBootstrapAbsoluteFilename()
        {
            // Determine the location of the bootstrap dll. See GetSolutionOutDirPath() for more details.
            auto path = GetSolutionOutDirPath();
            path /= L"ProjectReunion_BootstrapDLL";
            path /= L"Microsoft.ProjectReunion.Bootstrap.dll";
            return path;
        }

        static std::filesystem::path GetMainSidecarMsixPath()
        {
            // Determine the location of the Main.Sidecar's msix. See GetSolutionOutDirPath() for more details.
            auto path = GetSolutionOutDirPath();
            path /= L"Main.Sidecar.Msix";
            path /= L"Main.Sidecar.msix";
            return path;
        }

    private:
        static wil::unique_hmodule m_bootstrapDll;
    };
}

wil::unique_hmodule Test::DynamicDependency::BootstrapTests::m_bootstrapDll;
