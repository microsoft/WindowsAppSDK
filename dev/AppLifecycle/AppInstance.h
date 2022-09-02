// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <Microsoft.Windows.AppLifecycle.AppInstance.g.h>

#include "SharedMemory.h"
#include "RedirectionRequest.h"
#include "SharedProcessList.h"
#include "RedirectionRequestQueue.h"

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    static PCWSTR c_requestPacketNameFormat = L"%s_RedirectionRequest_%s";
    static PCWSTR c_activatedEventNameSuffix = L"_ActivatedEvent";
    static PCWSTR c_restartAgentFilename{ L"RestartAgent.exe" };

    struct AppInstance : AppInstanceT<AppInstance>
    {
        // No interface public methods.
        AppInstance(uint32_t processId);
        ~AppInstance()
        {
            if (m_terminationWatcherWaitHandle)
            {
                UnregisterWait(m_terminationWatcherWaitHandle);
            }
        }

        // IAppInstanceStatics.
        static Microsoft::Windows::AppLifecycle::AppInstance GetCurrent();
        static winrt::Windows::Foundation::Collections::IVector<Microsoft::Windows::AppLifecycle::AppInstance> GetInstances();
        static Microsoft::Windows::AppLifecycle::AppInstance FindOrRegisterForKey(hstring const& key);
        static winrt::Windows::ApplicationModel::Core::AppRestartFailureReason Restart(hstring const& arguments);

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
        static std::wstring GenerateRestartAgentPath();
        winrt::Windows::Foundation::IAsyncAction QueueRequest(Microsoft::Windows::AppLifecycle::AppActivationArguments args);
        void RemoveInstance(uint32_t processId);
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
        // Listing this after the mutex it locks, guarantees that
        // the lock gets released first before releasing the mutex itself.
        // Destruction order is reverse of declaration order, see C++ std: 12.6.2
        wil::mutex_release_scope_exit m_keyCreationMutexLock;
        SharedMemory<wchar_t> m_key;

        wil::unique_event m_innerActivated;
        wil::unique_event_watcher m_activationWatcher;

        // Wait threadpool handle for cleaning up AppInstance data on termination.  This handle is invalid for use with CloseHandle().
        HANDLE m_terminationWatcherWaitHandle{ nullptr };
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
