#include "pch.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Microsoft::Windows::AppLifecycle;

using namespace AppModel::Identity;

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    init_apartment();

    if (!IsPackagedProcess())
    {
        const UINT32 majorMinorVersion{ 0x00010000 };
        PCWSTR versionTag{ L"experimental1" };
        const PACKAGE_VERSION minVersion{};
        THROW_IF_FAILED(MddBootstrapInitialize(majorMinorVersion, versionTag, minVersion));
    }

    auto inst = AppInstance::GetCurrent();
    ILaunchActivatedEventArgs args = inst.GetActivatedEventArgs().Data().as<ILaunchActivatedEventArgs>();
    std::wstring cmdLine = args.Arguments().c_str();
    wprintf(L"CmdLine: %s\n", cmdLine.c_str());

    auto handleString = cmdLine.substr(cmdLine.find_last_of(L' '));
    wprintf(L"HandleString: %s\n", handleString.c_str());

    auto handleId = _wtoi64(handleString.c_str());
    wil::unique_handle parentHandle;
    parentHandle.reset(reinterpret_cast<HANDLE>(handleId));

    // TODO: TerminateProcess the caller.
    wchar_t callerPath[MAX_PATH];
    DWORD size = _countof(callerPath);
    auto len = QueryFullProcessImageNameW(parentHandle.get(), 0, callerPath, &size);
    FAIL_FAST_IF_MSG(len == 0, "Caller exited before we could get it's image info.");

    wprintf(L"Waiting for caller to exit.\n");
    DWORD status = ::WaitForSingleObjectEx(parentHandle.get(), INFINITE, FALSE);
    switch (status)
    {
    case WAIT_OBJECT_0:
        wprintf(L"Caller exited!");
        break;
    case WAIT_TIMEOUT:
        wprintf(L"WAIT_TIMEOUT\n");
        break;
    case WAIT_ABANDONED:
        wprintf(L"WAIT_ABANDONED\n");
        break;
    case WAIT_FAILED:
        wprintf(L"WAIT_FAILED %d\n", GetLastError());
        break;
    default:
        wprintf(L"Default %d\n", status);
        break;
    }
    
    wprintf(L"Executing caller: %s\n", callerPath);

    PROCESS_INFORMATION processInfo{};
    STARTUPINFO info{};
    info.cb = sizeof(info);
    THROW_IF_WIN32_BOOL_FALSE(CreateProcess(nullptr, callerPath, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &info, &processInfo));

    Sleep(4000);

    if (!IsPackagedProcess())
    {
        MddBootstrapShutdown();
    }
}
