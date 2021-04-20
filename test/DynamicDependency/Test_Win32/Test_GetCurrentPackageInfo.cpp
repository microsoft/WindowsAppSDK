// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

inline DWORD WIN32_FROM_HRESULT(const HRESULT hr)
{
    return HRESULT_FACILITY(hr) == FACILITY_WIN32 ? HRESULT_CODE(hr) : hr;
}

namespace Test::DynamicDependency
{
    class GetCurrentPackageInfoTests
    {
    public:
        BEGIN_TEST_CLASS(GetCurrentPackageInfoTests)
            //TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(Setup)
        {
            TP::RemovePackage_DynamicDependencyLifetimeManagerGC1010();
            TP::RemovePackage_DynamicDependencyLifetimeManagerGC1000();
            TP::RemovePackage_DynamicDependencyLifetimeManager();
            TP::RemovePackage_DynamicDependencyDataStore();
            TP::RemovePackage_ProjectReunionFramework();
            TP::RemovePackage_FrameworkMathMultiply();
            TP::RemovePackage_FrameworkMathAdd();
            TP::AddPackage_FrameworkMathAdd();
            TP::AddPackage_ProjectReunionFramework();
            TP::AddPackage_DynamicDependencyLifetimeManager();

            // Load the DLL hooking GetCurrentPackageInfo*()
            auto dllAbsoluteFilename{ TF::GetProjectReunionDllAbsoluteFilename() };
            wil::unique_hmodule dll(LoadLibrary(dllAbsoluteFilename.c_str()));
            if (!dll)
            {
                const auto lastError{ GetLastError() };
                auto message{ wil::str_printf<wil::unique_process_heap_string>(L"Error in LoadLibrary: %d (0x%X) loading %s", lastError, lastError, dllAbsoluteFilename.c_str()) };
                VERIFY_IS_NOT_NULL(dll.get(), message.get());
            }

            m_dll = std::move(dll);

            return true;
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            m_dll.reset();

            TP::RemovePackage_DynamicDependencyLifetimeManager();
            TP::RemovePackage_ProjectReunionFramework();
            TP::RemovePackage_FrameworkMathAdd();

            return true;
        }

