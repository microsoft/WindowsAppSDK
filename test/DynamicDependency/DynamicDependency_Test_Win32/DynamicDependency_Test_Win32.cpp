// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MsixDynamicDependency.h>

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test::DynamicDependency::Win32
{
	TEST_CLASS(DynamicDependencyTestWin32)
	{
	public:
        TEST_CLASS_INITIALIZE(Setup)
        {
            // CppUnitTest initializes COM as STA before we get called
            // But we don't need (or want) STA, and we do want MTA. We can't
            // stop CppUnitTest from initializing COM but we can uninitialize
            // it and (re)initialize it as MTA. Don't think of it as crude
            // and brutish but rather 'thinking outside the box'...
            COM::CoSuperInitialize();

            TP::RemovePackage_FrameworkMathMultiply();
            TP::RemovePackage_FrameworkMathAdd();
            TP::RemovePackage_MainSidecar();
            TP::RemovePackage_DynamicDependencyDataStore();
            TP::RemovePackage_ProjectReunionFramework();
            TP::AddPackage_ProjectReunionFramework();
            TP::AddPackage_DynamicDependencyDataStore();
            TP::AddPackage_MainSidecar();
            TP::AddPackage_FrameworkMathAdd();
            TP::AddPackage_FrameworkMathMultiply();

            // We need to find Microsoft.ProjectReunion.Bootstrap.dll.
            // Normally it's colocated with the application (i.e. same dir as the exe)
            // but that's not true of our test project (a dll) in our build environment
            // (different directories). So we'll explicitly find and load it so the
            // rest of our test is fine
            auto bootstrapDllAbsoluteFilename{ TF::GetBootstrapAbsoluteFilename() };
            wil::unique_hmodule bootstrapDll(LoadLibrary(bootstrapDllAbsoluteFilename.c_str()));
            {
                const auto lastError{ GetLastError() };
                auto message{ wil::str_printf<wil::unique_process_heap_string>(L"Error in LoadLibrary: %d (0x%X) loading %s", lastError, lastError, bootstrapDllAbsoluteFilename.c_str()) };
                Assert::IsNotNull(bootstrapDll.get(), message.get());
            }
            Assert::AreEqual(S_OK, MddBootstrapInitialize(Test::Packages::MainSidecar::c_MyLifetimeManagerClsid));

            // We want to find Microsoft.ProjectReunion.dll from out test build
            // and not the framework's package location so let's force it...
            // Explicitly load the dll so future references find it already
            // in memory and don't search the file system (and not find it)
            auto projectReunionDllFilename{ TF::GetProjectReunionDllAbsoluteFilename() };
            wil::unique_hmodule projectReunionDll(LoadLibrary(projectReunionDllFilename.c_str()));
            {
                const auto lastError{ GetLastError() };
                auto message{ wil::str_printf<wil::unique_process_heap_string>(L"Error in LoadLibrary: %d (0x%X) loading %s", lastError, lastError, projectReunionDllFilename.c_str()) };
                Assert::IsNotNull(projectReunionDll.get(), message.get());
            }

            m_bootstrapDll = std::move(bootstrapDll);
            m_projectReunionDll = std::move(projectReunionDll);
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            MddBootstrapShutdown();

            m_projectReunionDll.reset();
            m_bootstrapDll.reset();

            TP::RemovePackage_FrameworkMathMultiply();
            TP::RemovePackage_FrameworkMathAdd();
            TP::RemovePackage_MainSidecar();
            TP::RemovePackage_DynamicDependencyDataStore();
            TP::RemovePackage_ProjectReunionFramework();

            winrt::uninit_apartment();
        }

        TEST_METHOD(Create)
        {
            PCWSTR packageFamilyName{ TP::FrameworkMathAdd::c_PackageFamilyName };
            PACKAGE_VERSION minVersion{};
            const auto architectureFilter = MddPackageDependencyProcessorArchitectures::None;
            const auto lifetimeKind = MddPackageDependencyLifetimeKind::Process;
            PCWSTR lifetimeArtifact{};
            const auto options = MddCreatePackageDependencyOptions::None;
            wil::unique_process_heap_string packageDependencyId;
            Assert::AreEqual(S_OK, MddTryCreatePackageDependency(nullptr, packageFamilyName, minVersion, architectureFilter, lifetimeKind, lifetimeArtifact, options, &packageDependencyId));
        }

        TEST_METHOD(Delete_Null)
        {
            PCWSTR packageDependencyId{};
            MddDeletePackageDependency(packageDependencyId);
        }

        TEST_METHOD(Delete)
        {
            PCWSTR packageFamilyName{ TP::FrameworkMathAdd::c_PackageFamilyName };
            PACKAGE_VERSION minVersion{};
            const auto architectureFilter = MddPackageDependencyProcessorArchitectures::None;
            const auto lifetimeKind = MddPackageDependencyLifetimeKind::Process;
            PCWSTR lifetimeArtifact{};
            const auto options = MddCreatePackageDependencyOptions::None;
            wil::unique_process_heap_string packageDependencyId;
            Assert::AreEqual(S_OK, MddTryCreatePackageDependency(nullptr, packageFamilyName, minVersion, architectureFilter, lifetimeKind, lifetimeArtifact, options, &packageDependencyId));

            MddDeletePackageDependency(packageDependencyId.get());
        }

        TEST_METHOD(Create_Add_Remove_Delete)
        {
            PCWSTR packageFamilyName{ TP::FrameworkMathAdd::c_PackageFamilyName };
            PACKAGE_VERSION minVersion{};
            const auto architectureFilter = MddPackageDependencyProcessorArchitectures::None;
            const auto lifetimeKind = MddPackageDependencyLifetimeKind::Process;
            PCWSTR lifetimeArtifact{};
            const auto createOptions = MddCreatePackageDependencyOptions::None;
            wil::unique_process_heap_string packageDependencyId;
            Assert::AreEqual(S_OK, MddTryCreatePackageDependency(nullptr, packageFamilyName, minVersion, architectureFilter, lifetimeKind, lifetimeArtifact, createOptions, &packageDependencyId));

            const INT32 rank = MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT;
            const auto addOptions = MddAddPackageDependencyOptions::None;
            MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext{};
            wil::unique_process_heap_string packageFullName;
            Assert::AreEqual(S_OK, MddAddPackageDependency(packageDependencyId.get(), rank, addOptions, &packageDependencyContext, &packageFullName));
            Assert::IsNotNull(packageFullName.get());
            auto actualPackageFullName = std::wstring(packageFullName.get());
            auto expectedPackageFullName = std::wstring(TP::FrameworkMathAdd::c_PackageFullName);
            Assert::AreEqual(actualPackageFullName, expectedPackageFullName);

            MddRemovePackageDependency(packageDependencyContext);
            //TODO:Verify removal

            MddDeletePackageDependency(packageDependencyId.get());
        }

        TEST_METHOD(GetResolvedPackageFullName)
        {
            PCWSTR packageDependencyId{};
            wil::unique_process_heap_string packageFullName;
            Assert::AreEqual(E_NOTIMPL, MddGetResolvedPackageFullNameForPackageDependency(packageDependencyId, &packageFullName));
        }

    private:
        static wil::unique_hmodule m_bootstrapDll;
        static wil::unique_hmodule m_projectReunionDll;
    };
}

wil::unique_hmodule Test::DynamicDependency::Win32::DynamicDependencyTestWin32::m_bootstrapDll;
wil::unique_hmodule Test::DynamicDependency::Win32::DynamicDependencyTestWin32::m_projectReunionDll;
