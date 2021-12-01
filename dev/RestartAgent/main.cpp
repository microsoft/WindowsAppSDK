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
    wchar_t callerPath[MAX_PATH];
    DWORD size = _countof(callerPath);
    auto len = QueryFullProcessImageNameW(parentHandle.get(), 0, callerPath, &size);
    THROW_HR_IF_MSG(E_UNEXPECTED, len == 0, "Caller exited before we could get it's image info.");

    // Terminate the caller.  TerminateProcess is async, so we need to wait for the process to finish terminating.
    THROW_IF_WIN32_BOOL_FALSE(TerminateProcess(parentHandle.get(), 0));
    THROW_LAST_ERROR_IF(!wil::handle_wait(parentHandle.get()));

    auto startOfHandleArg = cmdLine.find(handleArg);
    THROW_HR_IF(E_INVALIDARG, startOfHandleArg == std::wstring::npos);
    startOfHandleArg += wcslen(handleArg);
    std::wstring arguments{ cmdLine.substr(startOfHandleArg) };
    auto newCmdLine = wil::str_printf<wil::unique_cotaskmem_string>(L"\"%s\" %s", callerPath, arguments.c_str());

    PROCESS_INFORMATION processInfo{};
    STARTUPINFO info{};
    info.cb = sizeof(info);
    THROW_IF_WIN32_BOOL_FALSE(CreateProcess(callerPath, newCmdLine.get(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &info, &processInfo));
    return 0;
}
