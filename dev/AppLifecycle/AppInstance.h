// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <Microsoft.Windows.AppLifecycle.AppInstance.g.h>

#include "SharedMemory.h"
#include "RedirectionRequest.h"
#include "SharedProcessList.h"
#include "RedirectionRequestQueue.h"

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    static const PCWSTR c_requestPacketNameFormat = L"%s_RedirectionRequest_%s";
    static const PCWSTR c_activatedEventNameSuffix = L"_ActivatedEvent";

    struct AppInstance : AppInstanceT<AppInstance>
    {
        // No interface public methods.
        AppInstance(uint32_t processId);

        // IAppInstanceStatics.
        static Microsoft::Windows::AppLifecycle::AppInstance GetCurrent();
        static winrt::Windows::Foundation::Collections::IVector<Microsoft::Windows::AppLifecycle::AppInstance> GetInstances();
        static Microsoft::Windows::AppLifecycle::AppInstance FindOrRegisterForKey(hstring const& key);

        // IAppInstance.
        void UnregisterKey();
        winrt::Windows::Foundation::IAsyncAction RedirectActivationToAsync(Microsoft::Windows::AppLifecycle::AppActivationArguments const& args);
        winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments GetActivatedEventArgs();
        winrt::event_token Activated(winrt::Windows::Foundation::EventHandler<Microsoft::Windows::AppLifecycle::AppActivationArguments> const& handler);
        void Activated(winrt::event_token const& token) noexcept;

        hstring Key();
        bool IsCurrent() { return m_isCurrent; }
        uint32_t ProcessId() { return m_processId; }

    private:
        winrt::Windows::Foundation::IAsyncAction QueueRequest(Microsoft::Windows::AppLifecycle::AppActivationArguments args);
        void OnInstanceTerminated();
        void ProcessRedirectionRequests();
        bool TrySetKey(std::wstring const& key);
        Microsoft::Windows::AppLifecycle::AppInstance FindForKey(std::wstring const& key);
        void EnqueueRedirectionRequestId(GUID id);
        GUID DequeueRedirectionRequestId();

        // Named object prefixes used to scope.
        std::wstring m_moduleName;
        std::wstring m_processName;

        static INIT_ONCE s_initOnce;
        static winrt::com_ptr<AppInstance> s_current;

        winrt::event<winrt::Windows::Foundation::EventHandler<Microsoft::Windows::AppLifecycle::AppActivationArguments>> m_activatedEvent;

        bool m_isCurrent;
        uint32_t m_processId{ 0 };

        wil::unique_mutex m_dataMutex;
        wil::unique_mutex m_keyCreationMutex;
        SharedMemory<wchar_t> m_key;

        wil::unique_event m_innerActivated;
        wil::unique_event_watcher m_activationWatcher;

        wil::unique_event_watcher m_terminationWatcher;
        wil::unique_handle m_instanceHandle;

        SharedProcessList m_instances;
        RedirectionRequestQueue m_redirectionArgs;
    };
}

namespace winrt::Microsoft::Windows::AppLifecycle::factory_implementation
{
    struct AppInstance : AppInstanceT<AppInstance, implementation::AppInstance>
    {
    };
}
