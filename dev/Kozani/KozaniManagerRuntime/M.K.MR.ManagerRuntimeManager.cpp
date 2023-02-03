// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "M.K.MR.ManagerRuntimeManager.h"

#include "ManagerRuntimeManager.g.cpp"

namespace winrt::Microsoft::Kozani::ManagerRuntime::implementation
{
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
        winrt::hstring additionalSettingsFilePath,
        Windows::ApplicationModel::Activation::IActivatedEventArgs args,
        IInspectable statusCallback)
    {
        winrt::check_hresult(m_kozaniManager->ActivateRemoteApplication(
            static_cast<INT32>(activationKind),
            appUserModelId.c_str(),
            connectionRdpFilePath.c_str(),
            additionalSettingsFilePath.c_str(),
            reinterpret_cast<::IInspectable*>(winrt::get_abi(args)),
            reinterpret_cast<::IKozaniStatusCallback*>(winrt::get_abi(statusCallback)),
            GetCurrentProcessId()));
    }
}
