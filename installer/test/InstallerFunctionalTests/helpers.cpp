// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "constants.h"
#include "helpers.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::System;

namespace WindowsAppRuntimeInstallerTests
{
    wil::unique_handle Execute(const std::wstring& command, const std::wstring& args)
    {
        SHELLEXECUTEINFO ei{};
        ei.cbSize = sizeof(SHELLEXECUTEINFO);
        ei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
        ei.lpFile = command.c_str();
        ei.lpParameters = args.c_str();

        if (!ShellExecuteEx(&ei))
        {
            auto lastError{ GetLastError() };
            VERIFY_ARE_EQUAL(S_OK, HRESULT_FROM_WIN32(lastError));
        }

        wil::unique_handle process{ ei.hProcess };
        return process;
    }

    HRESULT RunInstaller(const std::wstring& args)
    {
        const std::wstring installerPath{ GetInstallerPath().c_str() };
        Log::Comment(WEX::Common::String().Format(L"Running installer at: %ws", installerPath.c_str()));
        Log::Comment(WEX::Common::String().Format(L"Arguments: %ws", args.c_str()));
        auto process{ Execute(installerPath, args) };

        auto waitResult{ WaitForSingleObject(process.get(), c_phaseTimeout) };
        if (waitResult != WAIT_OBJECT_0)
        {
            auto lastError{ GetLastError() };
            VERIFY_ARE_NOT_EQUAL(S_OK, HRESULT_FROM_WIN32(lastError));
        }

        DWORD exitCode{};
        THROW_IF_WIN32_BOOL_FALSE(GetExitCodeProcess(process.get(), &exitCode));
        Log::Comment(WEX::Common::String().Format(L"Installer exit code: 0x%0X", HRESULT_FROM_WIN32(exitCode)));
        return HRESULT_FROM_WIN32(exitCode);
    }

    void RemovePackage(const std::wstring& packageName, bool ignoreFailures)
    {
        Log::Comment(WEX::Common::String().Format(L"Removing package: %ws", packageName.c_str()));
        PackageManager manager;
        auto result{ manager.RemovePackageAsync(packageName).get() };
        Log::Comment(WEX::Common::String().Format(L"Removal result: 0x%0X", result.ExtendedErrorCode().value));
        if (!ignoreFailures)
        {
            winrt::check_hresult(result.ExtendedErrorCode());
        }
    }

    // Removing provisioned packages requires the test to run elevated with a user that is an administrator.
    // This is best-effort at cleanup, though the program is idempotent and should succeed regardless of existing
    // provisioning state in situations where it is not run elevated.
    void TryRemoveProvisionedPackage(const std::wstring& packageFamilyName)
    {
        Log::Comment(WEX::Common::String().Format(L"Trying to remove provisioned package: %ws", packageFamilyName.c_str()));
        PackageManager manager;
        auto result{ manager.DeprovisionPackageForAllUsersAsync(packageFamilyName).get() };
        Log::Comment(WEX::Common::String().Format(L"Provision removal result: 0x%0X", result.ExtendedErrorCode().value));
    }

    void RemoveAllPackages(bool ignoreFailures)
    {
        for (const auto& packageName : c_packages)
        {
            RemovePackage(packageName, ignoreFailures);
        }

        for (const auto& packageFamilyName : c_mainPackageFamilies)
        {
            TryRemoveProvisionedPackage(packageFamilyName);
        }
    }

    bool IsPackageRegistered(const std::wstring& packageFullName)
    {
        PackageManager manager;
        auto result{ manager.FindPackageForUser(L"", packageFullName) };
        Log::Comment(WEX::Common::String().Format(L"Package %ws is %wsregistered", packageFullName.c_str(), result?L"":L"not "));
        return result != nullptr;
    }

    ProcessorArchitecture GetSystemArchitecture()
    {
        USHORT processMachine{ IMAGE_FILE_MACHINE_UNKNOWN };
        USHORT nativeMachine{ IMAGE_FILE_MACHINE_UNKNOWN };
        THROW_IF_WIN32_BOOL_FALSE(::IsWow64Process2(::GetCurrentProcess(), &processMachine, &nativeMachine));
        switch (nativeMachine)
        {
        case IMAGE_FILE_MACHINE_I386:
            return ProcessorArchitecture::X86;
        case IMAGE_FILE_MACHINE_AMD64:
            return ProcessorArchitecture::X64;
        case IMAGE_FILE_MACHINE_ARM64:
            return ProcessorArchitecture::Arm64;
        default:
            THROW_HR_MSG(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), "nativeMachine=%hu", nativeMachine);
        }
    }

    std::filesystem::path GetModulePath(HMODULE hmodule)
    {
        if (hmodule == NULL)
        {
            hmodule = GetModuleHandle(L"InstallerFunctionalTests.dll");
        }
        auto path{ GetModuleFileName(hmodule) };
        return path.remove_filename();
    }

    std::filesystem::path GetModuleFileName(HMODULE hmodule)
    {
        auto moduleFileName{ wil::GetModuleFileNameW(hmodule) };
        return std::filesystem::path(moduleFileName.get());
    }

    std::filesystem::path GetCommonRootPath()
    {
        auto path = GetModulePath();

        // TAEF runs as a package under the installer, so we have to go way up the parent root in order to
        // get to the common project root and then get to the build output.
        return path.parent_path().parent_path();
    }

    std::filesystem::path GetInstallerPath()
    {
        auto path{ GetCommonRootPath() };
        return path /= INSTALLER_EXE_PATH;
    }
}
