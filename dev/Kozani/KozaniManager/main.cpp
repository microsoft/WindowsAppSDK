// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <fstream>
#include <filesystem>

#include "..\KozaniManager\KozaniManager-Constants.h"

#include <KozaniManager_h.h>

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

#include <wrl\module.h>

#include <winrt_WindowsAppRuntime.h>

#include <windows.applicationmodel.activation.h>
#include "KozaniDvc-Constants.h"
#include "ConnectionManager.h"

using namespace Microsoft::WRL;
using namespace Microsoft::Kozani::Manager;

namespace Dvc = Microsoft::Kozani::DVC;

// Implement the LifetimeManager as a classic COM Out-of-Proc server, via WRL
// See https://docs.microsoft.com/cpp/cppcx/wrl/how-to-create-a-classic-com-component-using-wrl?redirectedfrom=MSDN&view=vs-2019 for more details

static constexpr GUID KozaniManager_guid { PR_KOZANIMANAGER_CLSID_GUID };

Microsoft::Kozani::Manager::ConnectionManager g_connectionManager;

// Accumulated number of connections to remote server. Used to keep track of whether a new connection is made between remote desktop client is
// launched and connection wait time out.
volatile LONG g_newConnectionCount{};

static std::string GetConnectionId(PCWSTR connectionRdpFilePath)
{
    std::fstream rdpFile;

    // Set exception behavior - will throw exception if the file stream operation hits error. Will NOT throw if read has reached end-of-file
    rdpFile.exceptions(std::fstream::failbit | std::fstream::badbit);

    try
    {
        rdpFile.open(connectionRdpFilePath, std::fstream::in);
    }
    catch (...)
    {
        // Failing to open the file may be caused by non-existing file or file path is a folder instead of a file. Check these 2 conditions and 
        // throw with meaningful error code if it matches either condition.
        THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), !std::filesystem::exists(connectionRdpFilePath), "File %ls does not exist", connectionRdpFilePath);
        THROW_HR_IF_MSG(E_INVALIDARG, !std::filesystem::is_regular_file(connectionRdpFilePath), "File %ls is not a regular file. Maybe it is a folder?", connectionRdpFilePath);
    }

    std::string connectionId;
    bool readNextLine{ true };
    std::string line;
    while (readNextLine)
    {
        std::getline(rdpFile, line);
        size_t switchOffset{ line.find(Dvc::Constants::ConnectionIdSwitch) };
        if (switchOffset != std::string::npos)
        {
            size_t idOffset{ line.find_first_not_of(" \t", switchOffset + ARRAYSIZE(Dvc::Constants::ConnectionIdSwitch) - 1) };
            if (idOffset != std::string::npos)
            {
                while (idOffset < line.length() && !isspace(line[idOffset]))
                {
                    connectionId.push_back(line[idOffset]);
                    idOffset++;
                }
            }
            break;
        }

        readNextLine = !rdpFile.eof();
    }

    return std::move(connectionId);
}

