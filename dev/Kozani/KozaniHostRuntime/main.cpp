// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

#include <KozaniManager_h.h>
#include "winrt/Microsoft.Kozani.ManagerRuntime.h"

#include "Logging.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;

enum KozaniStatus
{
    None = 0,
    Activated = 1,
    Failed = 2,
    Closed = 3
};

struct KozaniStatusCallbackHandler : winrt::implements<KozaniStatusCallbackHandler, IKozaniStatusCallback, winrt::Windows::Foundation::IInspectable>
{
    KozaniStatusCallbackHandler(std::wstring& aumid, DWORD localProcessId) :
        m_aumid(aumid),
        m_localProcessId(localProcessId)
    {
        m_eventStatusUpdate.create();
    }

#pragma region IKozaniStatusCallback_methods
    STDMETHODIMP OnActivated(DWORD pid, boolean isNewInstance)
    {
        LOG_HR_MSG(KOZANI_E_INFO, "[ActivationSuccess] IKozaniStausCallback::OnActivated is called. Remote app aumid = %s, pid = %u, isNewInstance = %s",
            m_aumid.c_str(), pid, isNewInstance ? "true" : "false");

        m_remoteAppProcessId = pid;
        m_status = KozaniStatus::Activated;
        m_eventStatusUpdate.SetEvent();
        return S_OK;
    }

    STDMETHODIMP OnActivationFailed(
        DWORD errorCode,
        PCWSTR errorMessage)
    {
        LOG_HR_MSG(KOZANI_E_INFO, "[ActivationFailed] IKozaniStausCallback::OnActivationFailed is called. Remote app aumid = %s, errorCode = 0x%x, errorMessage: %s",
                m_aumid.c_str(), errorCode, errorMessage);

        m_status = KozaniStatus::Failed;
        m_eventStatusUpdate.SetEvent();
        return S_OK;
    }

    STDMETHODIMP OnClosed()
    {
        LOG_HR_MSG(KOZANI_E_INFO, "[App Terminated] IKozaniStausCallback::OnClosed is called. Remote app aumid = %s, pid=%u",
                m_aumid.c_str(), m_remoteAppProcessId);

        m_status = KozaniStatus::Closed;
        m_eventStatusUpdate.SetEvent();
        return S_OK;
    }
#pragma endregion IKozaniStatusCallback_methods

    bool WaitForStatusUpdate(DWORD timeout)
    {
        return m_eventStatusUpdate.wait(timeout);
    }

    KozaniStatus GetStatus()
    {
        return m_status;
    }

private:
    std::wstring m_aumid;
    DWORD m_localProcessId{};
    DWORD m_remoteAppProcessId{};
    KozaniStatus m_status{};
    wil::unique_event m_eventStatusUpdate;
};

void LogArgs(int argc, PWSTR* argv)
{
    TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "argc",
        TraceLoggingValue(argc, "argc"));
    for (int i = 0; i < argc; i++)
    {
        TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "argv",
            TraceLoggingValue(i, "index"),
            TraceLoggingValue(argv[i], "argv"));
    }
}


/*
// Read data from a file.
IAsyncAction MainPage::ReadTimestampAsync()
{
    StorageFile file{ co_await m_localFolder.GetFileAsync(L"dataFile.txt") };

    try
    {
        winrt::hstring timestamp{ co_await Windows::Storage::FileIO::ReadTextAsync(file) };
    }
    catch (winrt::hresult_error const& ex)
    {
        // Timestamp not read.
    }
}

*/

