// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "M.K.MR.ManagerRuntimeManager.h"
#include "ManagerRuntimeManager.g.cpp"

namespace winrt::Microsoft::Kozani::ManagerRuntime::implementation
{
    constexpr PCWSTR c_remoteDesktopClientExe = L"mstsc.exe";

    struct KozaniRemoteDesktopClientLauncher : winrt::implements<KozaniRemoteDesktopClientLauncher, IKozaniRemoteDesktopClientLauncher, IUnknown>
    {
        STDMETHODIMP Launch(_In_ PCWSTR connectionRdpFilePath, _In_opt_ PCWSTR /* userName */)
        {
            RETURN_HR_IF_NULL(E_INVALIDARG, connectionRdpFilePath);

            SHELLEXECUTEINFO shellExecuteInfo{};
            shellExecuteInfo.cbSize = sizeof(shellExecuteInfo);
            shellExecuteInfo.fMask = SEE_MASK_NOASYNC;  // Will wait for ShellExecuteEx to finish launching the remote desktop client.
            shellExecuteInfo.lpFile = c_remoteDesktopClientExe;
            shellExecuteInfo.lpParameters = connectionRdpFilePath;
            shellExecuteInfo.nShow = SW_NORMAL;

            RETURN_IF_WIN32_BOOL_FALSE_MSG(ShellExecuteEx(&shellExecuteInfo), "ShellExecuteEx failed to launch %ls", c_remoteDesktopClientExe);
            return S_OK;
        }
    };

    ManagerRuntimeManager::ManagerRuntimeManager()
    {
        m_kozaniManager = wil::CoCreateInstance<KozaniManager, IKozaniManager>(CLSCTX_LOCAL_SERVER);
    }

    winrt::Microsoft::Kozani::ManagerRuntime::ManagerRuntimeManager ManagerRuntimeManager::Create()
    {
        return winrt::make<winrt::Microsoft::Kozani::ManagerRuntime::implementation::ManagerRuntimeManager>();
    }

    void ManagerRuntimeManager::ActivateRemoteApplication(
        Windows::ApplicationModel::Activation::ActivationKind activationKind,
        winrt::hstring appUserModelId,
        winrt::hstring connectionRdpFilePath,
        UINT32 associatedLocalProcessId,
        Windows::ApplicationModel::Activation::IActivatedEventArgs args,
        IInspectable statusCallback,
        winrt::hstring additionalSettingsFilePath)
    {
        // The purpose of IKozaniRemoteDesktopClientLauncher is to allow the caller of the IKozaniManager::ActivateRemoteApplication API
        // to launch remote desktop client (RDC) in its process. The COM server hosting the IKozaniManager APIs is a background process, 
        // which may not be able to launch the RDC to desktop foreground. From experiments we've found that if the caller process is a 
        // foregrounddoes process (e.g., just got activated from Start Menu) but does not display a window (process with no UIs), launching
        // RDC from its process will show the RDC in foreground, while launching RDC in the IKozaniManager APIs COM server process will
        // have the RDC window in background with flashing icon on the taskbar.
        auto rdcLauncher{ winrt::make_self<KozaniRemoteDesktopClientLauncher>() };

        winrt::check_hresult(m_kozaniManager->ActivateRemoteApplication(
            static_cast<INT32>(activationKind),
            appUserModelId.c_str(),
            connectionRdpFilePath.c_str(),
            reinterpret_cast<::IKozaniRemoteDesktopClientLauncher*>(winrt::get_abi(rdcLauncher)),
            associatedLocalProcessId,
            args.as<::IInspectable>().get(),
            statusCallback.as<::IKozaniStatusCallback>().get(),
            additionalSettingsFilePath.c_str()));
    }
}
