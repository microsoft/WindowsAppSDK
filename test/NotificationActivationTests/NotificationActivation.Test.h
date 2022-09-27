// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

namespace NotificationActivation::TestFunctions
{
    wil::unique_event CreateTestEvent(const std::wstring& eventName)
    {
        bool alreadyExists = false;
        SECURITY_ATTRIBUTES attributes = {};
        wil::unique_hlocal_security_descriptor descriptor;

        // Allow app containers to signal the TAEF test event
        THROW_IF_WIN32_BOOL_FALSE(ConvertStringSecurityDescriptorToSecurityDescriptor(
            L"D:(A;;GA;;;WD)(A;;GA;;;AC)", SDDL_REVISION_1, &descriptor, nullptr));
        attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
        attributes.lpSecurityDescriptor = descriptor.get();

        wil::unique_event event;
        event.create(wil::EventOptions::None, eventName.c_str(), &attributes, &alreadyExists);
        return event;
    }

    void WaitForEvent(const wil::unique_event& successEvent, const wil::unique_event& failedEvent)
    {
        HANDLE waitEvents[2]{ successEvent.get(), failedEvent.get() };
        auto waitResult{ WaitForMultipleObjects(_countof(waitEvents), waitEvents, FALSE,
            c_phaseTimeout) };

        // If waitResult == failureEventIndex, it means the remote test process signaled a
        // failure event while we were waiting for a different event.
        auto failureEventIndex{ WAIT_OBJECT_0 + 1 };
        VERIFY_ARE_NOT_EQUAL(waitResult, failureEventIndex);

        VERIFY_ARE_NOT_EQUAL(waitResult, static_cast<DWORD>(WAIT_TIMEOUT));
        if (waitResult == WAIT_FAILED)
        {
            VERIFY_WIN32_FAILED(GetLastError());
        }

        successEvent.ResetEvent();
        failedEvent.ResetEvent();
    }

    void RunTest(const PCWSTR& testName, const int& waitTime)
    {
        DWORD processId{};
        winrt::com_ptr<IApplicationActivationManager> testAppLauncher{ winrt::try_create_instance<IApplicationActivationManager>(CLSID_ApplicationActivationManager, CLSCTX_ALL) };
        VERIFY_SUCCEEDED(testAppLauncher->ActivateApplication(L"NotificationActivationPackage_8wekyb3d8bbwe!App", testName, AO_NONE, &processId));

        wil::unique_process_handle processHandle;
        processHandle.reset(OpenProcess(SYNCHRONIZE | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId));
        VERIFY_IS_TRUE(processHandle.is_valid());

        VERIFY_IS_TRUE(wil::handle_wait(processHandle.get(), waitTime));

        DWORD exitCode{};
        VERIFY_WIN32_BOOL_SUCCEEDED(GetExitCodeProcess(processHandle.get(), &exitCode));
        VERIFY_ARE_EQUAL(exitCode, 0u);
    }

    wil::unique_handle RunUnpackaged(const std::wstring& command, const std::wstring& args, const std::wstring& directory)
    {
        SHELLEXECUTEINFO ei{};
        ei.cbSize = sizeof(SHELLEXECUTEINFO);
        ei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
        ei.lpFile = command.c_str();
        ei.lpParameters = args.c_str();
        ei.lpDirectory = directory.c_str();
        ei.nShow = SW_NORMAL;

        if (!ShellExecuteEx(&ei))
        {
            auto lastError = GetLastError();
            VERIFY_WIN32_SUCCEEDED(lastError);
        }

        wil::unique_handle process{ ei.hProcess };
        return process;
    }

    const std::wstring GetDeploymentDir()
    {
        WEX::Common::String deploymentDir;
        WEX::TestExecution::RuntimeParameters::TryGetValue(L"TestDeploymentDir", deploymentDir);
        return reinterpret_cast<PCWSTR>(deploymentDir.GetBuffer());
    }
}
