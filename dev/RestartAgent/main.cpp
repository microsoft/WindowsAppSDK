// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Microsoft::Windows::AppLifecycle;

using namespace AppModel::Identity;

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    // Get the parent process handle id from the command-line.  We assume here
    // that CreateProcess was called in a manner that inherited this handle to 
    // the current process.

    int argc{};
    std::wstring cmdLine{ GetCommandLineW() };
    wil::unique_hlocal_ptr<PWSTR[]> argv{ CommandLineToArgvW(cmdLine.c_str(), &argc) };

    wil::unique_handle parentHandle;
    auto handleArg{ argv[1] };
    parentHandle.reset(reinterpret_cast<HANDLE>(_wtoi64(handleArg)));

    // Determine the exact path of the calling process needing a restart.
    auto callerPath = wil::QueryFullProcessImageNameW<wil::unique_cotaskmem_string>(parentHandle.get(), 0);

    // Terminate the caller.  TerminateProcess is async, so we need to wait for the process to finish terminating.
    THROW_IF_WIN32_BOOL_FALSE(TerminateProcess(parentHandle.get(), 0));
    THROW_LAST_ERROR_IF(!wil::handle_wait(parentHandle.get()));

    auto startOfHandleArg = cmdLine.find(handleArg);
    THROW_HR_IF(E_INVALIDARG, startOfHandleArg == std::wstring::npos);
    startOfHandleArg += wcslen(handleArg);
    std::wstring arguments{ cmdLine.substr(startOfHandleArg) };
    auto newCmdLine = wil::str_printf<wil::unique_cotaskmem_string>(L"\"%s\" %s", callerPath.get(), arguments.c_str());

    SIZE_T attributeListSize{ 0 };
    auto attributeCount{ 1 };
    THROW_HR_IF(E_UNEXPECTED, InitializeProcThreadAttributeList(nullptr, attributeCount, 0, &attributeListSize));
    THROW_LAST_ERROR_IF(GetLastError() != ERROR_INSUFFICIENT_BUFFER);

    wil::unique_process_heap_ptr<_PROC_THREAD_ATTRIBUTE_LIST> attributeList(reinterpret_cast<PPROC_THREAD_ATTRIBUTE_LIST> (HeapAlloc(GetProcessHeap(), 0, attributeListSize)));
    THROW_IF_NULL_ALLOC(attributeList);

    THROW_IF_WIN32_BOOL_FALSE(InitializeProcThreadAttributeList(attributeList.get(), attributeCount, 0, &attributeListSize));
    auto freeAttributeList = wil::scope_exit([&] { DeleteProcThreadAttributeList(attributeList.get()); });

    DWORD policy = PROCESS_CREATION_DESKTOP_APP_BREAKAWAY_OVERRIDE;
    THROW_IF_WIN32_BOOL_FALSE(UpdateProcThreadAttribute(attributeList.get(), 0, PROC_THREAD_ATTRIBUTE_DESKTOP_APP_POLICY, &policy, sizeof(policy), nullptr, nullptr));

    STARTUPINFOEX info{};
    info.StartupInfo.cb = sizeof(info);

    if (IsPackagedProcess())
    {
        // Currently only packaged scenarios require attributes to be applied.
        info.lpAttributeList = attributeList.get();
    }

    wil::unique_process_information processInfo{};
    THROW_IF_WIN32_BOOL_FALSE(CreateProcess(callerPath.get(), newCmdLine.get(), nullptr, nullptr, FALSE, CREATE_SUSPENDED | EXTENDED_STARTUPINFO_PRESENT, nullptr, nullptr,
        &info.StartupInfo, &processInfo));

    // Transfer foreground rights to the new process before resuming it.
    AllowSetForegroundWindow(processInfo.dwProcessId);
    ResumeThread(processInfo.hThread);

    return 0;
}
