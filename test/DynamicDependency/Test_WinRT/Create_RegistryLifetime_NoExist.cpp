// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <MsixDynamicDependency.h>

#include <Math.Add.h>
#include <Math.Multiply.h>

#include "Test_WinRT.h"

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

void Test::DynamicDependency::Test_WinRT::Create_RegistryLifetime_NoExist()
{
    // Setup our dynamic dependencies

    winrt::hstring expectedPackageFullName_WindowsAppRuntimeFramework{ TP::WindowsAppRuntimeFramework::c_PackageFullName };
    winrt::hstring expectedPackageFullName_FrameworkMathAdd{ TP::FrameworkMathAdd::c_PackageFullName };

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    auto pathEnvironmentVariable{ GetPathEnvironmentVariableMinusWindowsAppRuntimeFramework() };
    auto packagePath_WindowsAppRuntimeFramework{ TP::GetPackagePath(expectedPackageFullName_WindowsAppRuntimeFramework) };
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());

    // -- Create

    std::wstring lifetimeArtifactRegistryKey{ L"HKCU\\SOFTWARE\\TestWindowsAppRuntime-DynamicDependency" };
    Registry_DeleteKey(lifetimeArtifactRegistryKey);

    try
    {
        const auto lifetimeKind{ winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::RegistryKey };
        auto packageDependency_FrameworkMathAdd{ _Create_FrameworkMathAdd(HRESULT_FROM_WIN32(ERROR_CONTEXT_EXPIRED), lifetimeKind, lifetimeArtifactRegistryKey.c_str()) };
        auto message{ wil::str_printf<wil::unique_process_heap_string>(L"Expected exception (value=0x%X ERROR_CONTEXT_EXPIRED) didn't occur", HRESULT_FROM_WIN32(ERROR_CONTEXT_EXPIRED)) };
        VERIFY_FAIL(message.get());
    }
    catch (const winrt::hresult_error& e)
    {
        constexpr int32_t expectedHR{ HRESULT_FROM_WIN32(ERROR_CONTEXT_EXPIRED) };
        VERIFY_ARE_EQUAL(expectedHR, e.code().value, e.message().c_str());
    }

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
}
