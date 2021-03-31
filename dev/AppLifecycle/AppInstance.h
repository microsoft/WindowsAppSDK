// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <Microsoft.Windows.AppLifecycle.AppInstance.g.h>
#include "shared_memory.h"
#include "InstanceList.h"

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    struct AppInstance : AppInstanceT<AppInstance>
    {
        // No interface public methods.
        AppInstance(uint32_t processId);
        void Activate();

        // IAppInstanceStatics.
        static Microsoft::Windows::AppLifecycle::AppInstance GetCurrent();
        static winrt::Windows::Foundation::Collections::IVector<Microsoft::Windows::AppLifecycle::AppInstance> GetInstances();
        static Microsoft::Windows::AppLifecycle::AppInstance FindOrRegisterForKey(hstring const& key);

        // IAppInstance.
        void UnregisterKey(hstring const& key);
        void RedirectTo(Microsoft::Windows::AppLifecycle::ActivationArguments const& args);
        ActivationArguments GetActivatedEventArgs();
        winrt::event_token Activated(winrt::Windows::Foundation::EventHandler<Microsoft::Windows::AppLifecycle::ActivationArguments> const& handler);
        void Activated(winrt::event_token const& token) noexcept;
        
        hstring Key() { return winrt::hstring(m_key); }
        bool IsCurrent() { return m_isCurrent; }

    private:
        bool TrySetKey(std::wstring const& key);
        Microsoft::Windows::AppLifecycle::AppInstance FindForKey(std::wstring const& key);
        void MarshalArguments(Microsoft::Windows::AppLifecycle::ActivationArguments const& args);
        Microsoft::Windows::AppLifecycle::ActivationArguments UnmarshalArguments();

        static INIT_ONCE s_initInstance;
        static winrt::com_ptr<AppInstance> s_instance;

        winrt::event<winrt::Windows::Foundation::EventHandler<ActivationArguments>> m_activatedEvent;

        bool m_isCurrent;
        std::wstring_view m_key;
        wil::unique_mutex m_dataMutex;
        wil::unique_mutex m_keyMutex;
        wil::unique_event m_innerActivated;
        wil::unique_event_watcher m_activationWatcher;

        struct InstanceData
        {
            uint32_t processId = 0;
            wchar_t key[255]{ 0 };
            uint8_t stream[1024]{ 0 };
        };
        shared_memory<InstanceData> m_data;

        InstanceList m_processIds;
    };
}

namespace winrt::Microsoft::Windows::AppLifecycle::factory_implementation
{
    struct AppInstance : AppInstanceT<AppInstance, implementation::AppInstance>
    {
    };
}
