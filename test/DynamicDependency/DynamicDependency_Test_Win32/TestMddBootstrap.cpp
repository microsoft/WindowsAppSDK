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

namespace Test::Packages::ProjectReunionFramework
{
    PCWSTR c_PackageDirName = L"Microsoft.ProjectReunion.Framework";
    PCWSTR c_PackageFullName = L"Microsoft.ProjectReunion.Framework_0.1.2.3_neutral__8wekyb3d8bbwe";
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
            CoSuperInitialize();

            // We need to find Microsoft.ProjectReunion.Bootstrap.dll.
            // Normally it's colocated with the application (i.e. same dir as the exe)
            // but that's not true of our test project (a dll) in our build environment
            // (different directories). So we'll explicitly find and load it so the
            // rest of our test is fine
            auto bootstrapDllAbsoluteFilename{ GetBootstrapAbsoluteFilename() };
            wil::unique_hmodule bootstrapDll(LoadLibrary(bootstrapDllAbsoluteFilename.c_str()));
            const auto lastError{ GetLastError() };
            Assert::IsNotNull(bootstrapDll.get());

            AddPackage_ProjectReunionFramework();
            AddPackage_MainSidecar();

            m_bootstrapDll = std::move(bootstrapDll);
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            RemovePackage_MainSidecar();
            RemovePackage_ProjectReunionFramework();
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
        static void CoSuperInitialize(winrt::apartment_type const type = winrt::apartment_type::multi_threaded)
        {
            // CoUninitialize() needs to be called as many times as CoInitialize()
            // Keep 'peeling the onion' until we're the 1st to initialize COM
            for (;;)
            {
                const HRESULT hr = WINRT_IMPL_CoInitializeEx(nullptr, static_cast<uint32_t>(type));
                if (hr == S_OK)
                {
                    // COM was initialized successfully on this thread
                    return;
                }
                else if (hr == S_FALSE)
                {
                    // COM is already initialized the for thead
                    // Undo the init we just did and the init we just detected
                    WINRT_IMPL_CoUninitialize();
                    WINRT_IMPL_CoUninitialize();
                }
                else if (hr == RPC_E_CHANGED_MODE)
                {
                    // COM is already initialized for the thread as a different apartment type
                    // This is an error so nothing to do. Undo the init we just detected
                    WINRT_IMPL_CoUninitialize();
                }
                else
                {
                    Assert::AreEqual(S_OK, hr, L"Error in CoInitializeEx()");
                }
            }
        }

        static void AddPackageIfNecessary(PCWSTR packageDirName, PCWSTR packageFullName)
        {
            // If the package is already registered REMOVE IT!
            // Make sure we start with a clean and current state
            // and not state old packages or builds
            if (IsPackageRegistered(packageFullName))
            {
                RemovePackageIfNecessary(packageFullName);
            }

            // Build the target package's .msix filename. It's under the Solution's $(OutDir)
            // NOTE: It could live in ...\Something.msix\... or ...\Something\...
            auto solutionOutDirPath = GetSolutionOutDirPath();
            //
            // Look in ...\Something.msix\...
            auto msix(solutionOutDirPath);
            msix /= packageDirName;
            msix += L".msix";
            msix /= packageDirName;
            msix += L".msix";
            if (!std::filesystem::is_regular_file(msix))
            {
                // Look in ...\Something\...
                msix = solutionOutDirPath;
                msix /= packageDirName;
                msix /= packageDirName;
                msix += L".msix";
                Assert::IsTrue(std::filesystem::is_regular_file(msix));
            }
            auto msixUri = winrt::Windows::Foundation::Uri(msix.c_str());

            // Install the package
            winrt::Windows::Management::Deployment::PackageManager packageManager;
            auto options{ winrt::Windows::Management::Deployment::DeploymentOptions::None };
            auto deploymentResult{ packageManager.AddPackageAsync(msixUri, nullptr, options).get() };
            if (FAILED(deploymentResult.ExtendedErrorCode()))
            {
                auto message = wil::str_printf<wil::unique_process_heap_string>(L"AddPackageAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str());
                Assert::Fail(message.get());
            }
        }

        static void RemovePackageIfNecessary(PCWSTR packageFullName)
        {
            // If the package isn't registered our work here is already done
            if (!IsPackageRegistered(packageFullName))
            {
                return;
            }

            // Remove the package
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
            // Check if the package is registered to the current user via GetPackagePath().
            // GetPackagePath() fails if the package isn't registerd to the current user.
            // Simplest and most portable test across the platforms we might run on
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

        static void AddPackage_ProjectReunionFramework()
        {
            AddPackageIfNecessary(Test::Packages::ProjectReunionFramework::c_PackageDirName, Test::Packages::ProjectReunionFramework::c_PackageFullName);
        }

        static void RemovePackage_ProjectReunionFramework()
        {
            RemovePackageIfNecessary(Test::Packages::ProjectReunionFramework::c_PackageFullName);
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

        static std::filesystem::path GetProjectReunionFrameworkMsixPath()
        {
            // Determine the location of ProjectReunion's Framework's msix. See GetSolutionOutDirPath() for more details.
            auto path = GetSolutionOutDirPath();
            path /= L"Microsoft.ProjectReunion.Framework";
            path /= L"Microsoft.ProjectReunion.Framework.msix";
            return path;
        }

    private:
        static wil::unique_hmodule m_bootstrapDll;
    };
}

wil::unique_hmodule Test::DynamicDependency::BootstrapTests::m_bootstrapDll;