        TEST_METHOD(Unpackaged_PackageGraph0)
        {
            PrintGetCurrentPackageInfoHeader();

            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_STATIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DYNAMIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC);

            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_DIRECT);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_DYNAMIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC);

            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_DYNAMIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC);

            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_RESOURCE);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_RESOURCE | PACKAGE_FILTER_STATIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_RESOURCE | PACKAGE_FILTER_DYNAMIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_RESOURCE | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC);

            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_OPTIONAL);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_STATIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_DYNAMIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC);

            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_IS_IN_RELATED_SET);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_IS_IN_RELATED_SET | PACKAGE_FILTER_STATIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_IS_IN_RELATED_SET | PACKAGE_FILTER_DYNAMIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_IS_IN_RELATED_SET | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC);

            VerifyGenerationId(0);
        }

        TEST_METHOD(Unpackaged_PackageGraph1)
        {
            // -- TryCreate
            const PACKAGE_VERSION minVersion{};
            const MddPackageDependencyProcessorArchitectures architectures{};
            const auto lifetimeKind{ MddPackageDependencyLifetimeKind::Process };
            PCWSTR lifetimeArtifact{};
            const MddCreatePackageDependencyOptions createOptions{};
            wil::unique_process_heap_string packageDependencyId_FrameworkMathAdd;
            VERIFY_ARE_EQUAL(S_OK, MddTryCreatePackageDependency(nullptr, TP::FrameworkMathAdd::c_PackageFamilyName, minVersion, architectures, lifetimeKind, lifetimeArtifact, createOptions, &packageDependencyId_FrameworkMathAdd));

            // -- Add
            const auto rank{ MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT };
            const MddAddPackageDependencyOptions addOptions{};
            MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext_FrameworkMathAdd{};
            wil::unique_process_heap_string packageFullName_FrameworkMathAdd;
            VERIFY_ARE_EQUAL(S_OK, MddAddPackageDependency(packageDependencyId_FrameworkMathAdd.get(), rank, addOptions, &packageDependencyContext_FrameworkMathAdd, &packageFullName_FrameworkMathAdd));

            // Verify GetCurrentPackageInfo*()
            PrintGetCurrentPackageInfoHeader();

            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), 0, 0, S_OK, 0, 0);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_STATIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DYNAMIC, S_OK, 0, 0, S_OK, 0, 0);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC, S_OK, 0, 0, S_OK, 0, 0);

            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_DIRECT, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), 0, 0, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_DYNAMIC, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1);

            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), 0, 0, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_DYNAMIC, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1);

            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_RESOURCE, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), 0, 0, S_OK, 0, 0);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_RESOURCE | PACKAGE_FILTER_STATIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_RESOURCE | PACKAGE_FILTER_DYNAMIC, S_OK, 0, 0, S_OK, 0, 0);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_RESOURCE | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC, S_OK, 0, 0, S_OK, 0, 0);

            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_OPTIONAL, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), 0, 0, S_OK, 0, 0);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_STATIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_DYNAMIC, S_OK, 0, 0, S_OK, 0, 0);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC, S_OK, 0, 0, S_OK, 0, 0);

            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_IS_IN_RELATED_SET, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), 0, 0, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_IS_IN_RELATED_SET | PACKAGE_FILTER_STATIC);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_IS_IN_RELATED_SET | PACKAGE_FILTER_DYNAMIC, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1);
            VerifyGetCurrentPackageInfo123(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_IS_IN_RELATED_SET | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1, HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), 1, 1);

            // Verify GetCurrentPackageInfo for GenerationId
            VerifyGenerationId(1, S_OK);

            // -- Remove
            MddRemovePackageDependency(packageDependencyContext_FrameworkMathAdd);

            // -- Delete
            MddDeletePackageDependency(packageDependencyId_FrameworkMathAdd.get());
        }

        void VerifyGetCurrentPackageInfo1(
            const UINT32 flags,
            const HRESULT expectedHR = HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE),
            const UINT32 minExpectedBufferSize = 0,
            const UINT32 expectedCount = 0)
        {
            const LONG expectedRC{ static_cast<LONG>(WIN32_FROM_HRESULT(expectedHR)) };
            UINT32 bufferSize{};
            UINT32 count{};
            const auto rc{ GetCurrentPackageInfo(flags, &bufferSize, nullptr, &count) };
            PrintGetCurrentPackageInfoN(L"GetCurrentPackageInfo ", flags, rc, bufferSize, count, expectedRC, minExpectedBufferSize, expectedCount);
            VERIFY_ARE_EQUAL(expectedRC, rc);
            VERIFY_IS_TRUE(minExpectedBufferSize <= bufferSize);
            VERIFY_ARE_EQUAL(expectedCount, count);
        }

        void VerifyGetCurrentPackageInfo2(
            const UINT32 flags,
            const HRESULT expectedHR = HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE),
            const UINT32 minExpectedBufferSize = 0,
            const UINT32 expectedCount = 0)
        {
            const LONG expectedRC{ static_cast<LONG>(WIN32_FROM_HRESULT(expectedHR)) };
            const auto packagePathType{ PackagePathType_Install };
            UINT32 bufferSize{};
            UINT32 count{};
            const auto rc{ GetCurrentPackageInfo2(flags, packagePathType, &bufferSize, nullptr, &count) };
            PrintGetCurrentPackageInfoN(L"GetCurrentPackageInfo2", flags, rc, bufferSize, count, expectedRC, minExpectedBufferSize, expectedCount);
            VERIFY_ARE_EQUAL(expectedRC, rc);
            VERIFY_IS_TRUE(minExpectedBufferSize <= bufferSize);
            VERIFY_ARE_EQUAL(expectedCount, count);
        }

        void VerifyGetCurrentPackageInfo3(
            const UINT32 flags,
            const HRESULT expectedHR = HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE),
            const UINT32 minExpectedBufferSize = 0,
            const UINT32 expectedCount = 0)
        {
            if (!IsGetCurrentPackageInfo3Supported())
            {
                return;
            }

            const auto packageInfoType{ PackageInfoType_PackageInfoInstallPath };
            UINT32 bufferSize{};
            UINT32 count{};
            const auto hr{ m_getCurrentPackageInfo3(flags, packageInfoType, &bufferSize, nullptr, &count) };
            PrintGetCurrentPackageInfoN(L"GetCurrentPackageInfo3", flags, hr, bufferSize, count, expectedHR, minExpectedBufferSize, expectedCount);
            VERIFY_ARE_EQUAL(expectedHR, hr);
            VERIFY_IS_TRUE(minExpectedBufferSize <= bufferSize);
            VERIFY_ARE_EQUAL(expectedCount, count);
        }

        void VerifyGetCurrentPackageInfo123(
            const UINT32 flags,
            const HRESULT expectedHR12 = HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE),
            const UINT32 minExpectedBufferSize12 = 0,
            const UINT32 expectedCount12 = 0,
            const HRESULT expectedHR3 = HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE),
            const UINT32 minExpectedBufferSize3 = 0,
            const UINT32 expectedCount3 = 0)
        {
            VerifyGetCurrentPackageInfo1(flags, expectedHR12, minExpectedBufferSize12, expectedCount12);
            VerifyGetCurrentPackageInfo2(flags, expectedHR12, minExpectedBufferSize12, expectedCount12);
            VerifyGetCurrentPackageInfo3(flags, expectedHR3, minExpectedBufferSize3, expectedCount3);
        }

        void VerifyGenerationId(
            const UINT32 expectedGenerationId,
            const HRESULT expectedHR = HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE))
        {
            if (!IsGetCurrentPackageInfo3Supported())
            {
                return;
            }

            UINT32 generationId{};
            UINT32 bufferSize{ static_cast<UINT32>(sizeof(generationId)) };
            const auto hr{ m_getCurrentPackageInfo3(0, PackageInfoType_PackageInfoGeneration, &bufferSize, &generationId, nullptr) };
            auto message{ wil::str_printf<wil::unique_process_heap_string>(L"Get...GenerationId: hr:0x%X id:%u\n"
                                                                           L"          Expected: hr:0x%X id:%u",
                                                                           hr, generationId, expectedHR, expectedGenerationId) };
            VERIFY_IS_TRUE(true, message.get());
            OutputDebugStringW(message.get());
            VERIFY_ARE_EQUAL(expectedHR, hr);
            VERIFY_ARE_EQUAL(expectedGenerationId, generationId);
        }

        void PrintGetCurrentPackageInfoHeader()
        {
            auto message{ wil::str_printf<wil::unique_process_heap_string>(L"%-10s %5s %7s %s\n", L"ErrorCode", L"Count", L"BufSize", L"Function") };
            VERIFY_IS_TRUE(true, message.get());
            OutputDebugStringW(message.get());
        }

        void PrintGetCurrentPackageInfoN(
            PCWSTR label,
            const UINT32 flags,
            const LONG errorCode,
            const UINT32 bufferSize,
            const UINT32 count,
            const LONG expectedErrorCode,
            const UINT32 minExpectedBufferSize,
            const UINT32 expectedCount)
        {
            std::wstring message;
            {
                auto s{ wil::str_printf<wil::unique_process_heap_string>(L"0x%08X %3u %6u %23s(0x%08X", errorCode, count, bufferSize, label, flags) };
                message += s.get();
            }
            if (WI_IsFlagSet(flags, PACKAGE_FILTER_HEAD))
            {
                message += L" HEAD";
            }
            if (WI_IsFlagSet(flags, PACKAGE_FILTER_DIRECT))
            {
                message += L" DIRECT";
            }
            if (WI_IsFlagSet(flags, PACKAGE_FILTER_RESOURCE))
            {
                message += L" RESOURCE";
            }
            if (WI_IsFlagSet(flags, PACKAGE_FILTER_OPTIONAL))
            {
                message += L" OPTIONAL";
            }
            if (WI_IsFlagSet(flags, PACKAGE_FILTER_IS_IN_RELATED_SET))
            {
                message += L" RELATEDSET";
            }
            if (WI_IsFlagSet(flags, PACKAGE_FILTER_STATIC))
            {
                message += L" STATIC";
            }
            if (WI_IsFlagSet(flags, PACKAGE_FILTER_DYNAMIC))
            {
                message += L" DYNAMIC";
            }
            message += L") --";
            if ((errorCode == expectedErrorCode) && (count == expectedCount) && (bufferSize >= minExpectedBufferSize))
            {
                message += L" OK";
            }
            else
            {
                if (errorCode != expectedErrorCode)
                {
                    auto s{ wil::str_printf<wil::unique_process_heap_string>(L" ErrorCode:0x%08X", expectedErrorCode) };
                    message += s.get();
                }
                if (count != expectedCount)
                {
                    auto s{ wil::str_printf<wil::unique_process_heap_string>(L" Count:%u", expectedCount) };
                    message += s.get();
                }
                if (bufferSize < minExpectedBufferSize)
                {
                    auto s{ wil::str_printf<wil::unique_process_heap_string>(L" BufferSize:%u", minExpectedBufferSize) };
                    message += s.get();
                }
            }
            message += L"\n";
            VERIFY_IS_TRUE(true, message.c_str());
            OutputDebugStringW(message.c_str());
        }

    private:
        wil::unique_hmodule m_kernelbaseDll;

        typedef HRESULT(WINAPI* GetCurrentPackageInfo3Function)(
            _In_ UINT32 flags,
            _In_ PackageInfoType packageInfoType,
            _Inout_ UINT32* bufferLength,
            _Out_writes_bytes_opt_(*bufferLength) void* buffer,
            _Out_opt_ UINT32* count);
        GetCurrentPackageInfo3Function m_getCurrentPackageInfo3{};

        void EnsureGetCurrentPackageInfo3IsIniitalizedIfExists()
        {
            if (!m_kernelbaseDll)
            {
                wil::unique_hmodule dll{ LoadLibraryW(L"kernelbase.dll") };
                FAIL_FAST_HR_IF_NULL(E_UNEXPECTED, dll);

                auto function{ reinterpret_cast<GetCurrentPackageInfo3Function>(GetProcAddress(dll.get(), "GetCurrentPackageInfo3")) };
                if (!function)
                {
                    const auto lastError{ GetLastError() };
                    if (lastError != ERROR_PROC_NOT_FOUND)
                    {
                        FAIL_FAST_WIN32(lastError);
                    }
                }

                m_kernelbaseDll = std::move(dll);
                m_getCurrentPackageInfo3 = std::move(function);
            }
        }

        bool IsGetCurrentPackageInfo3Supported()
        {
            EnsureGetCurrentPackageInfo3IsIniitalizedIfExists();
            return m_getCurrentPackageInfo3 != nullptr;
        }

    private:
        static wil::unique_hmodule m_dll;
    };
}

wil::unique_hmodule Test::DynamicDependency::GetCurrentPackageInfoTests::m_dll;
