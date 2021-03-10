// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <DynamicDependencyDataStore_h.h>

// Temporarily disable C4324 because WRL generates a false (well, irrelevant) warning
//   'Microsoft::WRL::Details::StaticStorage<Microsoft::WRL::Details::OutOfProcModuleBase<ModuleT>::GenericReleaseNotifier<T>,Microsoft::WRL::Details::StorageInstance::OutOfProcCallbackBuffer1,ModuleT>': structure was padded due to alignment specifier
#pragma warning(push)
#pragma warning(disable:4324)
#include <wrl.h>
#pragma warning(pop)

using namespace Microsoft::WRL;

// Implement the DataStore as a classic COM Out-of-Proc server, via WRL
// See https://docs.microsoft.com/en-us/cpp/cppcx/wrl/how-to-create-a-classic-com-component-using-wrl?redirectedfrom=MSDN&view=vs-2019 for more details

struct __declspec(uuid("D1AD16C7-EC59-4765-BF95-9A243EB00507")) DynamicDependencyDataStoreImpl WrlFinal : RuntimeClass<RuntimeClassFlags<ClassicCom>, IDynamicDependencyDataStore>
{
    STDMETHODIMP GetApplicationData(/*[out, retval]*/ IUnknown** applicationData)
    {
        *applicationData = nullptr;

        auto appData = winrt::Windows::Storage::ApplicationData::Current();
        auto appDataIUnkown = winrt::get_unknown(appData);
        winrt::copy_to_abi(appDataIUnkown, *applicationData);
        return S_OK;
    }

    STDMETHODIMP GetPackageFullName(/*[out, retval]*/ PWSTR* packageFullName)
    {
        *packageFullName = nullptr;

        WCHAR fullName[PACKAGE_FULL_NAME_MAX_LENGTH + 1]{};
        UINT32 fullNameLength = ARRAYSIZE(fullName);
        RETURN_IF_FAILED(GetCurrentPackageFullName(&fullNameLength, fullName));
        auto fullNameCoTaskMem = wil::make_cotaskmem_string_nothrow(fullName);
        RETURN_IF_NULL_ALLOC(fullNameCoTaskMem);

        *packageFullName = fullNameCoTaskMem.release();
        return S_OK;
    }
};
CoCreatableClass(DynamicDependencyDataStoreImpl);

wil::unique_event g_endOfTheLine;

void EndOfTheLine()
{
    g_endOfTheLine.SetEvent();
}

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    ::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);

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

STDAPI_(BOOL) DllMain(_In_opt_ HINSTANCE hinst, DWORD reason, _In_opt_ void*)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinst);
    }
    return TRUE;
}
