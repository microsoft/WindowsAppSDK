// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "..\KozaniManager\KozaniManager-Constants.h"

#include <KozaniManager_h.h>

#include "Microsoft.Kozani.Activation.h"

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

#include <wrl\module.h>

#include <windows.applicationmodel.activation.h>

using namespace Microsoft::WRL;

// Implement the LifetimeManager as a classic COM Out-of-Proc server, via WRL
// See https://docs.microsoft.com/cpp/cppcx/wrl/how-to-create-a-classic-com-component-using-wrl?redirectedfrom=MSDN&view=vs-2019 for more details

static constexpr GUID KozaniManager_guid { PR_KOZANIMANAGER_CLSID_GUID };

struct __declspec(uuid(PR_KOZANIMANAGER_CLSID_STRING)) KozaniManagerImpl WrlFinal : RuntimeClass<RuntimeClassFlags<ClassicCom>, IKozaniManager>
{
    STDMETHODIMP ActivateRemoteApplication(
        INT32 activationKind,
        PCWSTR appUserModelId,
        PCWSTR connectionRdpFilePath,
        PCWSTR additionalSettingsFilePath,
        ::IInspectable* activatedEventArgs,
        IKozaniStatusCallback* statusCallback,
        DWORD associatedLocalProcessId) try
    {
        // Serialize the message
        const std::int64_t cookie{};
        std::string messageBytes{ ::Microsoft::Kozani::Activation::ActivateApp(cookie, appUserModelId, activatedEventArgs) };

        // TODO: https://task.ms/42882034 temporary code to enable initial testing of the in-proc WinRT API and OOP COM API. Will be replaced with real impl later.
        if (statusCallback != nullptr)
        {
            RETURN_IF_FAILED(statusCallback->OnActivated(associatedLocalProcessId));
        }

        return S_OK;
    } CATCH_RETURN();
};
CoCreatableClass(KozaniManagerImpl);

wil::unique_event g_endOfTheLine;

void EndOfTheLine()
{
    g_endOfTheLine.SetEvent();
}

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
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
