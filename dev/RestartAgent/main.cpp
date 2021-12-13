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

    wil::unique_process_information processInfo{};
    STARTUPINFO info{};
    info.cb = sizeof(info);
    THROW_IF_WIN32_BOOL_FALSE(CreateProcess(callerPath.get(), newCmdLine.get(), nullptr, nullptr, FALSE, CREATE_SUSPENDED, nullptr, nullptr, &info, &processInfo));

    // Transfer foreground rights to the new process before resuming it.
    AllowSetForegroundWindow(processInfo.dwProcessId);
    ResumeThread(processInfo.hThread);

    return 0;
}
