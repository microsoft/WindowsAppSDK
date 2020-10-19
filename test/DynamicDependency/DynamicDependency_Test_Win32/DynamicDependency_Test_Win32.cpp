// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MsixDynamicDependency.h>

#include <Math.Add.h>
#include <Math.Multiply.h>

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

            // Remove our packages in case they were previously installed and incompletely removed
            TP::RemovePackage_MainSidecar();
            TP::RemovePackage_DynamicDependencyDataStore();
            TP::RemovePackage_ProjectReunionFramework();
            TP::RemovePackage_FrameworkMathMultiply();
            TP::RemovePackage_FrameworkMathAdd();

            // Install our needed packages
            TP::AddPackage_FrameworkMathAdd();
            TP::AddPackage_FrameworkMathMultiply();
            TP::AddPackage_ProjectReunionFramework();
            TP::AddPackage_DynamicDependencyDataStore();
            TP::AddPackage_MainSidecar();

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
            m_bootstrapDll = std::move(bootstrapDll);

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
            m_projectReunionDll = std::move(projectReunionDll);
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            MddBootstrapShutdown();

            m_projectReunionDll.reset();
            m_bootstrapDll.reset();

            TP::RemovePackage_MainSidecar();
            TP::RemovePackage_DynamicDependencyDataStore();
            TP::RemovePackage_ProjectReunionFramework();
            TP::RemovePackage_FrameworkMathMultiply();
            TP::RemovePackage_FrameworkMathAdd();

            // Undo COM::CoSuperInitialize() and restore the thread to its initial state
            // as when CppUnitTest  called us. Or as close as we can get to it
            winrt::uninit_apartment();
            winrt::init_apartment(winrt::apartment_type::single_threaded);
        }

        TEST_METHOD(Create_Delete)
        {
            PCWSTR packageFamilyName{ TP::FrameworkMathAdd::c_PackageFamilyName };
            PACKAGE_VERSION minVersion{};
            const MddPackageDependencyProcessorArchitectures architectureFilter{};
            const auto lifetimeKind{ MddPackageDependencyLifetimeKind::Process };
            PCWSTR lifetimeArtifact{};
            const MddCreatePackageDependencyOptions options{};
            wil::unique_process_heap_string packageDependencyId;
            Assert::AreEqual(S_OK, MddTryCreatePackageDependency(nullptr, packageFamilyName, minVersion, architectureFilter, lifetimeKind, lifetimeArtifact, options, &packageDependencyId));

            MddDeletePackageDependency(packageDependencyId.get());
        }

        TEST_METHOD(Delete_Null)
        {
            PCWSTR packageDependencyId{};
            MddDeletePackageDependency(packageDependencyId);
        }

        TEST_METHOD(Delete_NotFound)
        {
            PCWSTR packageDependencyId{ L"This.Does.Not.Exist" };
            MddDeletePackageDependency(packageDependencyId);
        }

        TEST_METHOD(Create_Add_Remove_Delete_GetResolved)
        {
            // Setup our dynamic dependency

            auto expectedPackageFullName{ std::wstring(TP::FrameworkMathAdd::c_PackageFullName) };
            VerifyPackageInPackageGraph(expectedPackageFullName, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            auto pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH") };
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());

            PCWSTR packageFamilyName{ TP::FrameworkMathAdd::c_PackageFamilyName };
            PACKAGE_VERSION minVersion{};
            const MddPackageDependencyProcessorArchitectures architectureFilter{};
            const auto lifetimeKind{ MddPackageDependencyLifetimeKind::Process };
            PCWSTR lifetimeArtifact{};
            const MddCreatePackageDependencyOptions createOptions{};
            wil::unique_process_heap_string packageDependencyId;
            Assert::AreEqual(S_OK, MddTryCreatePackageDependency(nullptr, packageFamilyName, minVersion, architectureFilter, lifetimeKind, lifetimeArtifact, createOptions, &packageDependencyId));

            VerifyPackageInPackageGraph(expectedPackageFullName, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId.get(), S_OK, expectedPackageFullName);

            const INT32 rank{ MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT };
            const MddAddPackageDependencyOptions addOptions{};
            MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext{};
            wil::unique_process_heap_string packageFullName;
            Assert::AreEqual(S_OK, MddAddPackageDependency(packageDependencyId.get(), rank, addOptions, &packageDependencyContext, &packageFullName));
            Assert::IsNotNull(packageFullName.get());
            auto actualPackageFullName{ std::wstring(packageFullName.get()) };
            Assert::AreEqual(actualPackageFullName, expectedPackageFullName);

            VerifyPackageInPackageGraph(expectedPackageFullName, S_OK);
            auto packagePath{ TP::GetPackagePath(expectedPackageFullName) };
            VerifyPathEnvironmentVariable(packagePath, pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId.get(), S_OK, expectedPackageFullName);

            // Let's use resources from the dynamically added package
            auto mathAddDllFilename{ L"Framework.Math.Add.dll" };
            wil::unique_hmodule mathAddDll(LoadLibrary(mathAddDllFilename));
            {
                const auto lastError{ GetLastError() };
                auto message{ wil::str_printf<wil::unique_process_heap_string>(L"Error in LoadLibrary: %d (0x%X) loading %s", lastError, lastError, mathAddDllFilename) };
                Assert::IsNotNull(mathAddDll.get(), message.get());
            }

            auto mathAdd{ GetProcAddressByFunctionDeclaration(mathAddDll.get(), Math_Add) };
            Assert::IsNotNull(mathAdd);

            const int expectedValue{ 2 + 3 };
            const auto actualValue{ mathAdd(2, 3) };
            Assert::AreEqual(expectedValue, actualValue);

            // Tear down our dynamic dependency

            MddRemovePackageDependency(packageDependencyContext);

            VerifyPackageInPackageGraph(expectedPackageFullName, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId.get(), S_OK, expectedPackageFullName);

            MddDeletePackageDependency(packageDependencyId.get());

            VerifyPackageInPackageGraph(expectedPackageFullName, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId.get(), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
        }

        TEST_METHOD(GetResolvedPackageFullName_Null)
        {
            PCWSTR packageDependencyId{};
            wil::unique_process_heap_string packageFullName;
            Assert::AreEqual(E_INVALIDARG, MddGetResolvedPackageFullNameForPackageDependency(packageDependencyId, &packageFullName));
        }

        TEST_METHOD(GetResolvedPackageFullName_NotFound)
        {
            PCWSTR packageDependencyId{ L"This.Does.Not.Exist" };
            wil::unique_process_heap_string packageFullName;
            Assert::AreEqual(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), MddGetResolvedPackageFullNameForPackageDependency(packageDependencyId, &packageFullName));
        }

    private:
        static void VerifyPackageDependency(
            PCWSTR packageDependencyId,
            const HRESULT expectedHR,
            PCWSTR expectedPackageFullName = nullptr)
        {
            wil::unique_process_heap_string packageFullName;
            Assert::AreEqual(expectedHR, MddGetResolvedPackageFullNameForPackageDependency(packageDependencyId, &packageFullName));
            if (!expectedPackageFullName)
            {
                Assert::IsTrue(!packageFullName);
            }
            else
            {
                Assert::AreEqual(std::wstring(packageFullName.get()), std::wstring(expectedPackageFullName));
            }
        }

        static void VerifyPackageDependency(
            PCWSTR packageDependencyId,
            const HRESULT expectedHR,
            const std::wstring& expectedPackageFullName)
        {
            VerifyPackageDependency(packageDependencyId, expectedHR, expectedPackageFullName.c_str());
        }

        static void VerifyPathEnvironmentVariable(PCWSTR path)
        {
            std::wstring expectedPath{ path };
            std::wstring pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
            Assert::AreEqual(expectedPath, pathEnvironmentVariable);
        }

        static void VerifyPathEnvironmentVariable(PCWSTR prefix, PCWSTR path)
        {
            std::wstring pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
            std::wstring expectedPath{ std::wstring(prefix) + L";" + path };
            Assert::AreEqual(expectedPath, pathEnvironmentVariable);
        }

        static void VerifyPathEnvironmentVariable(const std::wstring& prefix, PCWSTR path)
        {
            VerifyPathEnvironmentVariable(prefix.c_str(), path);
        }

        static void VerifyPackageInPackageGraph(
            const std::wstring& packageFullName,
            const HRESULT expectedHR)
        {
            UINT32 packageInfoCount{};
            const PACKAGE_INFO* packageInfo{};
            wil::unique_cotaskmem_ptr<BYTE[]> packageInfosBuffer;
            Assert::AreEqual(expectedHR, GetCurrentPackageInfo(packageInfoCount, packageInfo, packageInfosBuffer));
            if (expectedHR == S_OK)
            {
                Assert::AreNotEqual(-1, FindPackageFullNameInPackageInfoArray(packageFullName, packageInfoCount, packageInfo));
            }
        }

        static HRESULT GetCurrentPackageInfo(
            UINT32& packageInfoCount,
            const PACKAGE_INFO*& packageInfo,
            wil::unique_cotaskmem_ptr<BYTE[]>& buffer)
        {
            const UINT32 flags = PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_RESOURCE | PACKAGE_FILTER_BUNDLE;
            const PackagePathType packagePathType = PackagePathType_Effective;
            return GetCurrentPackageInfo(flags, packagePathType, packageInfoCount, packageInfo, buffer);
        }

        static HRESULT GetCurrentPackageInfo(
            const UINT32 flags,
            const PackagePathType packagePathType,
            UINT32& packageInfoCount,
            const PACKAGE_INFO*& packageInfo,
            wil::unique_cotaskmem_ptr<BYTE[]>& buffer)
        {
            UINT32 bufferLength{};
            LONG rc{ GetCurrentPackageInfo2(flags, packagePathType, &bufferLength, nullptr, nullptr) };
            RETURN_HR_IF(HRESULT_FROM_WIN32(rc), rc != ERROR_INSUFFICIENT_BUFFER);

            buffer = wil::make_unique_cotaskmem<BYTE[]>(bufferLength);
            RETURN_IF_WIN32_ERROR(GetCurrentPackageInfo2(flags, packagePathType, &bufferLength, buffer.get(), &packageInfoCount));
            packageInfo = reinterpret_cast<PACKAGE_INFO*>(buffer.get());
            return S_OK;
        }

        static int FindPackageFullNameInPackageInfoArray(
            const std::wstring& packageFullName,
            const size_t packageInfoCount,
            const PACKAGE_INFO* packageInfo)
        {
            for (UINT32 index = 0; index < packageInfoCount; ++index, ++packageInfo)
            {
                if (CompareStringOrdinal(packageFullName.c_str(), -1, packageInfo->packageFullName, -1, TRUE) == CSTR_EQUAL)
                {
                    return true;
                }
            }
            return -1;
        }

    private:
        static wil::unique_hmodule m_bootstrapDll;
        static wil::unique_hmodule m_projectReunionDll;
    };
}

wil::unique_hmodule Test::DynamicDependency::Win32::DynamicDependencyTestWin32::m_bootstrapDll;
wil::unique_hmodule Test::DynamicDependency::Win32::DynamicDependencyTestWin32::m_projectReunionDll;
