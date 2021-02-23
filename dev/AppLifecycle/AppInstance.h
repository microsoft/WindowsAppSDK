// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <AppInstance.g.h>
#include "shared_memory.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct AppInstanceList
    {
        unsigned long count = 0;
    };

    struct AppInstanceData
    {
        DWORD processId = 0;
        BYTE stream[1024];
    };

    struct AppInstance : AppInstanceT<AppInstance>
    {
        // No interface public methods.
        AppInstance() = default;
        AppInstance(winrt::hstring key);
        void Activate();

        // IAppInstanceStatics.
        static Microsoft::ProjectReunion::AppInstance GetCurrent()
        {
            return nullptr;
        }

        static Windows::Foundation::Collections::IVector<Microsoft::ProjectReunion::AppInstance> GetInstances();
        static Microsoft::ProjectReunion::AppInstance FindOrRegisterForKey(hstring const& key);

        // IAppInstance.
        void UnregisterKey(hstring const& key);
        void RedirectTo(Microsoft::ProjectReunion::ActivationArguments const& args);
        ActivationArguments GetActivatedEventArgs();
        winrt::event_token Activated(Windows::Foundation::EventHandler<Microsoft::ProjectReunion::ActivationArguments> const& handler);
        void Activated(winrt::event_token const& token) noexcept;
        

        hstring Key() { return m_key.c_str(); }
        bool IsCurrent() { return m_isCurrent; }

    private:
        void MarshalArguments(Microsoft::ProjectReunion::ActivationArguments const& args);
        Microsoft::ProjectReunion::ActivationArguments UnmarshalArguments();

        static INIT_ONCE s_initArgs;
        static winrt::com_ptr<Microsoft::ProjectReunion::IActivationArguments> s_args;

        winrt::event<Windows::Foundation::EventHandler<ActivationArguments>> m_activatedEvent;

        bool m_isCurrent;
        std::wstring m_key;
        wil::unique_mutex m_mutex;
        wil::unique_event m_innerActivated;
        wil::unique_event_watcher m_activationWatcher;
        shared_memory<AppInstanceData> m_shared;
        shared_memory<AppInstanceList> m_instanceList;
    };
}

namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct AppInstance : AppInstanceT<AppInstance, implementation::AppInstance>
    {
    };
}