struct __declspec(uuid(PR_KOZANIMANAGER_CLSID_STRING)) KozaniManagerImpl WrlFinal : RuntimeClass<RuntimeClassFlags<ClassicCom>, IKozaniManager>
{
    STDMETHODIMP ActivateRemoteApplication(
        INT32 activationKind,
        _In_ PCWSTR appUserModelId,
        _In_ PCWSTR connectionRdpFilePath,
        _In_ IKozaniRemoteDesktopClientLauncher* rdcLauncher,
        DWORD associatedLocalProcessId,
        _In_opt_::IInspectable* activatedEventArgs,
        _In_opt_ IKozaniStatusCallback* statusCallback,
        _In_opt_ PCWSTR additionalSettingsFilePath) noexcept try
    {
        RETURN_HR_IF_NULL(E_INVALIDARG, appUserModelId);
        RETURN_HR_IF_NULL(E_INVALIDARG, connectionRdpFilePath);
        RETURN_HR_IF_NULL(E_INVALIDARG, rdcLauncher);

        const auto activationKindLocal{ static_cast<winrt::Windows::ApplicationModel::Activation::ActivationKind>(activationKind) };
        RETURN_HR_IF_MSG(KOZANI_E_UNSUPPORTED_ACTIVATION_KIND, 
            !IsActivationKindSupported(activationKindLocal),
            "Activation kind: %d", activationKind);

        winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs args;
        if (activatedEventArgs)
        {
            args = winrt::convert_from_abi<winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs>(activatedEventArgs);
        }

        std::string connectionId{ GetConnectionId(connectionRdpFilePath) };
        RETURN_HR_IF_MSG(E_INVALIDARG, connectionId.empty(), "Invalid connection RDP file - connectionId switch not found or the ID string is empty");

        std::shared_ptr<ActivationRequestStatusReporter> requestStatusReporter{ 
            g_connectionManager.AddNewActivationRequest(connectionId, activationKindLocal, appUserModelId, args, statusCallback, associatedLocalProcessId) };

        // If failure happens after this point, we will automatically cleanup the new request from tracking mechanism.
        auto cleanupRequestOnFailure = wil::scope_exit([&]()
        {
            g_connectionManager.CleanupActivationRequest(requestStatusReporter.get());
        });

        const LONG connectionCountBeforeRDCLaunch{ InterlockedAdd(&g_newConnectionCount, 0) };

        RETURN_IF_FAILED(rdcLauncher->Launch(connectionRdpFilePath, nullptr));

        // Wait for request status change or time out to ensure this module is alive for RDC to load the DVC plugin hosted by the module.
        // If the module is exiting while RDC is loading the DVC plugin, the DVC loading will fail and RDC will ignore the failure and
        // continue without the DVC. MaxDvcPluginLoadingTime gives enough time for DVC loading.
        bool waitSucceeded{ requestStatusReporter->WaitForStatusChange(MaxDvcPluginLoadingTime) };
        if (!waitSucceeded)
        {
            // Wait timed out before request stauts changes. 
            const LONG connectionCountAfterRDCLaunch{ InterlockedAdd(&g_newConnectionCount, 0) };
            if (connectionCountAfterRDCLaunch == connectionCountBeforeRDCLaunch)
            {
                // There are no new connections detected during the wait time (MaxDvcPluginLoadingTime). 
                // RDC must be reusig an existing connection. Continue to wait for acknowledgment of the connection from DVC server side.
                waitSucceeded = requestStatusReporter->WaitForStatusChange(MaxConnectionWaitTime);
            }
            else
            {
                // New connection detected during the wait time. We will return success here as the wait time for a new connection to 
                // finish cannot be determined. The user may take some time to enter the password to login and the login can take time
                // to finish depending on the server's workload. The IKozaniStatusCallback object will be used by the DVC to communicate
                // any issues in this longer process.
                cleanupRequestOnFailure.release();
                return S_OK;
            }
        }
        
        if (waitSucceeded)
        {
            auto status{ requestStatusReporter->GetStatus() };
            if (status == RequestStatus::Failed)
            {
                RETURN_HR(E_APPLICATION_ACTIVATION_EXEC_FAILURE);
            }
        }
        else
        {
            // Wait timed out.
            RETURN_HR(E_APPLICATION_ACTIVATION_TIMED_OUT);
        }

        // No failures before returning - disable the auto cleanup on failure logic.
        cleanupRequestOnFailure.release();
        return S_OK;
    } CATCH_RETURN()

private:
    bool IsActivationKindSupported(winrt::Windows::ApplicationModel::Activation::ActivationKind kind)
    {
        switch (kind)
        {
            case winrt::Windows::ApplicationModel::Activation::ActivationKind::Launch:
                [[fallthrough]];
            case winrt::Windows::ApplicationModel::Activation::ActivationKind::File:
                [[fallthrough]];
            case winrt::Windows::ApplicationModel::Activation::ActivationKind::Protocol:
                return true;
        }

        return false;
    }
};
CoCreatableClass(KozaniManagerImpl);

wil::unique_event g_endOfTheLine;

void EndOfTheLine()
{
    g_endOfTheLine.SetEvent();
}

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    // Hook up wil logging MACROs to trace provider.
    wil::SetResultLoggingCallback(&TraceFailureFromProvider<Microsoft_Kozani_Manager_TraceLogger>);

    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    RETURN_IF_FAILED(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));

    wil::unique_event endOfTheLine(::CreateEventW(nullptr, TRUE, FALSE, nullptr));
    RETURN_LAST_ERROR_IF_NULL(endOfTheLine);
    g_endOfTheLine = std::move(endOfTheLine);

    auto& module = Module<OutOfProc>::Create(EndOfTheLine);
    RETURN_IF_FAILED(module.RegisterObjects());

    g_endOfTheLine.wait();

    // Release any COM related stuffs before calling CoUninitialize().
    g_connectionManager.Close();

    (void)LOG_IF_FAILED(module.UnregisterObjects());
    module.Terminate();

    ::CoUninitialize();

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}

STDAPI_(BOOL) DllMain(_In_opt_ HINSTANCE hinst, DWORD reason, _In_opt_ void* reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinst);
    }

    // Give WIL a crack at DLLMain processing
    // See DLLMain() in wil/result_macros.h for why
    wil::DLLMain(hinst, reason, reserved);

    return TRUE;
}