// if co-awating, need to return iasyncaction.
//winrt::Windows::Foundation::IAsyncAction GetConfigurationFiles()
void GetConfigurationFiles()
{
    auto pp = Package::Current();

    StorageFolder localFolder{ ApplicationData::Current().LocalFolder() };
    // This hostRuntime exe should run with the identity of the hosted app (localvariant) package that activated
    // Logging the AppData local folder path thus indicates the identity of the hosted app.
    TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "localFolder",
        TraceLoggingValue(localFolder.Path().c_str(), "path"));

    if (IStorageItem const& connectionRdp = localFolder.TryGetItemAsync(L"connection.rdp").get())
    {
        if (connectionRdp.IsOfType(StorageItemTypes::File))
        {
            TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "connectionRdpFound",
                TraceLoggingValue(connectionRdp.Path().c_str(), "file"));
        }
    }
    else
    {
        for (IStorageItem const& item : localFolder.GetItemsAsync().get())
        {
            if (item.IsOfType(StorageItemTypes::File))
            {
                TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "contents",
                    TraceLoggingValue(item.Name().c_str(), "file"));

                if (item.Name().ends_with(L".rdp"))
                {
                    TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "rdpfound",
                        TraceLoggingValue(item.Path().c_str(), "file"));
                }
            }
        }
    }

}

void GetActivationType()
{
    if (const auto args = AppInstance::GetActivatedEventArgs())
    {
        auto kind = args.Kind();
        switch (kind)
        {
        case ActivationKind::Launch:
            TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "launch kind");
            break;
        case ActivationKind::File:
            TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "file kind");
            break;
        case ActivationKind::Protocol:
            TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "protocol kind");
            break;
            // add more case ActivationKind::
        default:
            TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "Unhandled ActivationKind",
                TraceLoggingValue((UINT32)kind, "ActivationKind"));
        }
    }
}

int APIENTRY wWinMain(
    HINSTANCE /*hInstance*/,
    HINSTANCE /*hPrevInstance*/,
    PWSTR /*pCmdLine*/,
    int /*nCmdShow*/) try
{
    wil::SetResultLoggingCallback(&TraceFailureFromProvider<Microsoft_Kozani_HostRuntime_TraceLogger>);
    winrt::init_apartment();

    LOG_HR_MSG(KOZANI_E_INFO, "Test tracing!");

    //const auto yesno{ MessageBoxW(nullptr, L"Hello", L"message", MB_OK | MB_ICONINFORMATION)};

    //Sleep(5000);

    /*
    SHELLEXECUTEINFO shellExecuteInfo{};
    shellExecuteInfo.cbSize = sizeof(shellExecuteInfo);
    shellExecuteInfo.fMask = SEE_MASK_NOASYNC;  // Will wait for ShellExecuteEx to finish launching the remote desktop client.
    shellExecuteInfo.lpFile = L"mstsc.exe";
    shellExecuteInfo.lpParameters = L"D:\\temp\\3\\connection.rdp";
    shellExecuteInfo.nShow = SW_NORMAL;

    ShellExecuteEx(&shellExecuteInfo);
    */

//    ShellExecute(nullptr, nullptr, L"mstsc.exe", L"D:\\temp\\3\\connection.rdp", nullptr, SW_SHOWNORMAL);

    auto runtimeManager{ winrt::Microsoft::Kozani::ManagerRuntime::ManagerRuntimeManager::Create() };

    std::wstring aumid{ L"MyAumid!App" };
    auto statusCallback{ winrt::make_self<KozaniStatusCallbackHandler>(aumid, 0) };


    try
    {
        runtimeManager.ActivateRemoteApplication(
            winrt::Windows::ApplicationModel::Activation::ActivationKind::Launch,
            aumid.c_str(), L"D:\\temp\\3\\connection.rdp", winrt::param::hstring(),
            nullptr,    // IActivatedEventArgs
            statusCallback.as<winrt::Windows::Foundation::IInspectable>(),
            0);
    }
    catch (winrt::hresult_error& e)
    {
        THROW_HR_MSG(
            e.code(),
            "\nActivateRemoteApplication failed. errorCode = 0x%x, errorMessage: %ls",
            e.code(),
            e.message().c_str());
    }

    

    int argc{};
    const wil::unique_hlocal_ptr<PWSTR[]> argv{ CommandLineToArgvW(GetCommandLineW(), &argc) };
    LogArgs(argc, argv.get());
    //GetConfigurationFiles().get();
    GetConfigurationFiles();
    GetActivationType();

    TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "Exiting instance");
    return S_OK;
}
CATCH_RETURN()
