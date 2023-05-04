// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <KozaniManager_h.h>
#include "ManagerRuntimeManager.g.h"

namespace winrt::Microsoft::Kozani::ManagerRuntime::implementation
{
    struct ManagerRuntimeManager : ManagerRuntimeManagerT<ManagerRuntimeManager>
    {
        ManagerRuntimeManager();

        static winrt::Microsoft::Kozani::ManagerRuntime::ManagerRuntimeManager Create();

        void ActivateRemoteApplication(
            Windows::ApplicationModel::Activation::ActivationKind activationKind,
            winrt::hstring appUserModelId,
            winrt::hstring connectionRdpFilePath,
            winrt::hstring additionalSettingsFilePath,
            Windows::ApplicationModel::Activation::IActivatedEventArgs args,
            IInspectable statusCallback,
            UINT32 associatedLocalProcessId);

    private:
        wil::com_ptr<IKozaniManager> m_kozaniManager;
    };
}
namespace winrt::Microsoft::Kozani::ManagerRuntime::factory_implementation
{
    struct ManagerRuntimeManager : ManagerRuntimeManagerT<ManagerRuntimeManager, implementation::ManagerRuntimeManager>
    {
    };
}
