// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;

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

template<typename TProvider> void TraceFailureFromProvider(const wil::FailureInfo& failure) WI_NOEXCEPT
{
    TraceLoggingWrite(
        TProvider::Provider(),
        "Failure",
        TraceLoggingHResult(failure.hr, "HResult"),
        TraceLoggingString(failure.pszFile, "File"),
        TraceLoggingUInt32(failure.uLineNumber, "LineNumber"),
        TraceLoggingString(failure.pszFunction, "Function"),
        TraceLoggingWideString(failure.pszMessage, "Message"),
        TraceLoggingString(failure.pszCallContext, "CallingContext"),
        TraceLoggingString(failure.pszModule, "Module"),
        TraceLoggingPointer(failure.returnAddress, "Site"),
        TraceLoggingString(failure.pszCode, "Code"));
}


int APIENTRY wWinMain(
    HINSTANCE /*hInstance*/,
    HINSTANCE /*hPrevInstance*/,
    PWSTR /*pCmdLine*/,
    int /*nCmdShow*/) try
{
    wil::SetResultLoggingCallback(&TraceFailureFromProvider<Microsoft_Kozani_HostRuntime_TraceLogger>);
    winrt::init_apartment();

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
