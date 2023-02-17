// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <fstream> 

#include "..\KozaniManager\KozaniManager-Constants.h"

#include <KozaniManager_h.h>

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

#include <wrl\module.h>

#include <windows.applicationmodel.activation.h>

using namespace Microsoft::WRL;

namespace Microsoft::Kozani::Manager
{
    const UINT32 MaxConnectionRdpFileSize = 64 * 1024;
}

namespace KM = Microsoft::Kozani::Manager;

// Implement the LifetimeManager as a classic COM Out-of-Proc server, via WRL
// See https://docs.microsoft.com/cpp/cppcx/wrl/how-to-create-a-classic-com-component-using-wrl?redirectedfrom=MSDN&view=vs-2019 for more details

static constexpr GUID KozaniManager_guid { PR_KOZANIMANAGER_CLSID_GUID };

static std::string GetConnectionId(PCWSTR connectionRdpFilePath)
{
    std::fstream ff(connectionRdpFilePath, std::fstream::in);
    //ff.getline()
    //ff.failbit
    //ff.rdstate() 
    
    //rdpFile.
    //std::fstream
    std::string line;
    if (!std::getline(ff, line))
    {
        std::istream ii();
        if (!ii)
        {

        }
    }


    wil::unique_hfile rdpFile{ ::CreateFileW(connectionRdpFilePath, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr) };
    if (!rdpFile)
    {
        THROW_LAST_ERROR_MSG("Failed to open connection RDP file: %ls", connectionRdpFilePath);
    }

    LARGE_INTEGER fileSize{};
    THROW_IF_WIN32_BOOL_FALSE(GetFileSizeEx(rdpFile.get(), &fileSize));
    THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_FILE_TOO_LARGE), (fileSize.QuadPart > KM::MaxConnectionRdpFileSize), 
        "Unsupported: Connection RDP file too large. File path: %ls, file size: %I64u, max supported size: %u", 
        connectionRdpFilePath, fileSize.QuadPart, KM::MaxConnectionRdpFileSize);

    //std::filebuf dd;
    //dd
    return "";
}

struct __declspec(uuid(PR_KOZANIMANAGER_CLSID_STRING)) KozaniManagerImpl WrlFinal : RuntimeClass<RuntimeClassFlags<ClassicCom>, IKozaniManager>
{
    STDMETHODIMP ActivateRemoteApplication(
        INT32 activationKind,
        PCWSTR appUserModelId,
        PCWSTR connectionRdpFilePath,
        PCWSTR additionalSettingsFilePath,
        ::IInspectable* activatedEventArgs,
        IKozaniStatusCallback* statusCallback,
        DWORD associatedLocalProcessId) noexcept try
    {
        
        if (statusCallback != nullptr)
        {
            RETURN_IF_FAILED(statusCallback->OnActivated(associatedLocalProcessId));
        }

        return S_OK;
    }
    CATCH_RETURN()
};
CoCreatableClass(KozaniManagerImpl);

wil::unique_event g_endOfTheLine;

void EndOfTheLine()
{
    g_endOfTheLine.SetEvent();
}

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
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
