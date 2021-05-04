#include "pch.h"
#include "constants.h"
#include "helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::System;

namespace ProjectReunionInstallerTests
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
            auto lastError = GetLastError();
            Assert::AreEqual(S_OK, HRESULT_FROM_WIN32(lastError));
        }

        wil::unique_handle process{ ei.hProcess };
        return process;
    }

    HRESULT RunInstaller(const std::wstring& args)
    {
        std::wostringstream sstr;
        sstr << L"Running installer at: " << INSTALLER_EXE_PATH << std::endl;
        sstr << L"Arguments: " << args << std::endl;
        Logger::WriteMessage(sstr.str().c_str());

        auto process = Execute(INSTALLER_EXE_PATH, args);

        auto waitResult = WaitForSingleObject(process.get(), c_phaseTimeout);
        if (waitResult != WAIT_OBJECT_0)
        {
            auto lastError = GetLastError();
            Assert::AreNotEqual(S_OK, HRESULT_FROM_WIN32(lastError));
        }

        DWORD exitCode{};
        THROW_IF_WIN32_BOOL_FALSE(GetExitCodeProcess(process.get(), &exitCode));
        return HRESULT_FROM_WIN32(exitCode);
    }

    void RemovePackage(const std::wstring& packageName, bool ignoreFailures)
    {
        std::wostringstream sstr;
        sstr << L"Removing package: " << packageName << std::endl;
        Logger::WriteMessage(sstr.str().c_str());

        PackageManager manager;
        auto result = manager.RemovePackageAsync(packageName).get();
        auto errorCode = result.ExtendedErrorCode();
        if (!ignoreFailures)
        {
            winrt::check_hresult(errorCode);
        }
    }

    void RemoveAllPackages(bool ignoreFailures)
    {
        for (const auto& packageName : c_packages)
        {
            RemovePackage(packageName, ignoreFailures);
        }
    }

    bool IsPackageRegistered(const std::wstring& packageFullName)
    {
        PackageManager manager;
        auto result = manager.FindPackageForUser(L"", packageFullName);

        std::wostringstream sstr;
        sstr << L"Package " << packageFullName << " is ";
        if (!result)
        {
            sstr << L"not ";
        }
        sstr << L"registered." << std::endl;
        Logger::WriteMessage(sstr.str().c_str());

        return result != nullptr;
    }

    ProcessorArchitecture GetSystemArchitecture()
    {
        SYSTEM_INFO systemInfo{};
        GetNativeSystemInfo(&systemInfo);
        return static_cast<ProcessorArchitecture>(systemInfo.wProcessorArchitecture);
    }
}
