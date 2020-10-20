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

        TEST_METHOD(FullLifecycle_ProcessLifetime_Framework_ProjectReunion)
        {
            // Setup our dynamic dependencies

            std::wstring expectedPackageFullName{ TP::ProjectReunionFramework::c_PackageFullName };

            VerifyPackageInPackageGraph(expectedPackageFullName, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            auto pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH") };
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());

            // -- TryCreate

            wil::unique_process_heap_string packageDependencyId{ Mdd_TryCreate_ProjectReunionFramework() };

            VerifyPackageInPackageGraph(expectedPackageFullName, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId.get(), S_OK, expectedPackageFullName);

            // -- Add

            wil::unique_process_heap_string packageFullName;
            MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext{ Mdd_Add(packageDependencyId.get(), packageFullName) };
            Assert::IsNotNull(packageFullName.get());
            std::wstring actualPackageFullName{ packageFullName.get() };
            Assert::AreEqual(actualPackageFullName, expectedPackageFullName);

            VerifyPackageInPackageGraph(expectedPackageFullName, S_OK);
            auto packagePath{ TP::GetPackagePath(expectedPackageFullName) };
            VerifyPathEnvironmentVariable(packagePath, pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId.get(), S_OK, expectedPackageFullName);

            // Let's use resources from the dynamically added package
            auto projectReunionDllFilename{ L"Microsoft.ProjectReunion.dll" };
            wil::unique_hmodule projectReunionDll(LoadLibrary(projectReunionDllFilename));
            {
                const auto lastError{ GetLastError() };
                auto message{ wil::str_printf<wil::unique_process_heap_string>(L"Error in LoadLibrary: %d (0x%X) loading %s", lastError, lastError, projectReunionDllFilename) };
                Assert::IsNotNull(projectReunionDll.get(), message.get());
            }

            auto mddGetResolvedPackageFullNameForPackageDependency{ GetProcAddressByFunctionDeclaration(projectReunionDll.get(), MddGetResolvedPackageFullNameForPackageDependency) };
            Assert::IsNotNull(mddGetResolvedPackageFullNameForPackageDependency);

            wil::unique_process_heap_string resolvedPackageFullName;
            Assert::AreEqual(S_OK, mddGetResolvedPackageFullNameForPackageDependency(packageDependencyId.get(), &resolvedPackageFullName));
            Assert::IsNotNull(resolvedPackageFullName.get());
            std::wstring actualResolvedPackageFullName{ resolvedPackageFullName.get() };
            const auto& expectedResolvedPackageFullName{ expectedPackageFullName };
            Assert::AreEqual(expectedResolvedPackageFullName, actualResolvedPackageFullName);

            // Tear down our dynamic dependencies

            // -- Remove

            MddRemovePackageDependency(packageDependencyContext);

            VerifyPackageInPackageGraph(expectedPackageFullName, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId.get(), S_OK, expectedPackageFullName);

            // -- Delete

            MddDeletePackageDependency(packageDependencyId.get());

            VerifyPackageInPackageGraph(expectedPackageFullName, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId.get(), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
        }

        TEST_METHOD(FullLifecycle_ProcessLifetime_Frameworks_ProjectReunion_MathAdd)
        {
            // Setup our dynamic dependencies

            std::wstring expectedPackageFullName_ProjectReunionFramework{ TP::ProjectReunionFramework::c_PackageFullName };
            std::wstring expectedPackageFullName_FrameworkMathAdd{ TP::FrameworkMathAdd::c_PackageFullName };

            VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            auto pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH") };
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());

            // -- TryCreate

            wil::unique_process_heap_string packageDependencyId_ProjectReunionFramework{ Mdd_TryCreate_ProjectReunionFramework() };

            VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId_ProjectReunionFramework.get(), S_OK, expectedPackageFullName_ProjectReunionFramework);

            wil::unique_process_heap_string packageDependencyId_FrameworkMathAdd{ Mdd_TryCreate_FrameworkMathAdd() };

            VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId_ProjectReunionFramework.get(), S_OK, expectedPackageFullName_ProjectReunionFramework);
            VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);

            // -- Add

            wil::unique_process_heap_string packageFullName_ProjectReunionFramework;
            MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext_ProjectReunionFramework{ Mdd_Add(packageDependencyId_ProjectReunionFramework.get(), packageFullName_ProjectReunionFramework) };
            Assert::IsNotNull(packageFullName_ProjectReunionFramework.get());
            std::wstring actualPackageFullName_ProjectReunionFramework{ packageFullName_ProjectReunionFramework.get() };
            Assert::AreEqual(actualPackageFullName_ProjectReunionFramework, expectedPackageFullName_ProjectReunionFramework);

            VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, S_OK);
            VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
            auto packagePath_ProjectReunionFramework{ TP::GetPackagePath(expectedPackageFullName_ProjectReunionFramework) };
            VerifyPathEnvironmentVariable(packagePath_ProjectReunionFramework, pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId_ProjectReunionFramework.get(), S_OK, expectedPackageFullName_ProjectReunionFramework);
            VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);

            wil::unique_process_heap_string packageFullName_FrameworkMathAdd;
            MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext_FrameworkMathAdd{ Mdd_Add(packageDependencyId_FrameworkMathAdd.get(), packageFullName_FrameworkMathAdd) };
            Assert::IsNotNull(packageFullName_FrameworkMathAdd.get());
            std::wstring actualPackageFullName_FrameworkMathAdd{ packageFullName_FrameworkMathAdd.get() };
            Assert::AreEqual(actualPackageFullName_FrameworkMathAdd, expectedPackageFullName_FrameworkMathAdd);

            VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, S_OK);
            VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
            auto packagePath_FrameworkMathAdd{ TP::GetPackagePath(expectedPackageFullName_FrameworkMathAdd) };
            VerifyPathEnvironmentVariable(packagePath_ProjectReunionFramework, packagePath_FrameworkMathAdd, pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId_ProjectReunionFramework.get(), S_OK, expectedPackageFullName_ProjectReunionFramework);
            VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);

            // -- Use it

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

            // Tear down our dynamic dependencies

            // -- Remove

            MddRemovePackageDependency(packageDependencyContext_FrameworkMathAdd);

            VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, S_OK);
            VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
            VerifyPathEnvironmentVariable(packagePath_ProjectReunionFramework, pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId_ProjectReunionFramework.get(), S_OK, expectedPackageFullName_ProjectReunionFramework);
            VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);

            MddRemovePackageDependency(packageDependencyContext_ProjectReunionFramework);

            VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId_ProjectReunionFramework.get(), S_OK, expectedPackageFullName_ProjectReunionFramework);
            VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);

            // -- Delete

            MddDeletePackageDependency(packageDependencyId_FrameworkMathAdd.get());

            VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId_ProjectReunionFramework.get(), S_OK, expectedPackageFullName_ProjectReunionFramework);
            VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));

            MddDeletePackageDependency(packageDependencyId_ProjectReunionFramework.get());

            VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
            VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
            VerifyPackageDependency(packageDependencyId_ProjectReunionFramework.get(), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
            VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
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

        static void VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path)
        {
            std::wstring pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
            std::wstring expectedPath{ std::wstring(path1) + L";" + path };
            Assert::AreEqual(expectedPath, pathEnvironmentVariable);
        }

        static void VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path2, PCWSTR path)
        {
            std::wstring pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH").get() };
            std::wstring expectedPath{ std::wstring(path1) + L";" + path2 + L";" + path };
            Assert::AreEqual(expectedPath, pathEnvironmentVariable);
        }

        static void VerifyPathEnvironmentVariable(const std::wstring& path1, PCWSTR path)
        {
            VerifyPathEnvironmentVariable(path1.c_str(), path);
        }

        static void VerifyPathEnvironmentVariable(const std::wstring& path1, const std::wstring& path2, PCWSTR path)
        {
            VerifyPathEnvironmentVariable(path1.c_str(), path2.c_str(), path);
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

        static void VerifyPackageNotInPackageGraph(
            const std::wstring& packageFullName,
            const HRESULT expectedHR)
        {
            UINT32 packageInfoCount{};
            const PACKAGE_INFO* packageInfo{};
            wil::unique_cotaskmem_ptr<BYTE[]> packageInfosBuffer;
            Assert::AreEqual(expectedHR, GetCurrentPackageInfo(packageInfoCount, packageInfo, packageInfosBuffer));
            if (expectedHR == S_OK)
            {
                Assert::AreEqual(-1, FindPackageFullNameInPackageInfoArray(packageFullName, packageInfoCount, packageInfo));
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
        // Overloads and conveniences for TryCreate to simplify test readability
        wil::unique_process_heap_string Mdd_TryCreate(
            PCWSTR packageFamilyName,
            const MddPackageDependencyLifetimeKind lifetimeKind = MddPackageDependencyLifetimeKind::Process,
            PCWSTR lifetimeArtifact = nullptr)
        {
            PACKAGE_VERSION minVersion{};
            const MddPackageDependencyProcessorArchitectures architectureFilter{};
            const MddCreatePackageDependencyOptions createOptions{};
            wil::unique_process_heap_string packageDependencyId;
            Assert::AreEqual(S_OK, MddTryCreatePackageDependency(nullptr, packageFamilyName, minVersion, architectureFilter, lifetimeKind, lifetimeArtifact, createOptions, &packageDependencyId));
            return packageDependencyId;
        }

        wil::unique_process_heap_string Mdd_TryCreate_ProjectReunionFramework(
            const MddPackageDependencyLifetimeKind lifetimeKind = MddPackageDependencyLifetimeKind::Process,
            PCWSTR lifetimeArtifact = nullptr)
        {
            return Mdd_TryCreate(TP::ProjectReunionFramework::c_PackageFamilyName, lifetimeKind, lifetimeArtifact);
        }

        wil::unique_process_heap_string Mdd_TryCreate_FrameworkMathAdd(
            const MddPackageDependencyLifetimeKind lifetimeKind = MddPackageDependencyLifetimeKind::Process,
            PCWSTR lifetimeArtifact = nullptr)
        {
            return Mdd_TryCreate(TP::FrameworkMathAdd::c_PackageFamilyName, lifetimeKind, lifetimeArtifact);
        }

    private:
        // Overloads and conveniences for TryCreate to simplify test readability
        MDD_PACKAGEDEPENDENCY_CONTEXT Mdd_Add(
            PCWSTR packageDependencyId,
            wil::unique_process_heap_string& packageFullName)
        {
            const INT32 rank{ MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT };
            const MddAddPackageDependencyOptions addOptions{};
            MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext{};
            Assert::AreEqual(S_OK, MddAddPackageDependency(packageDependencyId, rank, addOptions, &packageDependencyContext, &packageFullName));
            return packageDependencyContext;
        }

    private:
        static wil::unique_hmodule m_bootstrapDll;
        static wil::unique_hmodule m_projectReunionDll;
    };
}

wil::unique_hmodule Test::DynamicDependency::Win32::DynamicDependencyTestWin32::m_bootstrapDll;
wil::unique_hmodule Test::DynamicDependency::Win32::DynamicDependencyTestWin32::m_projectReunionDll;
